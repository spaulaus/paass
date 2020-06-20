///@file Ldf2ParquetUnpacker.hpp
///@brief
///@author S. V. Paulauskas
///@date June 13, 2020

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

    ///Add an event to generic statistics output.
    ///@param[in]  event_ Pointer to the current XIA event.
    ///@param[in]  addr_  Pointer to a ScanInterface object.
    void RawStats(XiaData *event_) {}

    ///Add a channel event to the deque of events to send to the processors.
    /// This method should only be called from Ldf2ParquetUnpacker::ProcessRawEvent().
    /// @param[in]  event_ The raw XiaData to add to the channel event deque.
    /// @return False.
    bool AddEvent(XiaData *event_);

    ///Process all channel events read in from the rawEvent.
    /// @return False.
    bool ProcessEvents();
};

#endif //PAASS_Ldf2ParquetUNPACKER_HPP
