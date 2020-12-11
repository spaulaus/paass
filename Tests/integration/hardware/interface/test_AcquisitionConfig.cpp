/// @file unittest-AcquisitionConfig.cpp
/// @brief Unittest for the AcquisitionConfig class
/// @author S. V. Paulauskas
/// @date August 11, 2018
/// @copyright Copyright (c) 2018 S. V. Paulauskas. 
/// @copyright All rights reserved. Released under the Creative Commons Attribution-ShareAlike 4.0 International License
#include "AcquisitionConfig.hpp"
#include "doctest.h"

#include <stdexcept>

TEST_SUITE ("Acquisition/Interface/AcquisitionConfig") {
    TEST_CASE_FIXTURE (AcquisitionConfig, "TestModuleCounts") {
        ReadConfiguration("test-xml-files/no-errors.xml", false);
        CHECK(13 == GetNumberOfModules());
        CHECK(16 == GetNumberOfChannels());
    }

    TEST_CASE_FIXTURE (AcquisitionConfig, "TestMissingBit") {
        CHECK_THROWS_AS(ReadConfiguration("test-xml-files/missing-bit.xml", false), std::invalid_argument);
    }

    TEST_CASE_FIXTURE (AcquisitionConfig, "TestMissingFrequency") {
        CHECK_THROWS_AS(ReadConfiguration("test-xml-files/missing-frequency.xml", false), std::invalid_argument);
    }

    TEST_CASE_FIXTURE (AcquisitionConfig, "TestMissingModuleType") {
        CHECK_THROWS_AS(ReadConfiguration("test-xml-files/missing-module-type.xml", false), std::invalid_argument);
    }

    TEST_CASE_FIXTURE (AcquisitionConfig, "TestMissingPixieBaseDir") {
        CHECK_THROWS_AS(ReadConfiguration("test-xml-files/missing-pixie-base-dir.xml", false), std::invalid_argument);
    }

    TEST_CASE_FIXTURE (AcquisitionConfig, "TestMissingRevision") {
        CHECK_THROWS_AS(ReadConfiguration("test-xml-files/missing-revision.xml", false), std::invalid_argument);
    }

    TEST_CASE_FIXTURE (AcquisitionConfig, "TestMissingFirmwareChild") {
        CHECK_THROWS_AS(ReadConfiguration("test-xml-files/missing-firmware-child.xml", false), std::invalid_argument);
    }

    TEST_CASE_FIXTURE (AcquisitionConfig, "TestTooManyModules") {
        CHECK_THROWS_AS(ReadConfiguration("test-xml-files/too-many-modules.xml", false), std::invalid_argument);
    }
}