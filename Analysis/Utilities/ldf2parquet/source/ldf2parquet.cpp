///@file ldf2parquet.cpp
///@brief The main program for the Ldf2Parquet conversion program
#include <iostream>

#include "Ldf2ParquetInterface.hpp"
#include "Ldf2ParquetUnpacker.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    Ldf2ParquetUnpacker unpacker;
    Ldf2ParquetInterface scanner;

    try {
        // Set the output message prefix.
        scanner.SetProgramName("ldf2parquet");

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