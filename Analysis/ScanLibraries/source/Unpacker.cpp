/** \file Unpacker.cpp
 * \brief A class to handle the unpacking of UTK/ORNL style pixie16 data spills.
 *
 * This class is intended to be used as a replacement of PixieStd.cpp from
 * pixie_scan. The majority of function names and arguments are
 * preserved as much as possible while allowing for more standardized unpacking
 * of pixie16 data.
 */
#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <limits>

#include <pixie/pixie16/hw.hpp>

#include "PaassExceptions.hpp"
#include "Unpacker.hpp"
#include "XiaData.hpp"
#include "XmlInterface.hpp"

using namespace std;

/** Scan the time sorted event list and package the events into a raw
  * event with a size governed by the event width.
  * \return True if the event list is not empty and false otherwise.
  */
void Unpacker::BuildRawEvent() {
    if (!rawEvent.empty())
        rawEvent.clear();

    if (numRawEvt == 0) {
        // This is the first rawEvent, so we need to find the first time recorded by the modules.
        xia::pixie::data::list_mode::record::time_type time(std::numeric_limits<double>::max());
        for (const auto& mod: modulesData) {
            if (mod.second.recs.begin()->time < time) {
                time = mod.second.recs.begin()->time;
            }
        }
        firstTime = time;
        std::cout << "BuildRawEvent: First event time is " << std::to_string(firstTime.count()) << " s.\n";
    }

    auto start = firstTime + xia::pixie::data::list_mode::record::time_type(numRawEvt * eventWidth_);

    // Loop over all time-sorted modules.
    for (auto& mod: modulesData) {
        auto recs = mod.second.recs;
        if (recs.empty())
            continue;

        auto last_rec = recs.begin();
        for (auto& rec: recs) {
            auto currtime = rec.time;
            /*
             * In the event of a backward time skip, we remove the offending event from the deque without
             * adding it to the event lists.
             */
            if (currtime < start) {
                cerr << "BuildRawEvent: Detected backwards time-skip from start=" << std::to_string(start.count())
                     << " to " << std::to_string(currtime.count()) << "?\n";
                recs.pop_front();
                continue;
            }

            // If the time difference between the current and previous event is
            // larger than the event width, finalize the current event, otherwise
            // treat this as part of the current event
            if ((currtime - start).count() > eventWidth_)
                break;

            // Update raw stats output with the new event before adding it to the raw event.
            RawStats(rec);

            // Push this channel event into the rawEvent.
            rawEvent.push_back(rec);
            recs.pop_front();
        }
    }
    numRawEvt++;
}

void Unpacker::ProcessRawEvent() {
    rawEvent.clear();
}

///Called form ReadSpill. Scan the current spill and construct a list of events which fired by obtaining the module,
/// channel, trace, etc. of the timestamped event. This method will construct the event list for later processing.
///@param[in] buf : Pointer to an array of unsigned ints containing raw buffer data.
///@return The number of XiaDatas read from the buffer.
int Unpacker::ReadBuffer(paass::unpacker::module_data& moduleData) {
    xia::pixie::data::list_mode::records recs;
    xia::pixie::data::list_mode::buffer remainder;

    xia::pixie::data::list_mode::decode_data_block(moduleData.buf, moduleData.revision,
                                                   moduleData.frequency, recs, remainder);
    moduleData.buf = remainder;
    std::sort(recs.begin(), recs.end());
    moduleData.recs.insert(moduleData.recs.end(), recs.begin(), recs.end());
    return int(recs.size());
}

Unpacker::Unpacker() : debug_mode(false), eventWidth_(100e-6), running(true),
                       TOTALREAD(1000000), // Maximum number of data words to read.
                       numRawEvt(0), // Count of raw events read from file.
                       firstTime(0) {}

Unpacker::~Unpacker() {
    rawEvent.clear();
    modulesData.clear();
}

void Unpacker::InitializeDataMask(size_t module_number, size_t firmware, size_t frequency) {
    modulesData.insert(make_pair(module_number, paass::unpacker::module_data(firmware, frequency)));
}

void Unpacker::InitializeDataMask(const std::string& xml_config_file) {
    unsigned int modCounter = 0;
    auto node = XmlInterface::get(xml_config_file)->GetDocument()->child("Configuration").child("Map");
    auto globalFreq_ = node.attribute("frequency").as_uint(0);
    auto globalFirm_ = node.attribute("firmware").as_uint(0);

    for (auto it = node.begin(); it != node.end(); ++it, modCounter++) {
        if (it->attribute("number").empty())
            throw IOException("Unpacker::InitializeDataMask - Unable to read the \"number\" attribute "
                              "from the module in position #" + to_string(modCounter) + "(0 counting)");
        if (it->attribute("firmware").empty() && globalFirm_ == 0)
            throw IOException("Unpacker::InitializeDataMask - Unable to read the \"firmware\" attribute from"
                              " the /Configuration/Map/Module/" + to_string(modCounter) +
                              " and the Global default is not set");
        if (it->attribute("frequency").empty() && globalFreq_ == 0)
            throw IOException("Unpacker::InitializeDataMask - Unable to read the \"frequency\" attribute from"
                              " the /Configuration/Map/Module/" + to_string(modCounter) +
                              " and the Global default is not set");

        modulesData.insert(make_pair(it->attribute("number").as_uint(),
                                     paass::unpacker::module_data(it->attribute("firmware").as_uint(globalFirm_),
                                                                  it->attribute("frequency").as_uint(globalFreq_))
        ));
    }
}

/** ReadSpill is responsible for constructing a list of pixie16 events from
  * a raw data spill. This method performs sanity checks on the spill and
  * calls ReadBuffer in order to construct the event list.
  * \param[in]  data       Pointer to an array of unsigned ints containing the spill data.
  * \param[in]  nWords     The number of words in the array.
  * \param[in]  is_verbose Toggle the verbosity flag on/off.
  * \return True if the spill was read successfully and false otherwise.
  */
bool Unpacker::ReadSpill(unsigned int* data, unsigned int nWords, bool is_verbose/*=true*/) {
    static constexpr unsigned int maxVsn = 14; // No more than 14 pixie modules per crate
    static int counter = 0; // the number of times this function is called
    static int evCount = 0;     // the number of times data is passed to ScanList

    unsigned int nWords_read = 0;
    time_t theTime = 0;
    unsigned int lastVsn = 0xFFFFFFFF; // the last vsn read from the data

    if (counter == 0)
        maxModuleNumberInFile_ = 0;

    counter++;

    bool fullSpill = false; // True if spill had all vsn's
    size_t vsn = 0xFFFFFFFF;

    while (nWords_read < nWords) {
        while (data[nWords_read] == 0xFFFFFFFF) // Search for the next non-delimiter.
            nWords_read++;

        /*
         * The buffer length as reported in the file includes the following two elements. These elements are *not* part
         * of the XIA Pixie-16 List-Mode data and so the length needs to be reduced by 2.
         */
        auto total_spill_length = data[nWords_read++];
        auto xia_list_mode_buffer_length = total_spill_length - 2;
        vsn = data[nWords_read++];

        if (vsn > maxModuleNumberInFile_ && vsn != 9999 && vsn != 1000)
            maxModuleNumberInFile_ = vsn;

        // Check sanity of record length and vsn
        if (total_spill_length > xia::pixie::hw::fifo_size_words || (vsn > maxVsn && vsn != 9999 && vsn != 1000)) {
            if (is_verbose)
                cout << "ReadSpill: SANITY CHECK FAILED: lenRec = " << total_spill_length << ", vsn = " << vsn
                     << ", read " << nWords_read << " of " << nWords << endl;
            return false;
        }

        // If the record length is 6, this is an empty channel.
        // Skip this vsn and continue with the next
        ///@TODO Revision specific, so move to ReadBuffData
        if (total_spill_length == 6) {
            nWords_read += total_spill_length;
            lastVsn = vsn;
            continue;
        }

        // If both the current vsn inspected is within an acceptable range, begin reading the buffer.
        if (vsn < maxVsn) {
            if (lastVsn != 0xFFFFFFFF && vsn != lastVsn + 1) {
                if (is_verbose)
                    cout << "ReadSpill: MISSING BUFFER " << lastVsn + 1 << ", lastVsn = " << lastVsn << ", vsn = "
                         << vsn << ", lenrec = " << total_spill_length << endl;
                fullSpill = false;
            }

            auto mod = modulesData.find(vsn);
            if (mod == modulesData.end()) {
                std::cout << "Unpacker::ReadSpill - modulesData did not contain an entry for VSN = " << vsn
                          << "! Adding entry assuming same type as VSN = 0." << std::endl;
            }

            auto moduleData = mod->second;
            moduleData.buf.insert(moduleData.buf.end(), &data[nWords_read],
                                  &data[nWords_read + xia_list_mode_buffer_length]);
            ReadBuffer(moduleData);

            // Update the variables that are keeping track of what has been
            // analyzed and increment the location in the current buffer
            lastVsn = vsn;
            nWords_read += xia_list_mode_buffer_length;
        } else if (vsn == 1000) { // Buffer with vsn 1000 was inserted with the time for superheavy exp't
            memcpy(&theTime, &data[nWords_read + 2], sizeof(time_t));
            if (is_verbose) {
                /*struct tm * timeinfo;
                timeinfo = localtime (&theTime);
                cout << "ReadSpill: Read wall clock time of " << asctime(timeinfo);*/
            }
            nWords_read += total_spill_length;
            continue;
        } else if (vsn == 9999) {
            // 9999 is the end spill vsn and indicates that we've reached the end of our spill.
            continue;
        } else {
            // Bail out if we have lost our place,
            // (bad vsn) and process events
            cout << "ReadSpill: UNEXPECTED VSN " << vsn << endl;
            break;
        }
    } // while still have words

    if (nWords > TOTALREAD || nWords_read > TOTALREAD) {
        cout << "ReadSpill: Values of nn - " << nWords << " nk - " << nWords_read << " TOTALREAD - " << TOTALREAD
             << endl;
        return false;
    }

    // If the vsn is 9999 this is the end of a spill, signal this buffer
    // for processing and determine if the buffer is split between spills.
    if (vsn == 9999 || vsn == 1000) {
        fullSpill = true;
    }

    if (is_verbose && nWords_read != nWords)
        cout << "ReadSpill: Received spill of " << nWords << " words, but read " << nWords_read << " words\n";

    if (fullSpill) { // if full spill process events
        // Once the vector of pointers eventlist is sorted based on time,
        // begin the event processing in ScanList().
        // ScanList will also clear the event list for us.
        BuildRawEvent();
        ProcessRawEvent();

        evCount++;

        // Every once in a while (when evcount is a multiple of 1000)
        // print the time elapsed doing the analysis
        if ((evCount % 1000 == 0 || evCount == 1) && theTime != 0)
            cout << endl << "ReadSpill: Data read up to poll status time " << ctime(&theTime);
    } else {
        if (is_verbose)
            cout << "ReadSpill: Spill split between buffers" << endl;
        return false;
    }
    return true;
}
