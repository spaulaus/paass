/// @file test_dsp_functions.cpp
/// @brief
/// @author S. V. Paulauskas
/// @date December 12, 2020
#include "dsp_functions.hpp"
#include "doctest.h"

using namespace paass::hardware::xia::pixie;

TEST_SUITE ("Hardware/xia/pixie/pixie16") {
    TEST_CASE ("readVarFile") {
        CHECK_THROWS_AS(read_var_file("sdlfkjlj.var"), std::invalid_argument);
        ///TODO: Figure out pathing for test files.

        read_set_file("/home/vincent/sandbox/pixie.set",
                      read_var_file("/usr/local/xia/pixie/firmware/revf_general_16b250m_r35921/dsp/Pixie16DSP_revfgeneral_16b250m_r35921.var"),
                      1);
    }
}

