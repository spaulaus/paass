///@file Ldf2ParquetUnpacker.cpp
///@brief
#include "Ldf2ParquetUnpacker.hpp"

#include <arrow/csv/api.h>
#include <arrow/io/api.h>
#include <arrow/ipc/api.h>
#include <arrow/pretty_print.h>
#include <arrow/result.h>
#include <arrow/status.h>
#include <arrow/table.h>

#include <pixie/data/list_mode.hpp>

//Process all events in the event list.
void Ldf2ParquetUnpacker::ProcessRawEvent() {
//    ARROW_ASSIGN_OR_RAISE(auto output_file,
//                          arrow::io::FileOutputStream::Open("test.parquet"));

    while (!rawEvent.empty()) {
        auto current_event = rawEvent.front();
        rawEvent.pop_front(); // Remove this event from the raw event deque.
//        std::cout << current_event << std::endl;
    }
}

///Process all channel events read in from the rawEvent.
///@return False.
bool Ldf2ParquetUnpacker::ProcessEvents() {
    // Really we're going to do nothing for processing.
    return false;
}