///@file Ldf2ParquetUnpacker.hpp
///@brief

#ifndef PAASS_Ldf2ParquetUNPACKER_HPP
#define PAASS_Ldf2ParquetUNPACKER_HPP

#include "Unpacker.hpp"

///Class that handles data unpacking for the Ldf2Parquet program.
class Ldf2ParquetUnpacker : public Unpacker {
public:
    /// Default constructor.
    Ldf2ParquetUnpacker() : Unpacker() {}

    /// Destructor.
    ~Ldf2ParquetUnpacker() {}

private:
    ///Process all events in the event list.
    void ProcessRawEvent();

    ///Process all channel events read in from the rawEvent.
    /// @return False.
    bool ProcessEvents();
};

#endif //PAASS_Ldf2ParquetUNPACKER_HPP
