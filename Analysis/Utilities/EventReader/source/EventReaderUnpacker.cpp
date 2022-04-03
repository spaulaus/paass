///@file EventReaderUnpacker.cpp
///@brief Derived class to handle unpacking of events for EventReader
///@authors S. V. Paulauskas and C. R. Thornsberry
///@date June 8, 2017

#include <iostream>
#include <thread>

#include "EventReaderUnpacker.hpp"

/** Process all events in the event list.
  * \param[in]  addr_ Pointer to a location in memory.
  * \return Nothing.
  */
void EventReaderUnpacker::ProcessRawEvent() {
    // Fill the processor event deques with events
    while (!rawEvent.empty()) {
        if (!running)
            break;

        auto current_event = rawEvent.front();
        rawEvent.pop_front(); // Remove this event from the raw event deque.

        // Send the event to the scan interface object for processing.
        AddEvent(current_event);
    }
}

void EventReaderUnpacker::displayBool(const char* msg_, const bool& val_) {
    if (val_) std::cout << msg_ << "YES\n";
    else std::cout << msg_ << "NO\n";
}

/** Add a channel event to the deque of events to send to the processors.
  * This method should only be called from readerUnpacker::ProcessRawEvent().
  * \param[in]  event_ The raw XiaData to add to the channel event deque.
  * \return False.
  */
bool EventReaderUnpacker::AddEvent(xia::pixie::data::list_mode::record& event_) {
    if (numSkip_ == 0) {
        std::cout << "*************************************************\n";
        std::cout << "** Raw Event no. " << ++eventsRead_ << std::endl;
        std::cout << "*************************************************\n";
        std::cout << " Filter Energy: " << event_.energy << std::endl;
        std::cout << " Trigger Time:  " << event_.time.count() << std::endl;
        std::cout << " Slot:          " << event_.slot_id << std::endl;
        std::cout << " Channel:       " << event_.channel_number << std::endl;
        std::cout << " CFD Time:      " << event_.cfd_fractional_time.count() << std::endl;
        std::cout << " CFD Trig Src   " << event_.cfd_trigger_source << std::endl;
        std::cout << " Trace Length:  " << event_.trace_length << std::endl;

        if (showFlags_) {
            displayBool(" Pileup:        ", event_.finish_code);
            displayBool(" Saturated:     ", event_.trace_out_of_range);
            displayBool(" CFD Force:     ", event_.cfd_forced_trigger);
        }

        if (showTrace_ && !event_.trace.empty()) {
            int numLine = 0;
            std::cout << " Trace:\n  ";
            for (const auto& val: event_.trace) {
                std::cout << val << "\t";
                if (++numLine % 10 == 0) std::cout << "\n  ";
            }
            std::cout << std::endl;
        }

        std::cout << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    } else {
        numSkip_--;
    }

    return false;
}