///@file unittest-XiaListModeDataEncoder.cpp
///@brief Unit tests for the XiaListModeDataDecoder class
///@author S. V. Paulauskas
///@date December 25, 2016
#include "XiaListModeDataEncoder.hpp"
#include "UnitTestSampleData.hpp"

#include "doctest.h"

using namespace std;
using namespace DataProcessing;
using namespace unittest_encoded_data;
using namespace unittest_decoded_data;
using namespace unittest_encoded_data::R30474_250;

TEST_SUITE ("Analysis/Scan Libraries/XiaListModeDataEncoder") {
    void SetupXiaDataClass(XiaData &data) {
        data.Initialize();
        data.SetEnergy(energy);
        data.SetSlotNumber(slotId);
        data.SetChannelNumber(channelNumber);
        data.SetCrateNumber(crateId);
        data.SetEventTimeLow(ts_low);
        data.SetEventTimeHigh(ts_high);
    }

    void SetupEsums(XiaData &data) {
        data.SetFilterBaseline(unittest_decoded_data::filterBaseline);
        data.SetEnergySums(unittest_decoded_data::energy_sums);
    }

    void SetupExternalTimestamp(XiaData &data) {
        data.SetExternalTimeLow(unittest_decoded_data::ex_ts_low);
        data.SetExternalTimeHigh(unittest_decoded_data::ex_ts_high);
    }

    ///For now we use the same encoder for everybody since we're only testing one firmware/frequency combo.
    XiaListModeDataEncoder encoder(test_firmware, test_frequency);

    ///Everybody is going to use the same XiaData class we'll just initialize it each time.
    XiaData data;

    TEST_CASE ("TestConstructors") {
        XiaListModeDataEncoder encoder1(XiaListModeDataMask(test_firmware, test_frequency));
        XiaListModeDataEncoder encoder2(test_firmware, test_frequency);
    }

    TEST_CASE ("TestEmptyDataThrow") {
        CHECK_THROWS_AS(encoder.EncodeXiaData(XiaData()), invalid_argument);
    }

    TEST_CASE ("TestEncodingBasicHeader") {
        SetupXiaDataClass(data);
        CHECK(vector<unsigned int>(header.begin() + 2, header.end()) == encoder.EncodeXiaData(data));
    }

    TEST_CASE ("TestEncodingExternalTimestamps") {
        SetupXiaDataClass(data);
        SetupExternalTimestamp(data);
        CHECK(vector<unsigned int>(headerWithExternalTimestamp.begin() + 2, headerWithExternalTimestamp.end()) ==
              encoder.EncodeXiaData(data));
    }

    TEST_CASE ("TestEncodingEnergySums") {
        SetupXiaDataClass(data);
        SetupEsums(data);
        CHECK(vector<unsigned int>(headerWithEnergySums.begin() + 2, headerWithEnergySums.end()) ==
              encoder.EncodeXiaData(data));
    }

    TEST_CASE ("TestEncodingEnergySumsAndExternalTimeStamps") {
        SetupXiaDataClass(data);
        SetupEsums(data);
        SetupExternalTimestamp(data);
        CHECK(vector<unsigned int>(headerWithEnergySumsExternalTimestamp.begin() + 2,
                                   headerWithEnergySumsExternalTimestamp.end()) == encoder.EncodeXiaData(data));
    }

    TEST_CASE ("TestEncodingQdc") {
        SetupXiaDataClass(data);
        data.SetQdc(qdc);
        CHECK(vector<unsigned int>(headerWithQdc.begin() + 2, headerWithQdc.end()) == encoder.EncodeXiaData(data));
    }

    TEST_CASE ("TestEncodingQdcAndExternalTimestamp") {
        SetupXiaDataClass(data);
        data.SetQdc(qdc);
        SetupExternalTimestamp(data);
        CHECK(vector<unsigned int>(headerWithQdcExternalTimestamp.begin() + 2, headerWithQdcExternalTimestamp.end()) ==
              encoder.EncodeXiaData(data));
    }

    TEST_CASE ("TestEncodingEnergySumsAndQdc") {
        SetupXiaDataClass(data);
        SetupEsums(data);
        data.SetQdc(qdc);
        CHECK(vector<unsigned int>(headerWithEnergySumsQdc.begin() + 2, headerWithEnergySumsQdc.end()) ==
              encoder.EncodeXiaData(data));
    }

    TEST_CASE ("TestEncodingEnergySumsAndQdcAndTimestamp") {
        SetupXiaDataClass(data);
        SetupEsums(data);
        data.SetQdc(qdc);
        SetupExternalTimestamp(data);
        CHECK(vector<unsigned int>(headerWithEnergySumsQdcExternalTimestamp.begin() + 2,
                                   headerWithEnergySumsQdcExternalTimestamp.end()) == encoder.EncodeXiaData(data));
    }

    TEST_CASE ("TestEncodingTrace") {
        SetupXiaDataClass(data);
        data.SetTrace(unittest_trace_variables::trace);
        CHECK(vector<unsigned int>(headerWithTrace.begin() + 2, headerWithTrace.end()) == encoder.EncodeXiaData(data));
    }

    TEST_CASE ("TestEncodingTraceAndQdc") {
        SetupXiaDataClass(data);
        data.SetQdc(qdc);
        data.SetTrace(unittest_trace_variables::trace);
        CHECK(
        vector<unsigned int>(headerWithQdcTrace.begin() + 2, headerWithQdcTrace.end()) == encoder.EncodeXiaData(data));
    }
}