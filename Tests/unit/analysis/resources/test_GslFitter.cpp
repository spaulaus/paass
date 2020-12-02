///\file unittest-GslFitter.cpp
///\brief A small code to test the functionality of the FitDriver
///\author S. V. Paulauskas
///\date August 8, 2016
#include "GslFitter.hpp"

#include "TimingConfiguration.hpp"
#include "UnitTestSampleData.hpp"

#include <doctest.h>

#include <stdexcept>

using namespace std;
using namespace unittest_fit_variables;
using namespace unittest_trace_variables;

TEST_SUITE ("GSL Fitter") {
    TEST_CASE_FIXTURE (GslFitter, "PmtFitting") {
        TimingConfiguration cfg;
        cfg.SetBeta(pmt::beta);
        cfg.SetGamma(pmt::gamma);
        cfg.SetQdc(waveform_qdc);
        cfg.SetIsFastSiPm(false);

        CHECK_THROWS_AS(CalculatePhase(vector<double>(), cfg, max_pair, baseline_pair), range_error);
        CHECK(pmt::phase == doctest::Approx(CalculatePhase(waveform, cfg, max_pair, baseline_pair)).epsilon(0.5));
    }

    TEST_CASE_FIXTURE (GslFitter, "GaussianFitting") {
        TimingConfiguration cfg;
        cfg.SetBeta(gaussian::beta);
        cfg.SetGamma(gaussian::gamma);
        cfg.SetQdc(unittest_gaussian_trace::qdc);
        cfg.SetIsFastSiPm(true);
        CHECK(gaussian::phase ==
              doctest::Approx(CalculatePhase(unittest_gaussian_trace::waveform, cfg, max_pair, baseline_pair)).epsilon(
              0.1));
    }
}