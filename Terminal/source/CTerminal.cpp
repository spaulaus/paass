/// @file CTerminal.cpp
/// @brief Library to handle all aspects of a stand-alone interactive command line interface under a linux environment
/// @author Cory R. Thornsberry, Karl Smith, S. V. Paulauskas
/// @date November 27, 2015
#include "CTerminal.h"
#include "TermColors.h"

#include <chrono>
#include <iostream>

#include <csignal>
#include <stdexcept>

#include <unistd.h>

bool SIGNAL_SEGFAULT = false;
bool SIGNAL_INTERRUPT = false;
bool SIGNAL_TERMSTOP = false;
bool SIGNAL_RESIZE = false;

// Make a typedef for clarity when working with chrono.
typedef std::chrono::system_clock sclock;

unsigned int cstrlen(const char* str_) {
    unsigned int output = 0;
    while (true) {
        if (str_[output] == '\0') { break; }
        output++;
    }
    return output;
}

std::string csubstr(char* str_, unsigned int start_index_/*=0*/) {
    std::string output;
    unsigned int index = start_index_;
    while (str_[index] != '\0' && str_[index] != ' ') {
        output += str_[index];
        index++;
    }
    return output;
}

///////////////////////////////////////////////////////////////////////////////
// CommandHolder
///////////////////////////////////////////////////////////////////////////////

void CommandHolder::Push(std::string& input_) {
    input_.erase(input_.find_last_not_of(" \n\t\r") + 1);
    commands[index] = input_;
    total++;
    index++;
    external_index = 0;

    if (index >= max_size) { index = 0; }
}

void CommandHolder::Clear() {
    for (unsigned int i = 0; i < max_size; i++) {
        commands[i] = "";
    }
}


unsigned int CommandHolder::wrap_() const {
    if (index < external_index) {
        unsigned int temp = (external_index - index) % max_size;
        return max_size - temp;
    } else if (index >= max_size + external_index) {
        unsigned int temp = (index - external_index) % max_size;
        return temp;
    }
    return (index - external_index);
}

std::string CommandHolder::GetPrev() {
    if (total == 0) { return "NULL"; }

    external_index++;
    if (external_index >= max_size) {
        external_index = max_size - 1;
    } else if (external_index >= total) {
        external_index = total;
    }

    return commands[wrap_()];
}

std::string CommandHolder::PeekPrev() {
    if (total == 0) { return "NULL"; }

    if (index == 0) { return commands[max_size - 1]; }
    return commands[index - 1];
}

std::string CommandHolder::GetNext() {
    if (total == 0) { return "NULL"; }

    if (external_index >= 1) {
        external_index--;
    }

    if (external_index == 0) { return fragment; }
    return commands[wrap_()];
}

std::string CommandHolder::PeekNext() {
    if (total == 0) { return "NULL"; }

    if (index == max_size - 1) { return commands[0]; }
    return commands[index + 1];
}

void CommandHolder::Dump() {
    for (unsigned int i = 0; i < max_size; i++)
        if (!commands[i].empty())
            std::cout << " " << i << ": " << commands[i] << std::endl;
}

void CommandHolder::Reset() {
    external_index = 0;
}

///////////////////////////////////////////////////////////////////////////////
// Terminal
///////////////////////////////////////////////////////////////////////////////

void sig_segv_handler(int ignore_) {
    SIGNAL_SEGFAULT = true;
}

void sig_int_handler(int ignore_) {
    SIGNAL_INTERRUPT = true;
}

void sig_tstp_handler(int ignore_) {
    SIGNAL_TERMSTOP = true;
}

void signalResize(int ignore_) {
    SIGNAL_RESIZE = true;
}

// Setup the interrupt signal intercept
void setup_signal_handlers() {
    // Handle segmentation faults press (SIGSEGV)
    if (signal(SIGSEGV, SIG_IGN) != SIG_IGN) {
        if (signal(SIGSEGV, sig_segv_handler) == SIG_ERR) {
            throw std::runtime_error(
            " Error setting up SIGSEGV signal handler!");
        }
    }

    // Handle ctrl-c press (SIGINT)
    if (signal(SIGINT, SIG_IGN) != SIG_IGN) {
        if (signal(SIGINT, sig_int_handler) == SIG_ERR) {
            throw std::runtime_error(
            " Error setting up SIGINT signal handler!");
        }
    }

    // Handle ctrl-z press (SIGTSTP)
    if (signal(SIGTSTP, SIG_IGN) != SIG_IGN) {
        if (signal(SIGTSTP, sig_tstp_handler) == SIG_ERR) {
            throw std::runtime_error(
            " Error setting up SIGTSTP signal handler!");
        }
    }

    //Handle resize signal
    signal(SIGWINCH, signalResize);
}

void unset_signal_handlers() {
    signal(SIGSEGV, SIG_DFL);
    signal(SIGINT, SIG_DFL);
    signal(SIGTSTP, SIG_DFL);
    signal(SIGWINCH, SIG_DFL);
}

void Terminal::resize_() {
    //end session and then refresh to get new window sizes.
    endwin();
    refresh();

    //Mark resize as handled
    SIGNAL_RESIZE = false;

    //Get new window sizes
    getmaxyx(stdscr, _winSizeY, _winSizeX);

    //Make pad bigger if needed.
    int outputSizeY;
    int outputSizeX;
    getmaxyx(output_window, outputSizeY, outputSizeX);
    if (outputSizeX < _winSizeX) {
        wresize(output_window, _scrollbackBufferSize, _winSizeX);
        wresize(input_window, 1, _winSizeX);
        if (status_window) wresize(status_window, _statusWindowSize, _winSizeX);
    }
    if (outputSizeY < _winSizeY) {
        _scrollbackBufferSize = outputSizeY;
        wresize(output_window, _scrollbackBufferSize, _winSizeX);
    }

    //Update the physical cursor location
    cursY = _winSizeY - _statusWindowSize - 1;

}

void Terminal::pause(bool& flag) {
    endwin();
    std::cout.rdbuf(original); // Restore cout's original streambuf
    setvbuf(stdout, nullptr, _IOLBF, 0); //Change to line buffering
    while (flag) sleep(1);
    std::cout.rdbuf(pbuf); // Restore cout's original streambuf
    refresh_();
}

void Terminal::refresh_() {
    if (!init) { return; }
    if (SIGNAL_RESIZE) resize_();

    pnoutrefresh(output_window,
                 _scrollbackBufferSize - _winSizeY - _scrollPosition + 1,
                 0,  //Pad corner to be placed in top left
                 0, 0, _winSizeY - _statusWindowSize - 2,
                 _winSizeX - 1); //Size of window
    pnoutrefresh(input_window, 0, 0, _winSizeY - _statusWindowSize - 1, 0,
                 _winSizeY - _statusWindowSize, _winSizeX - 1);
    if (status_window)
        pnoutrefresh(status_window, 0, 0, _winSizeY - _statusWindowSize, 0,
                     _winSizeY, _winSizeX - 1);

    refresh();

}

void Terminal::scroll_(int numLines) {
    if (!init) { return; }
    //We subtract so that a negative number is scrolled up resulting in a positive position value.
    _scrollPosition -= numLines;
    if (_scrollPosition > _scrollbackBufferSize - (_winSizeY - 1))
        _scrollPosition = _scrollbackBufferSize - (_winSizeY - 1);
    else if (_scrollPosition < 0) _scrollPosition = 0;
    refresh_();

}

void Terminal::update_cursor_() {
    if (!init) { return; }
    move(cursY, cursX); // Move the physical cursor
    wmove(input_window, 0,
          cursX); // Move the logical cursor in the input window
    refresh_();
}

void Terminal::clear_() {
    for (auto start = cmd.length() + offset; start >= 0; start--) {
        wmove(input_window, 0, start);
        wdelch(input_window);
    }
    cmd.clear();
    cursX = 0;
    update_cursor_();
    refresh_();
}

void Terminal::ClearCmd() { Terminal::clear_(); }

void Terminal::AddStatusWindow(unsigned short numLines) {
    _statusWindowSize = numLines;
    //Create the new status pad.
    status_window = newpad(_statusWindowSize, _winSizeX);

    for (int i = 0; i < numLines; i++)
        statusStr.emplace_back(std::string(""));

    //Update the cursor position
    cursY = _winSizeY - _statusWindowSize - 1;
    update_cursor_();

    //Refresh the screen
    refresh_();
}

void Terminal::SetStatus(std::string status, unsigned short line) {
    ClearStatus(line);
    AppendStatus(status, line);
}

void Terminal::ClearStatus(unsigned short line) {
    if (status_window)
        statusStr.at(line) = "";
}

void Terminal::AppendStatus(std::string status, unsigned short line) {
    if (status_window)
        statusStr.at(line).append(status);
}

// Force a character to the input screen
void Terminal::in_char_(const char input_) {
    cursX++;
    //If in insert mode we overwite the character otherwise insert it.
    if (insertMode_) waddch(input_window, input_);
    else winsch(input_window, input_);
    update_cursor_();
    refresh_();
}

// Force text to the input screen
void Terminal::in_print_(const char* input_) {
    cursX += cstrlen(input_);
    waddstr(input_window, input_);
    update_cursor_();
    refresh_();
}

void Terminal::init_colors_() {
    if (has_colors()) {
        start_color();
        //Use user's terminal colors.
        use_default_colors();

        //Define colors
        init_pair(1, COLOR_GREEN, -1);
        init_pair(2, COLOR_RED, -1);
        init_pair(3, COLOR_BLUE, -1);
        init_pair(4, COLOR_YELLOW, -1);
        init_pair(5, COLOR_MAGENTA, -1);
        init_pair(6, COLOR_CYAN, -1);
        init_pair(7, COLOR_WHITE, -1);

        //Assign colors to map
        attrMap[paass::terminal_colors::DkGreen] = COLOR_PAIR(1);
        attrMap[paass::terminal_colors::BtGreen] = COLOR_PAIR(1);
        attrMap[paass::terminal_colors::DkRed] = COLOR_PAIR(2);
        attrMap[paass::terminal_colors::BtRed] = COLOR_PAIR(2);
        attrMap[paass::terminal_colors::DkBlue] = COLOR_PAIR(3);
        attrMap[paass::terminal_colors::BtBlue] = COLOR_PAIR(3);
        attrMap[paass::terminal_colors::DkYellow] = COLOR_PAIR(4);
        attrMap[paass::terminal_colors::BtYellow] = COLOR_PAIR(4);
        attrMap[paass::terminal_colors::DkMagenta] = COLOR_PAIR(5);
        attrMap[paass::terminal_colors::BtMagenta] = COLOR_PAIR(5);
        attrMap[paass::terminal_colors::DkCyan] = COLOR_PAIR(6);
        attrMap[paass::terminal_colors::BtCyan] = COLOR_PAIR(6);
        attrMap[paass::terminal_colors::DkWhite] = COLOR_PAIR(7);
        attrMap[paass::terminal_colors::BtWhite] = COLOR_PAIR(7);
        attrMap[paass::terminal_colors::Flashing] = A_BLINK;
        attrMap[paass::terminal_colors::Underline] = A_UNDERLINE;
    }
}

bool Terminal::LoadCommandFile(const char* filename_) {
    std::ifstream input(filename_);

    // Check that the script opened successfully.
    if (!input.good()) {
        return false;
    }

    // Read the commands from the specified file.
    std::string cmdstr;
    while (true) {
        std::getline(input, cmdstr);
        if (input.eof()) { break; }

        // Check for empty string.
        if (cmdstr.empty()) { continue; }

        // Search for comments.
        if (cmdstr.find('#') != std::string::npos) {
            // Strip off trailing comments.
            cmdstr = cmdstr.substr(0, cmdstr.find_first_of('#'));
        }

        // Strip leading whitespace.
        if (!cmdstr.empty()) {
            cmdstr = cmdstr.substr(cmdstr.find_first_not_of(' '));
        }

        // Strip trailing whitespace.
        if (!cmdstr.empty()) {
            cmdstr = cmdstr.substr(0, cmdstr.find_last_not_of(' ') + 1);
        }

        // Check for empty string again since we've processed some more.
        if (cmdstr.empty()) { continue; }

        // Push the command into the command array
        cmd_queue.push_back(cmdstr);
    }

    input.close();
    return true;
}

bool Terminal::LoadCommandHistory(bool overwrite) {
    std::ifstream input(historyFilename_.c_str());

    //If the stream doesn't open we assume it has been created before and quietly fail.
    if (!input.good()) {
        return false;
    }

    //The current commands were to be overwritten
    if (overwrite) {
        commands.Clear();
    }

    //Read the commands from the specified file.
    size_t index;
    std::string cmdstr;
    std::vector<std::string> cmds;
    while (true) {
        std::getline(input, cmdstr);
        if (input.eof()) { break; }

        // Strip the newline from the end
        index = cmdstr.find('\n');
        if (index != std::string::npos) {
            cmdstr.erase(index);
        }

        // Push the command into the command array
        if (!cmdstr.empty()) { // Just to be safe!
            cmds.push_back(cmdstr);
        }
    }

    if (!cmds.empty()) {
        // Push commands into the array in reverse order so that the original order is preserved
        auto iter = cmds.end() - 1;
        while (true) {
            commands.Push(*iter);
            if (iter == cmds.begin()) { break; }
            else { iter--; }
        }
    }

    input.close();
    return true;
}

bool Terminal::SaveCommandHistory() {
    if (historyFilename_.empty()) return true;

    std::ofstream output(historyFilename_.c_str());
    if (!output.good()) {
        std::cout << "ERROR: Unable to open command history for writing! '"
                  << historyFilename_ << "'\n";
        return false;
    }

    std::string temp;
    unsigned int num_entries;
    if (commands.GetTotal() >
        commands.GetSize()) { num_entries = commands.GetSize(); }
    else { num_entries = commands.GetTotal(); }

    for (unsigned int i = 0; i < num_entries; i++) {
        temp = commands.GetPrev();
        if (temp != "NULL") { // Again, just to be safe
            output << temp << std::endl;
        }
    }

    output.close();
    return true;
}

Terminal::Terminal() : pbuf(nullptr), original(nullptr), main(nullptr), output_window(nullptr), input_window(nullptr),
                       status_window(nullptr), _statusWindowSize(0), commandTimeout_(0), insertMode_(false),
                       debug_(false), _scrollbackBufferSize(SCROLLBACK_SIZE), _scrollPosition(0) {
    from_script = false;
    prompt_user = false;
    historyFilename_ = "";
    init = false;
    cursX = 0;
    cursY = 0;
    offset = 0;
}

Terminal::~Terminal() {
    if (init) {
        flush(); // Make sure no text is remaining in the buffer
        Close();
    }
}

void Terminal::Initialize() {
    if (init)
        return;

    original = std::cout.rdbuf(); // Back-up cout's streambuf
    pbuf = stream.rdbuf(); // Get stream's streambuf
    std::cout.flush();
    std::cout.rdbuf(pbuf); // Assign streambuf to cout

    main = initscr();

    if (main == nullptr) { // Attempt to initialize ncurses
        std::cout.rdbuf(original); // Restore cout's original streambuf
        fprintf(stderr, " Error: failed to initialize ncurses!\n");
    } else {
        getmaxyx(stdscr, _winSizeY, _winSizeX);
        output_window = newpad(_scrollbackBufferSize, _winSizeX);
        input_window = newpad(1, _winSizeX);
        wmove(output_window, _scrollbackBufferSize - 1,
              0); // Set the output cursor at the bottom so that new text will scroll up

        if (halfdelay(5) == ERR) { // Timeout after 5/10 of a second
            std::cout
            << "WARNING: Unable to set terminal blocking half delay to 0.5s!\n";
            std::cout
            << "\tThis will increase CPU usage in the command thread.\n";
            if (nodelay(input_window, true) == ERR) {
                //Disable the blocking timeout.
                std::cout << "ERROR: Unable to remove terminal blocking!\n";
                std::cout
                << "\tThe command thread will be locked until a character is entered. This will reduce functionality of terminal status bar and timeout.\n";
            }
        }
        keypad(input_window, true); // Capture special keys
        noecho(); // Turn key echoing off

        scrollok(output_window, true);
        scrollok(input_window, true);

        if (NCURSES_MOUSE_VERSION > 0) {
            mousemask(ALL_MOUSE_EVENTS, nullptr);
            mouseinterval(0);
        }

        init = true;
        offset = 0;

        // Set the position of the physical cursor
        cursX = 0;
        cursY = _winSizeY - 1;
        update_cursor_();
        refresh_();

        init_colors_();
    }

    setup_signal_handlers();
}

void Terminal::SetCommandHistory(std::string filename, bool overwrite/*=false*/) {
    //Store the command file name.
    historyFilename_ = filename;

    LoadCommandHistory(overwrite);
}

void Terminal::SetPrompt(const char* input_) {
    prompt = input_;

    //Calculate the offset.
    //This is long winded as we want to ignore the escape sequences
    offset = 0;
    size_t pos = 0, lastPos = 0;
    while ((pos = prompt.find("\033[", lastPos)) != std::string::npos) {
        //Increase offset by number characters prior to escape
        offset += pos - lastPos;
        lastPos = pos;

        //Identify which escape code we found.
        //First try reset code then loop through other codes
        if (pos == prompt.find(paass::terminal_colors::Reset, pos)) {
            lastPos += std::string(paass::terminal_colors::Reset).length();
        } else {
            for (const auto &it : attrMap) {
                //If the attribute is at the same position then we found this attribute and we turn it on
                if (pos == prompt.find(it.first, pos)) {
                    //Iterate position to suppress printing the escape string
                    lastPos += std::string(it.first).length();
                    break;
                }
            }
        }
    }
    offset += prompt.length() - lastPos;

    PrintPrompt();
}

void Terminal::PrintPrompt() {
    print(input_window, prompt);
    cursX = offset;
    update_cursor_();
    refresh_();
}

// Force a character to the output screen
void Terminal::putch(const char input_) {
    waddch(output_window, input_);
    refresh_();
}

// Force text to the output screen
void Terminal::print(WINDOW* window, const std::string& input_) {
    size_t pos = 0, lastPos = 0;
    //Search for escape sequences
    while ((pos = input_.find("\033[", lastPos)) != std::string::npos) {
        //Output the string from last location to current escape sequence
        waddstr(window, input_.substr(lastPos, pos - lastPos).c_str());
        lastPos = pos;

        //Identify which escape code we found.
        //First try reset code then loop through other codes
        if (pos == input_.find(paass::terminal_colors::Reset, pos)) {
            wattrset(window, A_NORMAL);
            lastPos += std::string(paass::terminal_colors::Reset).length();
        } else {
            for (auto it = attrMap.begin(); it != attrMap.end(); ++it) {
                //If the attribute is at the same position then we found this attribute and we turn it on
                if (pos == input_.find(it->first, pos)) {
                    wattron(window, it->second);
                    //Iterate position to suppress printing the escape string
                    lastPos += std::string(it->first).length();
                    break;
                }
            }
        }
    }
    //Print the remaining string content
    waddstr(window, input_.substr(lastPos).c_str());
    refresh_();
}

// Dump all text in the stream to the output screen
void Terminal::flush() {
    std::string stream_contents = stream.str();
    if (!stream_contents.empty()) {
        print(output_window, stream_contents);
        if (logFile.good()) {
            logFile << stream.str();
            logFile.flush();
        }
        stream.str("");
        stream.clear();
    }
}

bool Terminal::SetLogFile(std::string logFileName) {
    logFile.open(logFileName, std::ofstream::app);
    if (!logFile.good()) {
        std::cout << "ERROR: Unable to open log file: " << logFileName << "!\n";
        return false;
    }
    return true;

}


void Terminal::EnableTabComplete(bool enable) {
    enableTabComplete = enable;
}


void Terminal::EnableTimeout(float timeout/*=0.5*/) {
    commandTimeout_ = timeout;
}

void Terminal::TabComplete(const std::string& input_, const std::vector<std::string>& possibilities_) {
    if (input_.empty() || possibilities_.empty())
        return;

    std::vector<std::string> matches;

    size_t start = input_.find_last_of(' ');
    if (start == std::string::npos)
        start = 0;
    else
        start++;

    size_t stop = input_.length() - 1; // Strip off the trailing '\t'.

    //Get the string to complete
    std::string strToComplete = input_.substr(start, stop - start);

    for (const auto &it: possibilities_) {
        if (it.empty())
            continue;
        if (it.find(strToComplete) == 0)
            matches.push_back(it.substr(strToComplete.length()));
    }

    //No tab complete matches so we do nothing.
    if (matches.empty())
        return;

        //A unique match so we extend the command with completed text
    else if (matches.size() == 1) {
        if (matches.at(0).find('/') == std::string::npos &&
            (unsigned int) (cursX - offset) == cmd.length()) {
            matches.at(0).append(" ");
        }
        cmd.insert(cursX - offset, matches.at(0));
        waddstr(input_window, cmd.substr(cursX - offset).c_str());
        cursX += matches.at(0).length();
    } else {
        std::string commonStr = matches.at(0);
        for (auto it = matches.begin() + 1; it != matches.end() && !commonStr.empty(); ++it) {
            while (!commonStr.empty()) {
                if ((*it).find(commonStr) == 0) break;
                commonStr.erase(commonStr.length() - 1);
            }
        }
        if (!commonStr.empty()) {
            cmd.insert(cursX - offset, commonStr);
            waddstr(input_window, cmd.substr(cursX - offset).c_str());
            cursX += commonStr.length();
        } else if (tabCount > 1) {
            //Compute the header position
            size_t headerPos = cmd.find_last_of(" /", cursX - offset - 1);
            std::string header;
            if (headerPos == std::string::npos)
                header = cmd;
            else
                header = cmd.substr(headerPos + 1,cursX - offset - 1 - headerPos);
            std::cout << prompt.c_str() << cmd << "\n";
            for (const auto &match : matches)
                std::cout << header << match << "\t";
            std::cout << "\n";
        }
    }
    update_cursor_();
    refresh_();
}

void Terminal::PrintCommand(const std::string& cmd_) {
    std::cout << prompt << cmd_ << "\n";
    flush();
    _scrollPosition = 0;
    clear_();
    tabCount = 0;
}

std::string Terminal::GetCommand(std::string& args, const int& prev_cmd_return_/*=0*/) {
    if (cursX == 0) {
        PrintPrompt();
    }
    std::string output;

    sclock::time_point commandRequestTime = sclock::now();
    sclock::time_point currentTime;

    //Update status message
    if (status_window) {
        werase(status_window);
        print(status_window, statusStr.at(0));
    }

    // Check for commands in the command queue.
    if (!prompt_user && !cmd_queue.empty()) {
        while (true) {
            output = cmd_queue.front();
            cmd_queue.pop_front();

            // Check for blank lines.
            if (!output.empty()) { break; }
        }
        from_script = true;
    } else {
        // Get a command from the user.
        while (true) {
            if (SIGNAL_SEGFAULT) { // segmentation fault (SIGSEGV)
                Close();
                return "_SIGSEGV_";
            }
            if (SIGNAL_INTERRUPT) { // ctrl-c (SIGINT)
                SIGNAL_INTERRUPT = false;
                output = "CTRL_C";
                break;
            }
            if (SIGNAL_TERMSTOP) { // ctrl-z (SIGTSTP)
                SIGNAL_TERMSTOP = false;
                output = "CTRL_Z";
                break;
            }

            //Update status message
            if (status_window) {
                werase(status_window);
                print(status_window, statusStr.at(0));
            }

            flush(); // If there is anything in the stream, dump it to the screen

            // Time out if there is no command within the set interval (default 0.5 s).
            if (commandTimeout_ > 0) {
                // Update the current time.
                currentTime = sclock::now();
                std::chrono::duration<float> time_span = std::chrono::duration_cast<std::chrono::duration<float>>(
                currentTime - commandRequestTime);

                // If the timeout has passed we simply return the empty output string.
                if (time_span.count() > commandTimeout_) {
                    break;
                }
            }

            auto keypress = wgetch(input_window);

            if (keypress == ERR)
                continue;

            if (debug_) {
                std::cout << "TERM: Curs (" << cursX << "-" << offset << ", "
                          << cursY << ") ";
                std::cout << "Key: " << keypress << " " << (char) keypress
                          << " ";
                std::cout << "\n";
            }

            if (keypress == 10) { // Enter key (10)
                std::string temp_cmd = cmd;
                //Reset the position in the history.
                commands.Reset();
                if (!temp_cmd.empty() && temp_cmd != commands.PeekPrev()) {
                    // Only save this command if it is different than the previous command
                    commands.Push(temp_cmd);
                }
                output = temp_cmd;
                std::cout << prompt << output << "\n";
                flush();
                _scrollPosition = 0;
                clear_();
                tabCount = 0;
                break;
            } else if (keypress == '\t' && enableTabComplete) {
                //increase the count for tab presses
                tabCount++;

                //Compute the boundaris of this command taking into account semicolons.
                size_t stop = cursX - offset;
                size_t start = cmd.find_last_of(';', cursX - offset - 1) + 1;
                //Check that the values are reasonable
                if (start == std::string::npos) start = 0;
                if (stop == std::string::npos) stop = cmd.length();

                //Determine string to be passed to tab completer and add '\t' character.
                output = cmd.substr(start, stop - start) + "\t";

                //Output debug info.
                if (debug_) {
                    std::cout << "TERM: Tab complete " << start << "<->" << stop
                              << " ";
                    std::cout << " '" << output << "'" << "\n";
                }

                break;
            } else if (keypress == 4) { // ctrl-d (EOT)
                output = "CTRL_D";
                clear_();
                tabCount = 0;
                break;
            } else if (keypress == KEY_UP) { // 259
                if (commands.GetIndex() == 0) { commands.Capture(cmd); }
                std::string temp_cmd = commands.GetPrev();
                if (temp_cmd != "NULL") {
                    clear_();
                    PrintPrompt();
                    cmd.assign(temp_cmd);
                    in_print_(cmd.c_str());
                }
            } else if (keypress == KEY_DOWN) { // 258
                std::string temp_cmd = commands.GetNext();
                if (temp_cmd != "NULL") {
                    clear_();
                    PrintPrompt();
                    cmd.assign(temp_cmd);
                    in_print_(cmd.c_str());
                }
            } else if (keypress == KEY_LEFT) { // 260
                cursX--;
            } else if (keypress == KEY_RIGHT) { // 261
                cursX++;
            } else if (keypress == KEY_PPAGE) { //Page up key
                scroll_(-(_winSizeY - 2));
            } else if (keypress == KEY_NPAGE) { //Page down key
                scroll_(_winSizeY - 2);
            } else if (keypress == KEY_BACKSPACE || keypress == 8) {
                // ncurses.h backspace character (KEY_BACKSPACE=263), ASCII code BS =8
                if (cursX - offset > 0) {
                    wmove(input_window, 0, --cursX);
                    wdelch(input_window);
                    cmd.erase(cursX - offset, 1);
                }
            } else if (keypress == KEY_DC || keypress == 127) {
                // ncurses.h Delete character (KEY_DC=330), ASCII code DEL=127
                //Remove character from terminal
                wdelch(input_window);
                //Remove character from cmd string
                cmd.erase(cursX - offset, 1);
            } else if (keypress == KEY_IC) { // Insert key (331)
                if (insertMode_) {
                    insertMode_ = false;
                } else {
                    insertMode_ = true;
                }
            } else if (keypress == KEY_HOME) {
                cursX = offset;
            } else if (keypress == KEY_END) {
                cursX = cmd.length() + offset;
            } else if (keypress == KEY_MOUSE) {
                //Handle mouse events
                MEVENT mouseEvent;
                //Get information about mouse event.
                getmouse(&mouseEvent);

                switch (mouseEvent.bstate) {
                    //Scroll up
                    case BUTTON4_PRESSED:
                        scroll_(-3);
                        break;
                        //Scroll down. (Yes the name is strange.)
                    case REPORT_MOUSE_POSITION:
                        scroll_(3);
                        break;
                }
            } else if (keypress == KEY_RESIZE) {
                //Do nothing with the resize key
            } else {
                in_char_((char) keypress);
                if (cursX - offset > (int) cmd.length()) {
                    cmd.push_back(keypress);
                } else { // Overwrite or insert a character
                    if (!insertMode_) {
                        cmd.insert(cursX - offset - 1, 1, keypress);
                    } // Insert
                    else { cmd.at(cursX - offset - 1) = keypress; } // Overwrite
                }
            }

            // Check for cursor too far to the left
            if (cursX < offset)
                cursX = offset;

            // Check for cursor too far to the right
            if (cursX > (int) (cmd.length() + offset))
                cursX = cmd.length() + offset;

            tabCount = 0;
            update_cursor_();
            refresh_();
        }

        if (prompt_user) { // Waiting for user to specify yes or no.
            if (output != "yes" && output != "y") {
                std::cout << prompt << "Aborting execution!\n";
                cmd_queue.clear();
            }
            prompt_user = false;
            return "";
        }

        from_script = false;
    }

    // In the event of an empty command, return.
    if (output.empty())
        return "";

    // Split the input string into commands separated by ';'.
    if (output.find(';') != std::string::npos) {
        split_commands(output, cmd_queue);
        output = cmd_queue.front();
        cmd_queue.pop_front();
        from_script = true;
    }

    // Split the string into a command and an argument.
    size_t start = output.find_first_not_of(' ');
    size_t stop = output.find_first_of(' ', start);
    std::string temp_cmd_string = output.substr(start, stop -
                                                       start); // Strip the command from the front of the input.

    // Strip whitspace from the beginning and end of the argument string.
    if (stop != std::string::npos) {
        start = output.find_first_not_of(' ', stop);
        stop = output.find_last_not_of(' ');
        args = output.substr(start, stop - start + 1);
    } else
        args = "";

    if (temp_cmd_string.empty() || temp_cmd_string[0] == '#') {
        // This is a comment line.
        return "";
    }

    if (temp_cmd_string[0] == '.') {
        if (temp_cmd_string == ".cmd") { // Load a command script.
            std::string command_filename = args.substr(
            args.find_first_not_of(' ')); // Ignores leading whitespace.
            if (!LoadCommandFile(
            command_filename.c_str())) { // Failed to load command script.
                std::cout << prompt << "Error! Failed to load command script "
                          << command_filename << ".\n";
            }
        } else if (temp_cmd_string ==
                   ".echo") { // Print something to the screen.
            std::cout << prompt << args << std::endl;
        } else if (temp_cmd_string ==
                   ".prompt") { // Prompt the user with a yes/no question.
            std::cout << prompt << args << " (yes/no)" << std::endl;
            prompt_user = true;
        } else { // Unrecognized command.
            std::cout << prompt << "Error! Unrecognized system command "
                      << temp_cmd_string << ".\n";
        }

        return ""; // Done processing the command. Don't need to send it to the caller.
    }

    // Print the command if it was read from a script. This is done so that the user
    // will know what is happening in the script file. It will also ignore system
    // commands in the file.
    if (from_script)
        PrintCommand(output.substr(output.find_first_not_of(' ')));

    return temp_cmd_string;
}

// Close the window and return control to the terminal
void Terminal::Close() {
    if (init) {
        std::cout.rdbuf(original); // Restore cout's original streambuf
        delwin(output_window); // Delete the output window
        delwin(input_window); // Delete the input window
        delwin(main); // Delete the main window
        endwin(); // Restore Terminal settings

        SaveCommandHistory();
        if (logFile.good()) {
            logFile.close();
        }

        init = false;
    }

    unset_signal_handlers();
}

void Terminal::split_commands(const std::string& input_,
                              std::deque<std::string>& cmds) const {
    if (input_.find(';') == std::string::npos) return;

    //Build a temporary deque of commands split on semicolon.
    std::deque<std::string> cmdQueue;

    size_t start = 0;
    size_t stop = 0;

    if (debug_) std::cout << "TERM: MultiCmd: '" << input_ << "' \n";

    int safety = 0;
    //Loop until we find no more semicolons.
    while (true) {
        safety++;
        if (safety > 100)
            break;
        stop = input_.find_first_of(';', start);
        if (debug_)
            std::cout << "\tsemicolon " << stop << " ";

        size_t dblQuotePos = start;
        int dblQuoteCnt = 0;
        while (dblQuotePos < stop && stop != std::string::npos) {
            safety++;
            if (safety > 100)
                break;

            dblQuotePos = input_.find_first_of('"', dblQuotePos + 1);

            if (debug_)
                std::cout << "dblQuote " << dblQuotePos << " ";

            if (dblQuotePos == std::string::npos) break;
            else if (dblQuotePos < stop) dblQuoteCnt++;
            else if (dblQuotePos > stop && dblQuoteCnt % 2 == 1) {
                stop = input_.find_first_of(';', dblQuotePos);
                if (debug_) std::cout << "semicolon inside " << stop << " ";
                break;
            }
        }

        cmdQueue.push_back(input_.substr(start, stop - start));
        if (debug_) {
            std::cout << "Cmd " << start << "<->" << stop << " ";
            std::cout << "'" << cmdQueue.back() << "'\n";
        }

        if (stop == std::string::npos) break;

        start = input_.find_first_not_of(';', stop);

        if (start == std::string::npos)
            break;
    }

    //If the destination queue iis empty we put split commands at the end,
    // if the destination has commands in it we put the split ones at the beginning.
    if (cmds.empty()) {
        while (!cmdQueue.empty()) {
            cmds.push_back(cmdQueue.front());
            cmdQueue.pop_front();
        }
    } else {
        while (!cmdQueue.empty()) {
            cmds.push_front(cmdQueue.back());
            cmdQueue.pop_back();
        }
    }
    if (debug_) std::cout << "\n";
}