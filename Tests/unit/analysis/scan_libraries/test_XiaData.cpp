///@file unittest-XiaData.cpp
///@brief A program that will execute unit tests on XiaData
///@author S. V. Paulauskas
///@date December 5, 2016
#include "XiaData.hpp"
#include "UnitTestSampleData.hpp"
#include "HelperFunctions.hpp"

#include <doctest.h>

#include <vector>

#include <cmath>

using namespace std;
using namespace unittest_trace_variables;
using namespace unittest_decoded_data;

XiaData lhs, rhs;

TEST_SUITE ("Analysis/Scan Libraries/XIA Data") {
    TEST_CASE_FIXTURE (XiaData, "GetBaseline") {
        SetFilterBaseline(baseline);
        CHECK(baseline == GetFilterBaseline());
    }

    TEST_CASE_FIXTURE (XiaData, "GetId") {
        SetSlotNumber(slotId);
        SetChannelNumber(channelNumber);
        SetCrateNumber(crateId);
        CHECK(crateId * 208 + GetModuleNumber() * 16 + channelNumber == GetId());
    }

    TEST_CASE_FIXTURE (XiaData, "GetSetCfdForcedTrig") {
        SetCfdForcedTriggerBit(cfd_forced_trigger);
        CHECK (GetCfdForcedTriggerBit());
    }

    TEST_CASE_FIXTURE (XiaData, "GetSetCfdFractionalTime") {
        SetCfdFractionalTime(cfd_fractional_time);
        CHECK(cfd_fractional_time == GetCfdFractionalTime());
    }

    TEST_CASE_FIXTURE (XiaData, "GetSetCfdTriggerSourceBit") {
        SetCfdTriggerSourceBit(cfd_source_trigger_bit);
        CHECK (GetCfdTriggerSourceBit());
    }

    TEST_CASE_FIXTURE (XiaData, "GetSetChannelNumber") {
        SetChannelNumber(channelNumber);
        CHECK(channelNumber == GetChannelNumber());
    }

    TEST_CASE_FIXTURE (XiaData, "GetSetCrateNumber") {
        SetCrateNumber(crateId);
        CHECK(crateId == GetCrateNumber());
    }

    TEST_CASE_FIXTURE (XiaData, "GetSetEnergy") {
        SetEnergy(energy);
        CHECK(energy == GetEnergy());
    }

    TEST_CASE_FIXTURE (XiaData, "GetSetEnergySums") {
        SetEnergySums(energy_sums);
        CHECK(energy_sums == GetEnergySums());
    }

    TEST_CASE_FIXTURE (XiaData, "GetSetEventTimeHigh") {
        SetEventTimeHigh(ts_high);
        CHECK(ts_high == GetEventTimeHigh());
    }

    TEST_CASE_FIXTURE (XiaData, "GetSetEventTimeLow") {
        SetEventTimeLow(ts_low);
        CHECK(ts_low == GetEventTimeLow());
    }

    TEST_CASE_FIXTURE (XiaData, "GetSetExternalTimestamp") {
        SetExternalTimestamp(Conversions::ConcatenateWords(ex_ts_low, ex_ts_high, 32));
        CHECK(Conversions::ConcatenateWords(ex_ts_low, ex_ts_high, 32) == GetExternalTimestamp());
    }

    TEST_CASE_FIXTURE (XiaData, "GetSetExternalTimeHigh") {
        SetExternalTimeHigh(ex_ts_high);
        CHECK(ex_ts_high == GetExternalTimeHigh());
    }

    TEST_CASE_FIXTURE (XiaData, "GetSetExternalTimeLow") {
        SetExternalTimeLow(ex_ts_low);
        CHECK(ex_ts_low == GetExternalTimeLow());
    }

    TEST_CASE_FIXTURE (XiaData, "GetSetPileup") {
        SetPileup(pileup_bit);
        CHECK (IsPileup());
    }

    TEST_CASE_FIXTURE (XiaData, "GetSetQdc") {
        SetQdc(qdc);
        CHECK(qdc == GetQdc());
    }

    TEST_CASE_FIXTURE (XiaData, "GetSetSaturation") {
        SetSaturation(trace_out_of_range);
        CHECK (IsSaturated());
    }

    TEST_CASE_FIXTURE (XiaData, "GetSetSlotNumber") {
        SetSlotNumber(slotId);
        CHECK(slotId == GetSlotNumber());
    }

    TEST_CASE_FIXTURE (XiaData, "GetSetTrace") {
        SetTrace(trace);
        CHECK(trace == GetTrace());
    }

    TEST_CASE_FIXTURE (XiaData, "GetSetVirtualChannel") {
        SetVirtualChannel(virtual_channel);
        CHECK (IsVirtualChannel());
    }

    TEST_CASE_FIXTURE (XiaData, "GetTime") {
        SetTime(unittest_decoded_data::R30474_250::ts);
        CHECK(unittest_decoded_data::R30474_250::ts == GetTime());
    }

///This will test that the Time for the rhs is greater than the lhs
    TEST_CASE ("CompareTime") {
        lhs.Initialize();
        rhs.Initialize();

        lhs.SetFilterTime(unittest_decoded_data::R30474_250::ts);
        rhs.SetFilterTime(unittest_decoded_data::R30474_250::ts + 10);

        CHECK(lhs.CompareTime(&lhs, &rhs));
    }

//This will test that the ID for the rhs is greater than the lhs
    TEST_CASE ("CompareId") {
        lhs.Initialize();
        rhs.Initialize();
        lhs.SetChannelNumber(channelNumber);
        lhs.SetSlotNumber(slotId);
        lhs.SetCrateNumber(crateId);

        rhs.SetChannelNumber(channelNumber);
        rhs.SetSlotNumber(slotId + 2);
        rhs.SetCrateNumber(crateId);

        CHECK(lhs.CompareId(&lhs, &rhs));
    }

    TEST_CASE ("Equality") {
        lhs.Initialize();
        rhs.Initialize();
        lhs.SetChannelNumber(channelNumber);
        lhs.SetSlotNumber(slotId);
        lhs.SetCrateNumber(crateId);
        rhs = lhs;
        CHECK(lhs == rhs);
    }

    TEST_CASE ("LessThanOperator") {
        lhs.Initialize();
        rhs.Initialize();
        lhs.SetFilterTime(unittest_decoded_data::R30474_250::ts);
        rhs = lhs;
        rhs.SetFilterTime(unittest_decoded_data::R30474_250::ts + 10);
        CHECK(lhs < rhs);
    }
}

