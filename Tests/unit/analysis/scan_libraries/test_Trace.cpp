///@file unittest-Trace.cpp
///@brief A program that will execute unit tests on Trace
///@author S. V. Paulauskas
///@date February 3, 2017
#include "Trace.hpp"

#include "UnitTestSampleData.hpp"
#include "doctest.h"

using namespace std;
using namespace unittest_trace_variables;
using namespace unittest_decoded_data;

TEST_SUITE ("Analysis/ScanLibraries/Trace") {
    TEST_CASE_FIXTURE (Trace, "TestingGettersAndSetters") {
        double double_input = 100.;

        SUBCASE ("Baseline") {
            SetBaseline(baseline_pair);
            CHECK(baseline_pair.first == GetBaselineInfo().first);
            CHECK(baseline_pair.second == GetBaselineInfo().second);
        }

        SUBCASE("Max") {
            SetMax(max_pair);
            CHECK(max_pair.first == GetMaxInfo().first);
            CHECK(max_pair.second == GetMaxInfo().second);

        }

        SUBCASE("Waveform range") {
            SetWaveformRange(waveform_range);
            CHECK(waveform_range.first == GetWaveformRange().first);
            CHECK(waveform_range.second == GetWaveformRange().second);
        }

        SUBCASE ("Trace sans baseline") {
            SetTraceSansBaseline(trace_sans_baseline);
            for (unsigned int i = 0; i < trace_sans_baseline.size(); i++)
                CHECK (trace_sans_baseline.at(i) == GetTraceSansBaseline().at(i));
        }

        SUBCASE ("Waveform") {
            SetTraceSansBaseline(trace_sans_baseline);
            SetWaveformRange(waveform_range);
            for (unsigned int i = 0; i < waveform.size(); i++)
                CHECK (waveform.at(i) == GetWaveform().at(i));
        }

        SUBCASE("Trigger Filter") {
            SetTriggerFilter(trace_sans_baseline);

            for (unsigned int i = 0; i < trace_sans_baseline.size(); i++)
                CHECK (trace_sans_baseline.at(i) == GetTriggerFilter().at(i));
        }

        SUBCASE ("Energy Sums") {
            SetEnergySums(waveform);
            for (unsigned int i = 0; i < waveform.size(); i++)
                CHECK (waveform.at(i) == GetEnergySums().at(i));
        }

        SUBCASE ("QDC") {
            SetQdc(double_input);
            CHECK(double_input == GetQdc());
        }

        SUBCASE ("Extrapolated Max") {
            SetExtrapolatedMax(extrapolated_maximum_pair);
            CHECK(extrapolated_maximum_pair.first == GetExtrapolatedMaxInfo().first);
            CHECK(extrapolated_maximum_pair.second == GetExtrapolatedMaxInfo().second);
        }

        SUBCASE ("Saturation") {
            SetIsSaturated(true);
            CHECK (IsSaturated());
        }

        SUBCASE ("Phase") {
            SetPhase(double_input);
            CHECK(double_input == GetPhase());
        }

        SUBCASE ("Tau") {
            SetTau(double_input);
            CHECK(double_input == GetTau());
        }

    }

}

