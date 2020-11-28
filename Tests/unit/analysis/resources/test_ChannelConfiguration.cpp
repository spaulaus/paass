///@file unittest-ChannelConfiguration.cpp
///@brief Program that will test functionality of ChannelConfiguration
///@author S. V. Paulauskas
///@date November 25, 2016
#include "ChannelConfiguration.hpp"

#include "doctest.h"

using namespace std;

TEST_SUITE ("Analysis/Resources/ChannelConfiguration") {
    TEST_CASE_FIXTURE (ChannelConfiguration, "Get and Set Tags") {
        string tag = "unittest";
        AddTag(tag);
        CHECK(HasTag(tag));

        set<string> testset;
        testset.insert(tag);
        CHECK(GetTags() == testset);
    }

    ///Testing the case that we have a missing tag
    TEST_CASE_FIXTURE (ChannelConfiguration, "Has Missing Tag") {
        string tag = "unittest";
        CHECK(!HasTag(tag));
    }

    ///Check the comparison operators
    TEST_CASE_FIXTURE (ChannelConfiguration, "Comparison") {
        string type = "unit";
        string subtype = "test";
        unsigned int loc = 112;
        SetSubtype(subtype);
        SetType(type);
        SetLocation(loc);

        ChannelConfiguration id(type, subtype, loc);

        CHECK(*this == id);

        SetLocation(123);
        CHECK(*this > id);

        SetLocation(4);
        CHECK(*this < id);
    }

    ///Testing that the place name is returning the proper value
    TEST_CASE_FIXTURE (ChannelConfiguration, "Place Name") {
        string type = "unit";
        string subtype = "test";
        unsigned int loc = 112;
        SetSubtype(subtype);
        SetType(type);
        SetLocation(loc);
        CHECK (GetPlaceName() == "unit_test_112");
    }

    ///Test that the zero function is performing it's job properly
    TEST_CASE_FIXTURE (ChannelConfiguration, "Zero") {
        ChannelConfiguration id("unit", "test", 123);
        id.Zero();
        CHECK(*this == id);
    }
}

