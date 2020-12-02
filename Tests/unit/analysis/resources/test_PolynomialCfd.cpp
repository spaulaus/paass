///@file unittest-PolynomialCfd.cpp
///@author S. V. Paulauskas
///@date December 12, 2016
#include "PolynomialCfd.hpp"
#include "TimingConfiguration.hpp"
#include "UnitTestSampleData.hpp"

#include <doctest.h>

#include <stdexcept>

using namespace std;
using namespace unittest_trace_variables;
using namespace unittest_cfd_variables;

TEST_SUITE ("Polynomial CFD") {
    TEST_CASE_FIXTURE (PolynomialCfd, "PolynomialCfd") {
        TimingConfiguration cfg;
        cfg.SetFraction(polynomial::fraction);
        cfg.SetDelay(polynomial::delay);

        CHECK_THROWS_AS(CalculatePhase(std::vector<double>(), cfg, max_pair, baseline_pair), range_error);
        CHECK_THROWS_AS(CalculatePhase(trace_sans_baseline, cfg, make_pair(trace_sans_baseline.size() + 3, 100),
                                       baseline_pair), range_error);
        CHECK(polynomial::phase == doctest::Approx(
        CalculatePhase(trace_sans_baseline, cfg, extrapolated_maximum_pair, baseline_pair)).epsilon(5));
    }
}