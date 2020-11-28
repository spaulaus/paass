///@file unittest-HelperFunctions.cpp
///@author S. V. Paulauskas
///@date December 12, 2016
#include "HelperFunctions.hpp"
#include "UnitTestSampleData.hpp"

#include "doctest.h"

using namespace std;
using namespace unittest_trace_variables;
using namespace unittest_helper_functions;

TEST_SUITE ("Resources/include/HelperFunctions.hpp") {
    TEST_CASE ("TrapezoidalFiltering") {
        CHECK_THROWS_AS(Filtering::TrapezoidalFilter(vector<double>(), 0, 0), invalid_argument);
        CHECK_THROWS_AS(Filtering::TrapezoidalFilter(trace_sans_baseline, trace_sans_baseline.size() + 10, 2),
                        invalid_argument);
        CHECK_THROWS_AS(Filtering::TrapezoidalFilter(trace_sans_baseline, 4, trace_sans_baseline.size() + 10),
                        invalid_argument);

        auto result = Filtering::TrapezoidalFilter(trace_sans_baseline, length, gap);
        CHECK(filteredTrace.size() == result.size());
        for (unsigned int i = 0; i < result.size(); i++)
            CHECK (filteredTrace[i] == doctest::Approx(result[i]).epsilon(0.1));
    }

    TEST_CASE ("CalculateSlopeAndIntercept") {
        auto result = Polynomial::CalculateSlope(xy1, xy2);
        CHECK(slope == result);
        CHECK(intercept == Polynomial::CalculateYIntercept(xy1, slope));
    }

    TEST_CASE ("CalculateBaseline") {
        ///This tests that the TraceFunctions::CalculateBaseline function works as
        /// expected. This also verifies the Statistics functions CalculateAverage
        /// and CalculateStandardDeviation
        CHECK_THROWS_AS(TraceFunctions::CalculateBaseline(trace, make_pair(0, 1)), range_error);
        CHECK_THROWS_AS(TraceFunctions::CalculateBaseline(vector<unsigned int>(), make_pair(0, 16)), range_error);
        CHECK_THROWS_AS(TraceFunctions::CalculateBaseline(trace, make_pair(17, 1)), range_error);
        CHECK_THROWS_AS(TraceFunctions::CalculateBaseline(trace, make_pair(0, trace.size() + 100)), range_error);

        pair<double, double> result = TraceFunctions::CalculateBaseline(trace, make_pair(0, 70));
        CHECK(baseline == doctest::Approx(result.first).epsilon(1e-7));
        CHECK(standard_deviation == doctest::Approx(result.second).epsilon(1e-9));
    }

    TEST_CASE ("FindMaxiumum") {
        CHECK_THROWS_AS(TraceFunctions::FindMaximum(vector<unsigned int>(), trace_delay), range_error);
        CHECK_THROWS_AS(TraceFunctions::FindMaximum(trace, trace.size() + 100), range_error);
        CHECK_THROWS_AS(TraceFunctions::FindMaximum(trace, 5), range_error);
        CHECK_THROWS_AS(TraceFunctions::FindMaximum(const_vector_uint, trace_delay), range_error);

        pair<unsigned int, double> result = TraceFunctions::FindMaximum(trace, trace_delay);
        CHECK(max_position == result.first);
        CHECK(maximum_value == result.second);
    }


    TEST_CASE ("FindLeadingEdge") {
        CHECK_THROWS_AS(TraceFunctions::FindLeadingEdge(trace, bad_fraction, max_pair), range_error);
        CHECK_THROWS_AS(TraceFunctions::FindLeadingEdge(vector<unsigned int>(), leading_edge_fraction, max_pair),
                        range_error);
        CHECK_THROWS_AS(TraceFunctions::FindLeadingEdge(trace, leading_edge_fraction, make_pair(trace.size() + 10, 3.)),
                        range_error);

        ///@TODO We still need to fix this function so that it works properly
        CHECK(leading_edge_position == TraceFunctions::FindLeadingEdge(trace, leading_edge_fraction, max_pair));
    }

    TEST_CASE ("CalculatePoly3") {
        CHECK_THROWS_AS(Polynomial::CalculatePoly3(vector<unsigned int>(), 0), range_error);

        pair<double, vector<double> > result = Polynomial::CalculatePoly3(poly3_data, 0);

        CHECK(extrapolated_maximum == doctest::Approx(result.first).epsilon(1e-6));

        CHECK(poly3_coeffs.size() == result.second.size());
        for (unsigned int i = 0; i < result.second.size(); i++)
            CHECK (poly3_coeffs[i] == doctest::Approx(result.second[i]).epsilon(1e-6));
    }

    TEST_CASE ("ExtrapolateMaximum") {
        //For determination of the extrapolated maximum value of the trace. This trace
        // favors the left side since f(max+1) is less than f(max - 1).
        CHECK_THROWS_AS(TraceFunctions::ExtrapolateMaximum(vector<unsigned int>(), max_pair), range_error);

        pair<double, vector<double> > result = TraceFunctions::ExtrapolateMaximum(trace, max_pair);

        CHECK(extrapolated_maximum == doctest::Approx(result.first).epsilon(1e-6));
        CHECK(extrapolated_max_coeffs.size() == result.second.size());
        for (unsigned int i = 0; i < result.second.size(); i++)
            CHECK (extrapolated_max_coeffs[i] == doctest::Approx(result.second[i]).epsilon(1e-3));
    }

    TEST_CASE ("CalculatePoly2") {
        CHECK_THROWS_AS(Polynomial::CalculatePoly2(vector<unsigned int>(), 0), range_error);

        pair<double, vector<double> > result = Polynomial::CalculatePoly2(poly2_data, 0);

        CHECK(poly2_val == doctest::Approx(result.first).epsilon(1e-4));

        CHECK(poly2_coeffs.size() == result.second.size());
        for (unsigned int i = 0; i < result.second.size(); i++)
            CHECK (poly2_coeffs[i] == doctest::Approx(result.second[i]).epsilon(1e-6));
    }

    TEST_CASE ("CalculateIntegral") {
        CHECK_THROWS_AS(Statistics::CalculateIntegral(vector<unsigned int>()), range_error);
        CHECK(integral == Statistics::CalculateIntegral(integration_data));
    }

    TEST_CASE ("CalculateQdc") {
        CHECK_THROWS_AS(TraceFunctions::CalculateQdc(vector<unsigned int>(), make_pair(0, 4)), range_error);
        CHECK_THROWS_AS(TraceFunctions::CalculateQdc(trace, make_pair(0, trace.size() + 10)), range_error);
        CHECK_THROWS_AS(TraceFunctions::CalculateQdc(trace, make_pair(1000, 0)), range_error);
        CHECK(integration_qdc == TraceFunctions::CalculateQdc(integration_data, qdc_pair));
    }

    TEST_CASE ("CalculateTailRatio") {
        CHECK_THROWS_AS(TraceFunctions::CalculateTailRatio(vector<unsigned int>(), make_pair(0, 4), 100.0), range_error);
        CHECK_THROWS_AS(TraceFunctions::CalculateTailRatio(trace, make_pair(0, trace.size() + 10), 100.0), range_error);
        CHECK_THROWS_AS(TraceFunctions::CalculateTailRatio(trace, make_pair(0, 4), 0.0), range_error);

        double qdc = TraceFunctions::CalculateQdc(trace, make_pair(70, 91));
        pair<unsigned int, unsigned int> range(80, 91);
        double result = TraceFunctions::CalculateTailRatio(trace, range, qdc);
        CHECK(tail_ratio == doctest::Approx(result).epsilon(1e-6));
    }

    TEST_CASE ("IeeeFloatingOperations") {
        unsigned int input = 1164725159;
        double expected = 3780.7283;
        CHECK(expected == doctest::Approx(IeeeStandards::IeeeFloatingToDecimal(input)).epsilon(1e-4));
        CHECK(input == doctest::Approx(IeeeStandards::DecimalToIeeeFloating(expected)).epsilon(1));
        CHECK((unsigned) 1034818683 == doctest::Approx(IeeeStandards::DecimalToIeeeFloating(0.085)).epsilon(1));
    }
}