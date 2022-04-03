///@file Ldf2ParquetUnpacker.cpp
///@brief
#include "list_mode_converter_unpacker.hpp"

#include <arrow/csv/api.h>
#include <arrow/io/api.h>
#include <arrow/ipc/api.h>
#include <arrow/pretty_print.h>
#include <arrow/result.h>
#include <arrow/status.h>
#include <arrow/table.h>

#include <pixie/data/list_mode.hpp>


void list_mode_converter_unpacker::ProcessRecords() {
//    ARROW_ASSIGN_OR_RAISE(auto output_file,
//                          arrow::io::FileOutputStream::Open("test.parquet"));
    if (outfile_extension == "jsonl") {
        std::string writebuf;
        for (auto& mod: modulesData) {
            auto recs = mod.second.recs;
            while (!recs.empty()) {
                writebuf += xia::pixie::data::list_mode::record_to_json(recs.front()) + "\n";
                recs.pop_front();
            }
        }
        outfile.write(writebuf.c_str(), writebuf.size());
    } else {
        throw std::invalid_argument(
        "list_mode_converter_unpacker::ProcessRecords() - Unknown filetype (" + outfile_extension + ")!");
    }
}