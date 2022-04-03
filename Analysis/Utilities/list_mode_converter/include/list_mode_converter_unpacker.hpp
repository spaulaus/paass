///@file list_mode_converter_unpacker.hpp
///@brief Outputs list-mode records to various data formats that *aren't* proprietary like LDF or PLD.

#ifndef PAASS_LIST_MODE_CONVERTER_UNPACKER_HPP
#define PAASS_LIST_MODE_CONVERTER_UNPACKER_HPP

#include <fstream>

#include "Unpacker.hpp"

///Class that handles data unpacking for the Ldf2Parquet program.
class list_mode_converter_unpacker : public Unpacker {
public:
    std::ofstream outfile;
    std::string outfile_extension;

    /// Default constructor.
    list_mode_converter_unpacker() : Unpacker() {}

    /// Destructor.
    ~list_mode_converter_unpacker() override {
        if (outfile.is_open())
            outfile.close();
    }

private:
    /**
     * @brief Processes the records decoded from the list-mode data file without any event building.
     */
    void ProcessRecords() override;
};

#endif //PAASS_LIST_MODE_CONVERTER_UNPACKER_HPP
