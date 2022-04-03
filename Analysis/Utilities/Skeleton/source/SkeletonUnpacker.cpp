///@file SkeletonUnpacker.cpp
///@brief
///@author C. R. Thornsberry, S. V. Paulauskas
///@date May 14, 2017

#include "SkeletonUnpacker.hpp"

void SkeletonUnpacker::ProcessRawEvent() {
    // Fill the processor event deques with events
    while (!rawEvent.empty()) {
        auto current_event = rawEvent.front();

        //Do something interesting with the events here.

        rawEvent.pop_front(); // Remove this event from the raw event deque.
    }
    //Process the event now that the event deque is built
    ProcessEvents();
}

///Process all channel events read in from the rawEvent.
///@return False.
bool SkeletonUnpacker::ProcessEvents() {
    // Really we're going to do nothing for processing.
    return false;
}