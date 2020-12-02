/// @file unittest-RootFitter.cpp
/// @brief Unit tests for the RootFitter class
/// @author S. V. Paulauskas
/// @date December 18, 2016
#include "RootFitter.hpp"
#include "TimingConfiguration.hpp"
#include "UnitTestSampleData.hpp"

#include "doctest.h"

#include <stdexcept>

using namespace std;
using namespace unittest_trace_variables;
using namespace unittest_fit_variables;

TEST_SUITE ("ROOT Fitter") {
    TEST_CASE_FIXTURE (RootFitter, "TestRootFitter") {
        TimingConfiguration cfg;
        cfg.SetBeta(pmt::beta);
        cfg.SetGamma(pmt::gamma);

        CHECK_THROWS_AS(CalculatePhase(vector<double>(), cfg, max_pair, baseline_pair), range_error);

        cfg.SetQdc(waveform_qdc);
        CHECK(-0.581124 == doctest::Approx(CalculatePhase(waveform, cfg, max_pair, baseline_pair)).epsilon(1));
    }
}