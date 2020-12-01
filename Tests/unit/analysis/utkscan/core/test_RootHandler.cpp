/// @file unittest-RootHandler.cpp
/// @brief Unittests for the RootHandler class.
/// @author S. V. Paulauskas
/// @date February 24, 2018
#include "RootHandler.hpp"

#include "doctest.h"

TEST_SUITE ("Analysis/Utkscan/Core/Root Handler") {
    TEST_CASE ("RootHandler") {
        RootHandler *handler = RootHandler::get("/tmp/test-RootHandler");
        CHECK(handler);

        CHECK("TH1D" == std::string(handler->RegisterHistogram(0, "test1d", 10)->ClassName()));
        CHECK("TH2D" == std::string(handler->RegisterHistogram(1, "test2d-xy", 10, 10)->ClassName()));
        CHECK("TH2D" == std::string(handler->RegisterHistogram(2, "test2d-xz", 10, 0, 10)->ClassName()));
        CHECK("TH3D" == std::string(handler->RegisterHistogram(3, "test3d", 10, 10, 10)->ClassName()));

        CHECK(!handler->Plot(123, 123));
        CHECK_THROWS_AS(handler->Get1DHistogram(123), std::invalid_argument);
        CHECK_THROWS_AS(handler->Get2DHistogram(123), std::invalid_argument);
        CHECK_THROWS_AS(handler->Get3DHistogram(123), std::invalid_argument);

        unsigned int dummy = 0;
        CHECK_THROWS_AS(handler->RegisterBranch("notatree", "branchname", &dummy, "leaf list"), std::invalid_argument);

        delete RootHandler::get();
    }
}