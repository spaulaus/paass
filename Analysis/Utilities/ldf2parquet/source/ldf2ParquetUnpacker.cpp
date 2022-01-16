///@file Ldf2ParquetUnpacker.cpp
///@brief

#include "Ldf2ParquetUnpacker.hpp"
#include "XiaData.hpp"

///Process all events in the event list.
void Ldf2ParquetUnpacker::ProcessRawEvent() {
    XiaData *current_event = NULL;

    // Fill the processor event deques with events
    while (!rawEvent.empty()) {
        current_event = rawEvent.front();
        rawEvent.pop_front(); // Remove this event from the raw event deque.

        // Check that this channel event exists.
        if (!current_event)
            continue;

        //Adds the event to some sort of tracking.
        AddEvent(current_event);
    }
    //Process the event now that the event deque is built
    ProcessEvents();
}

/** Add a channel event to the deque of events to send to the processors.
  * This method should only be called from Ldf2ParquetUnpacker::ProcessRawEvent().
  * \param[in]  event The raw XiaData to add to the channel event deque.
  * \return False if the event pointer was invalid.
  */
bool Ldf2ParquetUnpacker::AddEvent(XiaData *event) {
    if (!event)
        return false;


    // Handle the individual XiaData. Maybe add it to a detector's event list or something.
    // Do nothing with it for now.
    delete event;

    return false;
}

///Process all channel events read in from the rawEvent.
///@return False.
bool Ldf2ParquetUnpacker::ProcessEvents() {
    // Really we're going to do nothing for processing.
    return false;
}