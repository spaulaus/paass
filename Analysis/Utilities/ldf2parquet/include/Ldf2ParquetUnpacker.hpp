///@file Ldf2ParquetUnpacker.hpp
///@brief

#ifndef PAASS_Ldf2ParquetUNPACKER_HPP
#define PAASS_Ldf2ParquetUNPACKER_HPP

#include <fstream>

#include "Unpacker.hpp"

///Class that handles data unpacking for the Ldf2Parquet program.
class Ldf2ParquetUnpacker : public Unpacker {
public:
    std::ofstream outfile;
    std::string outfile_extension;

    /// Default constructor.
    Ldf2ParquetUnpacker() : Unpacker() {}

    /// Destructor.
    ~Ldf2ParquetUnpacker() override {
        if (outfile.is_open())
            outfile.close();
    }

private:

    /**
     * @brief Processes the records decoded from the list-mode data file without any event building.
     */
    void ProcessRecords() override;

};

#endif //PAASS_Ldf2ParquetUNPACKER_HPP
