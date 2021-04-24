/// @file poll2.cpp
/// @brief This program is designed as a replacement of the POLL program for reading
///   data from PIXIE-16 crates. The old POLL program relied on a connection
///   to PACMAN in order to receive commands whereas this is a stand-alone program
///   with a built-in command line interface.
///   Data is also not transmitted onto a socket (except for shm).
/// @author S. V. Paulauskas and C. R. Thornsberry
/// @date January 21, 2015
/// @date September 15, 2018
#include "poll2_core.h"

#include "args.hxx"
#include "CTerminal.h"
#include "Display.h"
#include "StringManipulationFunctions.hpp"

#include <iostream>
#include <thread>

#include <sys/stat.h>


void start_run_control(Poll* poll_) {
    poll_->RunControl();
}

void start_cmd_control(Poll* poll_) {
    poll_->CommandControl();
}

int main(int argc, char* argv[]) {
    args::ArgumentParser parser("Data acquisition and module configuration for XIA's Pixie Hardware.");
    args::Group arguments(parser, "arguments", args::Group::Validators::AtLeastOne, args::Options::Global);

    args::HelpFlag help_flag(arguments, "help", "Displays this message", {'h', "help"});

    args::ValueFlag<std::string> configuration(arguments, "cfg", "The configuration file to load.", {'c', "cfg"},
                                               args::Options::Required);
    args::Flag debug(arguments, "debug", "Turn on debugging", {'d', "debugging"});
    args::Flag is_fast_boot(arguments, "fast-boot", "Performs a partial boot of the system.", {'f', "fast-boot"});
    args::Flag is_verbose(arguments, "verbosity", "How much info gets printed to the terminal.", {'v', "verbose"});
    args::Flag no_wall_clock(arguments, "wall-clock", "Do not insert the wall clock in the data stream",
                             {"no-wall-clock"});
    args::Flag rates(arguments, "rates", "Display module rates in quiet mode", {"rates"});

    args::Flag use_emulated_interface(arguments, "emulation", "Tells the API to use Offline mode when running.",
                                      {'e', "emulated"});
    args::Flag zero(arguments, "zero clocks", "Zero clocks on each START_ACQ (false by default)", {"zero"});

    args::ValueFlag<double> thresh(arguments, "FIFO threshold",
                                   "Sets FIFO read threshold to num% full (50% by default)",
                                   {'t', "thresh"}, 50);
    args::ValueFlag<std::string> alarms(arguments, "alarm",
                                        "Call the alarm script with a given e-mail (or no argument)", {'a', "alarm"},
                                        "");

    try {
        parser.ParseCLI(argc, argv);
    } catch (args::Help& help) {
        std::cout << parser;
        return EXIT_SUCCESS;
    } catch (args::ValidationError& e) {
        std::cerr << e.what() << std::endl;
        std::cout << parser;
        return EXIT_FAILURE;
    } catch (args::Error& e) {
        std::cerr << e.what() << std::endl;
        std::cout << parser;
        return EXIT_FAILURE;
    }

    Poll poll;
    poll.SetQuietMode();

    if (alarms) {
        poll.SetSendAlarm();
        Display::LeaderPrint("Sending alarms to " + alarms.Get());
        poll.SetAlarmEmailList(alarms.Get());
    }

    if (is_fast_boot)
        poll.SetBootFast();

    if (is_verbose)
        poll.SetQuietMode(false);

    if (thresh) {
        if (thresh.Get() <= 0) {
            std::cerr << Display::ErrorStr() << " Threshold percentage must be greater than 0!!\n";
            return EXIT_FAILURE;
        }
        poll.SetThreshWords(thresh.Get());
    }

    if (debug)
        poll.SetDebugMode();

    if (no_wall_clock)
        poll.SetWallClock();

    if (rates)
        poll.SetShowRates();

    if (zero)
        poll.SetZeroClocks();

    try {
        if (!use_emulated_interface)
            poll.Initialize(configuration.Get(), true);
        else
            poll.Initialize(configuration.Get(), false);
    } catch (std::exception& exception) {
        std::cout << "poll2 : Caught exception while initializing Poll. \n" << exception.what() << "\n";
        return EXIT_FAILURE;
    }

    Terminal poll_term;
    poll_term.Initialize();

    std::string poll2Dir = getenv("HOME");
    if (!mkdir(poll2Dir.append("/.poll2/").c_str(), S_IRWXU))
        if (errno == EEXIST)
            std::cout << Display::ErrorStr() << "Unable to create poll2 settings directory '" << poll2Dir << "'!\n";

    std::cout << "\n#########      #####    ####      ####       ########\n";
    std::cout << " ##     ##    ##   ##    ##        ##       ##      ##\n";
    std::cout << " ##      ##  ##     ##   ##        ##                ##\n";
    std::cout << " ##     ##  ##       ##  ##        ##               ##\n";
    std::cout << " #######    ##       ##  ##        ##              ##\n";
    std::cout << " ##         ##       ##  ##        ##            ##\n";
    std::cout << " ##         ##       ##  ##        ##           ##\n";
    std::cout << " ##          ##     ##   ##        ##         ##\n";
    std::cout << " ##           ##   ##    ##    ##  ##    ##  ##\n";
    std::cout << "####           #####    ######### ######### ###########\n\n";

    poll_term.SetCommandHistory(poll2Dir + "poll2.cmd");
    poll_term.SetPrompt(Display::InfoStr("POLL2 $ ").c_str());
    poll_term.AddStatusWindow();
    poll_term.EnableTabComplete();
    poll_term.SetLogFile(poll2Dir + "poll2.log");
    poll.PrintModuleInfo();

    std::cout << std::endl;

    poll.SetTerminal(&poll_term);

    std::cout << StringManipulation::PadString("Starting run control thread", ".", 49);
    std::thread runctrl(start_run_control, &poll);
    std::cout << Display::OkayStr() << std::endl;

    std::cout << StringManipulation::PadString("Starting command thread", ".", 49);
    std::thread comctrl(start_cmd_control, &poll);
    std::cout << Display::OkayStr() << std::endl << std::endl;

    comctrl.join();
    runctrl.join();

    poll.Close();
    poll_term.Close();

    Display::LeaderPrint(std::string("Running poll2"));
    std::cout << Display::OkayStr("[Done]") << std::endl;
}
