///@file list_mode_converter_unpacker.cpp
///@brief Outputs list-mode records to various data formats that *aren't* proprietary like LDF or PLD.

//#include <arrow/csv/api.h>
//#include <arrow/io/api.h>
//#include <arrow/ipc/api.h>
//#include <arrow/pretty_print.h>
//#include <arrow/result.h>
//#include <arrow/status.h>
//#include <arrow/table.h>
#include <pixie/data/list_mode.hpp>

#include "list_mode_converter_unpacker.hpp"

void list_mode_converter_unpacker::ProcessRecords() {
    if (outfile_extension == "jsonl") {
        std::string writebuf;
        for (auto& mod: modulesData) {
            for (const auto& rec: mod.second.recs) {
                writebuf += xia::pixie::data::list_mode::record_to_json(rec) + "\n";
            }
            mod.second.recs.clear();
        }
        outfile.write(writebuf.c_str(), static_cast<std::streamsize>(writebuf.size()));
    } else if (outfile_extension == "parquet") {
//    ARROW_ASSIGN_OR_RAISE(auto output_file,
//                          arrow::io::FileOutputStream::Open("test.parquet"));
        std::cout << "list_mode_converter_unpacker::ProcessRecords() - Parquet output not implemented yet!"
                  << std::endl;
    } else if (outfile_extension == "csv") {
        std::cout << "list_mode_converter_unpacker::ProcessRecords() - CSV output not implemented yet!"
                  << std::endl;
    } else {
        throw std::invalid_argument(
        "list_mode_converter_unpacker::ProcessRecords() - Unknown filetype (" + outfile_extension + ")!");
    }
}