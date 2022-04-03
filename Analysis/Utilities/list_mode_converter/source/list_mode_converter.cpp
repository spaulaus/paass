/// @file list_mode_converter.cpp
/// @brief The main program for converting ldfs and plds to more usable formats.
#include <iostream>
#include <stdexcept>

#include "list_mode_converter_interface.hpp"
#include "list_mode_converter_unpacker.hpp"

int main(int argc, char* argv[]) {
    list_mode_converter_unpacker unpacker;
    list_mode_converter_interface scanner;

    try {
        scanner.SetProgramName("list_mode_converter");
        scanner.Setup(argc, argv, &unpacker);
    } catch (std::invalid_argument& invalidArgument) {
        std::cout << invalidArgument.what() << std::endl;
        return EXIT_FAILURE;
    }

    scanner.Execute();
    scanner.Close();

    return EXIT_SUCCESS;
}