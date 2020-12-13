/// @file CTerminal.h
/// @brief Library to handle all aspects of a stand-alone interactive command line interface under a linux environment
/// @author Cory R. Thornsberry, Karl Smith, S. V. Paulauskas
/// @date October 1, 2015

#ifndef CTERMINAL_H
#define CTERMINAL_H

#include <deque>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <vector>

#include <curses.h>

///Default size of terminal scroll back buffer in lines.
#define SCROLLBACK_SIZE 1000

#define CTERMINAL_VERSION "1.2.10"
#define CTERMINAL_DATE "Sept. 7th, 2016"

extern std::string CPP_APP_VERSION;

///////////////////////////////////////////////////////////////////////////////
// CommandHolder
///////////////////////////////////////////////////////////////////////////////

class CommandHolder {
public:
    CommandHolder(unsigned int max_size_ = 1000) {
        max_size = max_size_;
        commands = new std::string[max_size];
        fragment = "";
        index = 0;
        total = 0;
        external_index = 0;
    }

    ~CommandHolder() { delete[] commands; }

    /// Get the maximum size of the command array
    unsigned int GetSize() { return max_size; }

    /// Get the total number of commands
    unsigned int GetTotal() { return total; }

    /// Get the current command index (relative to the most recent command)
    unsigned int GetIndex() { return external_index; }

    /// Push a new command into the storage array
    void Push(std::string& input_);

    /// Capture the current command line text and store it for later use
    void Capture(const std::string& input_) { fragment = input_; }

    /// Clear the command array
    void Clear();

    /// Get the previous command entry
    std::string GetPrev();

    /// Get the next command entry but do not change the internal array index
    std::string PeekPrev();

    /// Get the next command entry
    std::string GetNext();

    /// Get the next command entry but do not change the internal array index
    std::string PeekNext();

    /// Dump all stored commands to the screen
    void Dump();

    /// Reset history to last item
    void Reset();

private:
    unsigned int max_size;
    unsigned int index, total;
    unsigned int external_index;
    std::string* commands;
    std::string fragment;

    /** Convert the external index (relative to the most recent command) to the internal index
      * which is used to actually access the stored commands in the command array. */
    unsigned int wrap_();
};

///////////////////////////////////////////////////////////////////////////////
// Terminal
///////////////////////////////////////////////////////////////////////////////

void sig_int_handler(int ignore_);

// Setup the interrupt signal intercept
void setup_signal_handlers();

class Terminal {
public:
    Terminal();

    ~Terminal();

    /// Initialize the terminal interface
    void Initialize();

    ///Specify the log file to append.
    bool SetLogFile(std::string logFileName);

    ///Initalize terminal debug mode.
    void SetDebug(bool debug = true) { debug_ = debug; };

    /// Creates a status window and the refreshes the output. Takes an optional number of lines, defaulted to 1.
    /// \param[in] numLines: Vertical size of status window.
    void AddStatusWindow(unsigned short numLines = 1);

    ///Set the status message.
    void SetStatus(std::string status, unsigned short line = 0);

    ///Clear the status line.
    void ClearStatus(unsigned short line = 0);

    ///Append some text to the status line.
    void AppendStatus(std::string status, unsigned short line = 0);

    /**By enabling tab autocomplete the current typed command is returned via GetCommand() with a trailing tab character.
     *
     * \param[in] enable State of tab complete.
     */
    void EnableTabComplete(bool enable = true);

    /**Take the list of matching tab complete values and output resulting tab completion.
     * If the list is empty nothing happens, if a unique value is given the command is completed. If there are multiple
     * matches the common part of the matches is determined and printed to the input. If there is no common part of the
     * matches and the tab key has been pressed twice the list of matches is printed for the user to decide.
     *
     * \param[in] input_ The string to complete.
     * \param[in] possibilities_ A vector of strings of possible values.
     */
    void TabComplete(const std::string& input_, const std::vector<std::string>& possibilities_);

    /**By enabling the timeout the GetCommand() routine returns after a set
     * timesout period has passed. The current typed text is stored for the next
     * GetCommand call.
     *
     * \param[in] timeout The amount of time to wait before timeout in seconds
     * 	defaults to 0.5 s.
     */
    void EnableTimeout(float timeout = 0.5);

    /** This command will clear all current commands from the history if overwrite is
     * set to true.
     *
     * \param[in] filename The filename for the command history.
     * \param[in] overwrite Flag indicating the current commands should be forgotten.
     */
    void SetCommandHistory(std::string filename, bool overwrite = false);

    /// Set the command prompt
    void SetPrompt(const char* input_);

    /// Force a character to the output screen
    void putch(const char input_);

    /// Disrupt ncurses while boolean is true
    void pause(bool& flag);

    /// Dump all text in the stream to the output screen
    void flush();

    /// Print a command to the terminal output.
    void PrintCommand(const std::string& cmd_);

    /// Wait for the user to input a command
    std::string GetCommand(std::string& args, const int& prev_cmd_return_ = 0);

    /// Close the window and restore control to the terminal
    void Close();

    /// Clear's the current cmd line in the poll2 prompt. (This is a wrapper of the internal clear_() command, we probably should reimplement it rather than just wrapping a private member function. )
    void ClearCmd();

private:
    std::map<std::string, int> attrMap;
    std::streambuf* pbuf, * original;
    std::stringstream stream;
    std::string historyFilename_;
    WINDOW* main;
    WINDOW* output_window;
    WINDOW* input_window;
    WINDOW* status_window;
    CommandHolder commands;
    std::string cmd;
    bool init;
    int cursX, cursY;
    int offset;
    int _winSizeX, _winSizeY;
    int _statusWindowSize;
    std::vector<std::string> statusStr;
    std::deque<std::string> cmd_queue; /// The queue of commands read from a command script.
    ///The prompt string.
    std::string prompt;
    ///The tab complete flag
    bool enableTabComplete;
    float commandTimeout_; ///<Time in seconds to wait for command.
    bool insertMode_;

    short tabCount;
    bool debug_; ///<Flag indicating verbose output is enabled.

    std::ofstream logFile;

    bool from_script; /// Set to true if a command is read from a script instead of user input.
    bool prompt_user; /// Set to true if the user should be prompted with a yes/no question.

    /// Size of the scroll back buffer in lines.
    int _scrollbackBufferSize;

    /// Number of lines scrolled back
    int _scrollPosition;

    /**Refreshes the specified window or if none specified all windows.
     *
     *\param[in] window The pointer to the window to be updated.
     */
    void refresh_();

    /// Resize the terminal
    void resize_();

    /// Scroll the output by a specified number of lines.
    void scroll_(int numLines);

    /// Update the positions of the physical and logical cursors
    void update_cursor_();

    /// Clear the command prompt output
    void clear_();

    /// Force a character to the input screen
    void in_char_(const char input_);

    /// Force a character string to the input screen
    void in_print_(const char* input_);

    /// Initialize terminal colors
    void init_colors_();

    /// Read commands from a command script.
    /// An example CTerminal script is given below. Comments are denoted by a #.
    /// ```
    /// # Tell the user something about this script.
    /// .echo This script is intended to be used to test the script reader (i.e. '.cmd').
    ///
    /// # Issue the user a prompt asking if they would like to continue.
    /// # If the user types anything other than 'yes' or 'y', the script will abort.
    /// .prompt WARNING! This script will do something. Are you sure you wish to proceed?
    ///
    /// help # Do something just to test that the script is working.
    /// ```
    /// \param[in] filename_ : The relative path to the file containing CTerminal commands.
    /// \returns true if the file opened successfully and false otherwise.
    bool LoadCommandFile(const char* filename_);

    /// Load a list of previous commands from a file
    bool LoadCommandHistory(bool overwrite);

    /// Save previous commands to a file
    bool SaveCommandHistory();

    /// Force a character string to the output screen
    void print(WINDOW* window, std::string input_);

    /**Split strings into multiple commands separated by ';'.
     *
     * \param[in] input_ The string to be parsed.
     * \param[out] cmds The vector to populate with sub-commands.
     */
    void split_commands(const std::string& input_, std::deque<std::string>& cmds);

    /// Print the command prompt to the screen.
    void PrintPrompt();
};

/**Split a string on the delimiter character populating the vector args with
 * any substrings formed. Returns the number of substrings found.
 *
 * \param[in] str The string to be parsed.
 * \param[out] args The vector to populate with substrings.
 * \param[in] delimiter The character to split the string on.
 * \return The number of substrings found.
 */
unsigned int split_str(std::string str, std::vector<std::string>& args,
                       char delimiter = ' ');

#endif
