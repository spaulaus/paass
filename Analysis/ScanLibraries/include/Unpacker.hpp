/** \file Unpacker.hpp
 * \brief A class to handle the unpacking of UTK/ORNL style pixie16 data spills.
 *
 * This class is intended to be used as a replacement of pixiestd.cpp from Stan
 * Paulauskas's pixie_scan. The majority of function names and arguments are
 * preserved as much as possible while allowing for more standardized unpacking
 * of pixie16 data.
 * CRT
 *
 * \author C. R. Thornsberry, S. V. Paulauskas
 * \date Feb. 12th, 2016
 */
#ifndef UNPACKER_HPP
#define UNPACKER_HPP

#include <deque>
#include <map>
#include <string>
#include <vector>

#include <pixie/data/list_mode.hpp>

namespace paass::unpacker {
struct module_data {
    module_data(size_t firmware, size_t frequency) : revision(firmware), frequency(frequency) {}
    module_data(const module_data& ref) : revision(ref.revision), frequency(ref.frequency) {}

    size_t revision;
    size_t frequency;
    std::deque<xia::pixie::data::list_mode::record> recs;
    xia::pixie::data::list_mode::buffer buf;
};

using modules_data = std::map<size_t, module_data>;
}


class Unpacker {
public:
    /// Default constructor.
    Unpacker() : debug_mode(false), eventWidth_(100e-6), running(true),
                 numRawEvt(0), // Count of raw events read from file.
                 firstTime(0) {}

    /// Destructor.
    virtual ~Unpacker() {
        rawEvent.clear();
        modulesData.clear();
    }

    double eventWidth_; ///< The width of the raw event in seconds
    bool debug_mode; ///< True if debug mode is set.
    std::deque<xia::pixie::data::list_mode::record> rawEvent; ///< A deque containing of all events in the event window.

    /// Return the number of raw events read from the file.
    unsigned int GetNumRawEvents() { return numRawEvt; }

    /// Return the time of the first fired channel event.
    double GetFirstTime() { return firstTime.count(); }

    /// Return true if the scan is running and false otherwise.
    bool IsRunning() { return running; }

    void InitializeDataMask(size_t module_number, size_t firmware, size_t frequency);

    void InitializeDataMask(const std::string& xml_config_file);

    /** ReadSpill is responsible for constructing a list of pixie16 events from
      * a raw data spill. This method performs sanity checks on the spill and
      * calls ReadBuffer in order to construct the event list.
      * \param[in]  data       Pointer to an array of unsigned ints containing the spill data.
      * \param[in]  nWords     The number of words in the array.
      * \param[in]  is_verbose Toggle the verbosity flag on/off.
      * \return True if the spill was read successfully and false otherwise.
      */
    bool ReadSpill(unsigned int* data, unsigned int nWords, bool is_verbose = true);

    /** Stop the scan. Unused by default.
      * \return Nothing.
      */
    void Stop() { running = false; }

    /** Run the scan. Unused by default.
      * \return Nothing.
      */
    void Run() { running = true; }

protected:
    unsigned int maxModuleNumberInFile_; ///< The maximum module number that we've encountered in the data file.
    bool running; ///< True if the scan is running.
    paass::unpacker::modules_data modulesData;

    virtual void ProcessRawRecords() {
        BuildRawEvent();
        ProcessRawEvent();
    }

    /** Process all events in the event list.
      * \param[in]  addr_ Pointer to a ScanInterface object. Unused by default.
      * \return Nothing.
      */
    virtual void ProcessRawEvent() { rawEvent.clear(); }

    /** Add an event to generic statistics output.
      * \param[in]  event_ Pointer to the current XIA event. Unused by default.
      * \param[in]  addr_  Pointer to a ScanInterface object. Unused by default.
      * \return Nothing.
      */
    virtual void RawStats(const xia::pixie::data::list_mode::record& rec) {}

    /** Called form ReadSpill. Scan the current spill and construct a list of
      * events which fired by obtaining the module, channel, trace, etc. of the
      * timestamped event. This method will construct the event list for
      * later processing.
      * \param[in]  buf    Pointer to an array of unsigned ints containing raw buffer data.
      * \param[out] bufLen The number of words in the buffer.
      * \return The number of records read from the buffer.
      */
    int ReadBuffer(paass::unpacker::module_data& moduleData);

private:
    unsigned int numRawEvt; /// The total count of raw events read from file.

    xia::pixie::data::list_mode::record::time_type firstTime; /// The first recorded event time.

    /** Scan the time sorted event list and package the events into a raw
      * event with a size governed by the event width.
      * \return True if the event list is not empty and false otherwise.
      */
    void BuildRawEvent();
};

#endif
