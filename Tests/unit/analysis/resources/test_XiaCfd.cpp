///@file unittest-XiaCfd.cpp
///@author S. V. Paulauskas
///@date May 13, 2018
#include "XiaCfd.hpp"

#include "TimingConfiguration.hpp"
#include "UnitTestSampleData.hpp"

#include "doctest.h"

#include <stdexcept>

using namespace std;
using namespace unittest_trace_variables;
using namespace unittest_cfd_variables::xia;

TEST_SUITE ("XIA CFD") {
    TEST_CASE_FIXTURE (XiaCfd, "XiaCfd") {
        TimingConfiguration cfg;
        cfg.SetFraction(fraction);
        cfg.SetDelay(delay);
        cfg.SetGap(gap);
        cfg.SetLength(length);

        CHECK_THROWS_AS(CalculatePhase(vector<double>(), cfg), range_error);
        CHECK(phase == doctest::Approx(CalculatePhase(trace_sans_baseline, cfg)).epsilon(0.001));
    }
}
