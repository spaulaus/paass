///@file SkeletonUnpacker.hpp
///@brief
///@author C. R. Thornsberry, S. V. Paulauskas
///@date May 14, 2017

#ifndef PAASS_SKELETONUNPACKER_HPP
#define PAASS_SKELETONUNPACKER_HPP

#include "Unpacker.hpp"

///Class that handles data unpacking for the skeleton program.
class SkeletonUnpacker : public Unpacker {
public:
    /// Default constructor.
    SkeletonUnpacker() : Unpacker() {}

    /// Destructor.
    ~SkeletonUnpacker() {}

private:
    ///Process all events in the event list.
    void ProcessRawEvent();

    ///Add an event to generic statistics output.
    ///@param[in]  event_ Pointer to the current XIA event.
    ///@param[in]  addr_  Pointer to a ScanInterface object.
    void RawStats(xia::pixie::data::list_mode::record& event_) {}

    ///Process all channel events read in from the rawEvent.
    /// @return False.
    bool ProcessEvents();
};

#endif //PAASS_SKELETONUNPACKER_HPP
