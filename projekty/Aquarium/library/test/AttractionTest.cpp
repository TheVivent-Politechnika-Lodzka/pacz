//
// Created by student on 11.06.2020.
//

#include <boost/test/unit_test.hpp>
#include "Attraction.h"

BOOST_AUTO_TEST_SUITE(AttractionTest)

    struct testFixture {
        double Cost = 21.37;
        int MaxVisitors = 69;
        std::string AttractionName = "Rollercoaster z Delfinami";

        Attraction *testAttraction;


        testFixture() {
            testAttraction = new Attraction(Cost, MaxVisitors, AttractionName);
        }

        ~testFixture() {
            delete testAttraction;
        }
    };

    BOOST_FIXTURE_TEST_CASE(Constructor, testFixture) {
        Attraction newAttraction(Cost, MaxVisitors, AttractionName);
        BOOST_CHECK_EQUAL(newAttraction.getCost(), Cost);
        BOOST_CHECK_EQUAL(newAttraction.getMaxVisitors(), MaxVisitors);
        BOOST_CHECK_EQUAL(newAttraction.getAttractionName(), AttractionName);
    }

    BOOST_FIXTURE_TEST_CASE(setAttractionName, testFixture) {
        std::string newAttractionName = "Rollercoaster z Robertem Makłowiczem";
        BOOST_CHECK_EQUAL(testAttraction->getAttractionName(), AttractionName);
        testAttraction->setAttractionName(newAttractionName);
        BOOST_CHECK_EQUAL(testAttraction->getAttractionName(), newAttractionName);
    }

    BOOST_FIXTURE_TEST_CASE(setEmptyAttractionName_Negative, testFixture) {
        BOOST_CHECK_THROW(testAttraction->setAttractionName(""), AttractionException);
    }

    BOOST_FIXTURE_TEST_CASE(setAttractionCost, testFixture) {
        double newCost = 11.09;
        BOOST_CHECK_EQUAL(testAttraction->getCost(), Cost);
        testAttraction->setCost(newCost);
        BOOST_CHECK_EQUAL(testAttraction->getCost(), newCost);
    }

    BOOST_FIXTURE_TEST_CASE(setNegativeAttractionCost_Negative, testFixture) {
        BOOST_CHECK_THROW(testAttraction->setCost(-10), AttractionException);
    }

    BOOST_FIXTURE_TEST_CASE(setAttractionMaxVisitors, testFixture) {
        int newMaxVisitors = 420;
        BOOST_CHECK_EQUAL(testAttraction->getMaxVisitors(), MaxVisitors);
        testAttraction->setMaxVisitors(newMaxVisitors);
        BOOST_CHECK_EQUAL(testAttraction->getMaxVisitors(), newMaxVisitors);
    }

    BOOST_FIXTURE_TEST_CASE(overloadedOutOperator, testFixture){
        std::ostringstream out;
        out << *testAttraction;
        BOOST_TEST_MESSAGE(out.str());
    }


BOOST_AUTO_TEST_SUITE_END()