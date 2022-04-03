///@file Ldf2ParquetInterface.cpp
///@brief
#include <iostream>

#include "Ldf2ParquetInterface.hpp"
#include "Ldf2ParquetUnpacker.hpp"
#include "StringManipulationFunctions.hpp"

using namespace std;

Ldf2ParquetInterface::Ldf2ParquetInterface() : ScanInterface() {
    init = false;
}

/** ExtraCommands is used to send command strings to classes derived
  * from ScanInterface. If ScanInterface receives an unrecognized
  * command from the user, it will pass it on to the derived class.
  * \param[in]  cmd_ The command to interpret.
  * \param[out] arg_ Vector or arguments to the user command.
  * \return True if the command was recognized and false otherwise.
  */
bool Ldf2ParquetInterface::ExtraCommands(const string& cmd_, vector<string>& args_) {
    return true;
}

/** ExtraArguments is used to send command line arguments to classes derived
  * from ScanInterface. This method should loop over the optionExt elements
  * in the vector userOpts and check for those options which have been flagged
  * as active by ::Setup(). This should be overloaded in the derived class.
  * \return Nothing.
  */
void Ldf2ParquetInterface::ExtraArguments() {
}

/** ArgHelp is used to allow a derived class to add a command line option
  * to the main list of options. This method is called at the end of
  * from the ::Setup method.
  * Does nothing useful by default.
  * \return Nothing.
  */
void Ldf2ParquetInterface::ArgHelp() {
    // Note that the following single character options are reserved by ScanInterface
    //  b, h, i, o, q, s, and v
}

/** SyntaxStr is used to print a linux style usage message to the screen.
  * \param[in]  name_ The name of the program.
  * \return Nothing.
  */
void Ldf2ParquetInterface::SyntaxStr(char* name_) {
    cout << " usage: " << string(name_) << " [options]\n";
}

/** Initialize the map file, the config file, the processor handler, 
  * and add all of the required processors.
  * \param[in]  prefix_ String to append to the beginning of system output.
  * \return True upon successfully initializing and false otherwise.
  */
bool Ldf2ParquetInterface::Initialize(string prefix_) {
    if (init)
        return false;
    // Do some initialization.
    return init = true;
}

/** Perform any last minute initialization before processing data.
  * /return Nothing.
  */
void Ldf2ParquetInterface::FinalInitialization() {
    auto unpacker = dynamic_cast<Ldf2ParquetUnpacker*>(unpacker_);
    unpacker->outfile.open(outputPath_ + outputFilename_);
    unpacker->outfile_extension = StringManipulation::GetFileExtension(outputFilename_);
}

/** Receive various status notifications from the scan.
  * \param[in] code_ The notification code passed from ScanInterface methods.
  * \return Nothing.
  */
void Ldf2ParquetInterface::Notify(const string& code_/*=""*/) {
    if (code_ == "START_SCAN") {}
    else if (code_ == "STOP_SCAN") {}
    else if (code_ == "SCAN_COMPLETE") {
        cout << msgHeader << "Scan complete.\n";
    } else if (code_ == "LOAD_FILE") {
        cout << msgHeader << "File loaded.\n";
    } else if (code_ == "REWIND_FILE") {}
    else {
        cout << msgHeader << "Unknown notification code '" << code_
             << "'!\n";
    }
}

