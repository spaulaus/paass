///@file unittest-StringManipulationFunctions.cpp
///@brief A unit tests for StringManipulationFunctions header functions
///@author S. V. Paulauskas
///@date February 09, 2017
#include "StringManipulationFunctions.hpp"

#include "doctest.h"

using namespace std;
using namespace StringManipulation;

TEST_SUITE ("Resources/StringManipulationFunctions") {
    TEST_CASE ("TestStringTokenizer") {
        vector<string> expected = {"We", "tokenize", "on", "spaces."};
        auto result = TokenizeString("We tokenize on spaces.", " ");
        CHECK(expected.size() == result.size());
        for (unsigned int i = 0; i < result.size(); i++)
            CHECK (expected[i] == result[i]);
    }

    TEST_CASE ("TestStringToBool") {
        CHECK(!StringToBool("false"));
        CHECK(!StringToBool("FALSE"));
        CHECK(!StringToBool("0"));
        CHECK(!StringToBool("No"));
        CHECK(!StringToBool("no"));

        CHECK(StringToBool("true"));
        CHECK(StringToBool("TRUE"));
        CHECK(StringToBool("YES"));
        CHECK(StringToBool("yes"));
        CHECK(StringToBool("Yes"));
        CHECK(StringToBool("1"));
    }

    TEST_CASE ("TestBoolToString") {
        CHECK("Yes" == BoolToString(true));
        CHECK("No" == BoolToString(false));
    }

    TEST_CASE ("TestPadString") {
        string delimiter = ".";
        string message = "success";
        unsigned int desiredLength = 20;
        string expectedFront = ".............success";
        string expectedBack = "success.............";

        CHECK_THROWS_AS(PadString(expectedFront, delimiter, 3), length_error);
        CHECK_THROWS_AS(PadString(expectedBack, expectedFront, 40), invalid_argument);
        CHECK(expectedFront == PadString(message, delimiter, desiredLength));
        CHECK(expectedBack == PadString(message, delimiter, desiredLength, false));
    }

    TEST_CASE ("TestFormatHumanReadableSizes") {
        CHECK("10 B" == FormatHumanReadableSizes(10));
        CHECK("2.93 kB" == FormatHumanReadableSizes(3000));
        CHECK("1.23 MB" == FormatHumanReadableSizes(1289000));
        CHECK("7.77 GB" == FormatHumanReadableSizes(8339000000));
    }

    TEST_CASE ("TestIsNumeric") {
        CHECK(IsNumeric("123456789"));
        CHECK(IsNumeric("-123456789"));
        CHECK(IsNumeric("12345.6789"));
        CHECK(IsNumeric("-12345.6789"));
        CHECK(!IsNumeric("123ABC456DEF"));
        CHECK(!IsNumeric("123abc"));
        CHECK(!IsNumeric("qwerty"));
        CHECK(!IsNumeric("!@#$%"));
        CHECK(!IsNumeric("1.34E-34"));
    }
}
