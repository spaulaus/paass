///@file ldf2parquet.cpp
///@brief The main program for the Ldf2Parquet conversion program
#include <iostream>

#include "list_mode_converter_interface.hpp"
#include "list_mode_converter_unpacker.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    list_mode_converter_unpacker unpacker;
    list_mode_converter_interface scanner;

    try {
        // Set the output message prefix.
        scanner.SetProgramName("list_mode_converter");

        // Initialize the scanner.
        scanner.Setup(argc, argv, &unpacker);
    } catch (invalid_argument &invalidArgument) {
        cout << invalidArgument.what() << endl;
        return 1;
    }

    // Run the main loop.
    int retval = scanner.Execute();

    scanner.Close();

    return retval;
}