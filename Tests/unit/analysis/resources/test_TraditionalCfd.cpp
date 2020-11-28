///@file unittest-TraditionalCfd.cpp
///@author S. V. Paulauskas
///@date December 12, 2016
#include "TimingConfiguration.hpp"

#include "TraditionalCfd.hpp"
#include "UnitTestSampleData.hpp"

#include "doctest.h"

#include <stdexcept>

using namespace std;
using namespace unittest_trace_variables;
using namespace unittest_cfd_variables::traditional;

TEST_SUITE ("Traditional CFD") {
    TEST_CASE_FIXTURE (TraditionalCfd, "TraditionalCfd") {
        TimingConfiguration cfg;
        cfg.SetFraction(fraction);
        cfg.SetDelay(delay);
        CHECK_THROWS_AS(CalculatePhase(vector<double>(), cfg), range_error);
        CHECK(phase == doctest::Approx(CalculatePhase(trace_sans_baseline, cfg)).epsilon(0.001));
    }
}