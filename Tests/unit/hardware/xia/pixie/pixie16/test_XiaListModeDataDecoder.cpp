///@file unittest-XiaListModeDataDecoder.cpp
///@brief Unit tests for the XiaListModeDataDecoder class
///@author S. V. Paulauskas
///@date December 25, 2016
#include "XiaListModeDataDecoder.hpp"

#include "HelperEnumerations.hpp"
#include "UnitTestSampleData.hpp"
#include "doctest.h"

#include <stdexcept>

using namespace std;
using namespace DataProcessing;
using namespace unittest_encoded_data;
using namespace unittest_decoded_data;

///@TODO These need to be expanded so that we cover all of the nine different firmware and frequency combinations.
TEST_SUITE ("Analysis/Scan Libraries/XiaListModeDataDecoder") {
    static const XiaListModeDataMask mask(R30474, 250);
    using namespace unittest_encoded_data::R30474_250;

    TEST_CASE_FIXTURE (XiaListModeDataDecoder, "BufferLengthChecks") {
        CHECK_THROWS_AS(DecodeBuffer(&empty_buffer[0], mask), length_error);
        CHECK(empty_buffer[1] == DecodeBuffer(&empty_module_buffer[0], mask).size());
    }

    TEST_CASE_FIXTURE (XiaListModeDataDecoder, "HeaderDecoding") {
        CHECK((unsigned int) 0 == DecodeBuffer(&header_w_bad_headerlen[0], mask).size());

        XiaData result_data = *(DecodeBuffer(&header[0], mask).front());
        CHECK(slotId == result_data.GetSlotNumber());
        CHECK(channelNumber == result_data.GetChannelNumber());
        CHECK(energy == result_data.GetEnergy());
        CHECK(ts_high == result_data.GetEventTimeHigh());
        CHECK(ts_low == result_data.GetEventTimeLow());
        CHECK(unittest_decoded_data::R30474_250::ts  == result_data.GetTime());
    }

    TEST_CASE_FIXTURE (XiaListModeDataDecoder, "ExternalTimestampDecoding") {
        XiaData result = *(DecodeBuffer(&headerWithExternalTimestamp[0], mask).front());
        CHECK(unittest_decoded_data::ex_ts_low == result.GetExternalTimeLow());
        CHECK(unittest_decoded_data::ex_ts_high == result.GetExternalTimeHigh());
    }

    TEST_CASE_FIXTURE (XiaListModeDataDecoder, "EsumsDecoding") {
        XiaData result = *(DecodeBuffer(&headerWithEnergySums[0], mask).front());
        CHECK(unittest_decoded_data::energy_sums == result.GetEnergySums());
        CHECK(unittest_decoded_data::filterBaseline == doctest::Approx(result.GetFilterBaseline()).epsilon(1e-4));
    }

    TEST_CASE_FIXTURE (XiaListModeDataDecoder, "EsumsAndExternalTsDecoding") {
        XiaData result = *(DecodeBuffer(&headerWithEnergySumsExternalTimestamp[0], mask).front());
        CHECK(unittest_decoded_data::energy_sums == result.GetEnergySums());
        CHECK(unittest_decoded_data::filterBaseline == doctest::Approx(result.GetFilterBaseline()).epsilon(1e-4));

        CHECK(unittest_decoded_data::ex_ts_low == result.GetExternalTimeLow());
        CHECK(unittest_decoded_data::ex_ts_high == result.GetExternalTimeHigh());
    }

    TEST_CASE_FIXTURE (XiaListModeDataDecoder, "QdcDecoding") {
        XiaData result = *(DecodeBuffer(&headerWithQdc[0], mask).front());
        CHECK(qdc == result.GetQdc());
    }

    TEST_CASE_FIXTURE (XiaListModeDataDecoder, "QdcAndExternalTsDecoding") {
        XiaData result = *(DecodeBuffer(&headerWithQdcExternalTimestamp[0], mask).front());
        CHECK(qdc == result.GetQdc());
        CHECK(unittest_decoded_data::ex_ts_low == result.GetExternalTimeLow());
        CHECK(unittest_decoded_data::ex_ts_high == result.GetExternalTimeHigh());
    }

    TEST_CASE_FIXTURE (XiaListModeDataDecoder, "EsumsAndQdcDecoding") {
        XiaData result = *(DecodeBuffer(&headerWithEnergySumsQdc[0], mask).front());
        CHECK(unittest_decoded_data::energy_sums == result.GetEnergySums());
        CHECK(unittest_decoded_data::filterBaseline == doctest::Approx(result.GetFilterBaseline()).epsilon(1e-4));
        CHECK(qdc == result.GetQdc());
    }

    TEST_CASE_FIXTURE (XiaListModeDataDecoder, "EsumsAndQdcAndExTsDecoding") {
        XiaData result = *(DecodeBuffer(&headerWithEnergySumsQdcExternalTimestamp[0], mask).front());
        CHECK(unittest_decoded_data::energy_sums == result.GetEnergySums());
        CHECK(unittest_decoded_data::filterBaseline == doctest::Approx(result.GetFilterBaseline()).epsilon(1e-4));
        CHECK(qdc == result.GetQdc());
        CHECK(unittest_decoded_data::ex_ts_low == result.GetExternalTimeLow());
        CHECK(unittest_decoded_data::ex_ts_high == result.GetExternalTimeHigh());
    }

    TEST_CASE_FIXTURE (XiaListModeDataDecoder, "TraceDecoding") {
        CHECK((unsigned int) 0 == DecodeBuffer(&header_w_bad_eventlen[0], mask).size());

        XiaData result = *(DecodeBuffer(&headerWithTrace[0], mask).front());
        CHECK(unittest_trace_variables::trace == result.GetTrace());
    }

    TEST_CASE_FIXTURE (XiaListModeDataDecoder, "CfdTimeCalculation") {
        XiaData result = *(DecodeBuffer(&headerWithCfd[0], mask).front());
        CHECK(cfd_fractional_time == result.GetCfdFractionalTime());
        CHECK(unittest_decoded_data::R30474_250::ts_w_cfd == doctest::Approx(result.GetTime()).epsilon(1e-5));
    }
}