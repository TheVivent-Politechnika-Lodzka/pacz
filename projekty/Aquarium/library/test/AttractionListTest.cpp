//
// Created by student on 11.06.2020.
//

#include <boost/test/unit_test.hpp>
#include "typedefs.h"
#include "AttractionList.h"
#include "Attraction.h"

BOOST_AUTO_TEST_SUITE(AttractionListTest)

    struct testFixture {
        std::string testAttraction1Name = "lol";

        AttractionPtr testAttraction1 = std::make_shared<Attraction>(34.5, 100, testAttraction1Name);
        AttractionPtr testAttraction2 = std::make_shared<Attraction>(12.5, 1000, "xd");

        AttractionList testList;


        testFixture() {
            testList.addAttration(testAttraction1);
            testList.addAttration(testAttraction2);
        }

        ~testFixture() {

        }
    };

    BOOST_FIXTURE_TEST_CASE(getAttractionListSize, testFixture) {
        BOOST_CHECK_EQUAL(testList.getAttractionListSize(), 2);
    }

    BOOST_FIXTURE_TEST_CASE(addAttraction, testFixture) {
        BOOST_CHECK_EQUAL(testList.getAttractionListSize(), 2);

        testList.addAttration(std::make_shared<Attraction>(12, 13, "dziesiec"));
        BOOST_CHECK_EQUAL(testList.getAttractionListSize(), 3);
    }

    BOOST_FIXTURE_TEST_CASE(addTheSameAttraction_Negative, testFixture) {
        //rozrónianie Attraction na podstawie nazwy
        BOOST_CHECK_THROW(testList.addAttration(testAttraction1), AttractionListException);
    }

    BOOST_FIXTURE_TEST_CASE(removeAttraction, testFixture) {
        BOOST_CHECK_EQUAL(testList.getAttractionListSize(), 2);
        testList.removeAttraction(testAttraction1Name);
        BOOST_CHECK_EQUAL(testList.getAttractionListSize(), 1);
    }

    BOOST_FIXTURE_TEST_CASE(getAttractionByIndex, testFixture) {
        BOOST_CHECK_EQUAL(testList.getAttractionByIndex(0)->getAttractionName(), testAttraction1->getAttractionName());
        BOOST_CHECK_EQUAL(testList.getAttractionByIndex(1)->getAttractionName(), testAttraction2->getAttractionName());
    }

    BOOST_FIXTURE_TEST_CASE(getAttractionByName, testFixture) {
        BOOST_CHECK_EQUAL(testList.getAttractionByName(testAttraction1Name)->getAttractionName(), testAttraction1Name);
    }

    BOOST_FIXTURE_TEST_CASE(getTotalCost, testFixture) {
        BOOST_CHECK_EQUAL(testList.getTotalCost(), testAttraction1->getCost() + testAttraction2->getCost());
    }

    BOOST_FIXTURE_TEST_CASE(clone, testFixture) {
        AttractionList *clonedList = testList.clone();
        clonedList->addAttration(std::make_shared<Attraction>(0.12, 10, "wzorcowa atrakcja"));
        BOOST_CHECK(testList.getAttractionListSize() != clonedList->getAttractionListSize());
    }

    BOOST_FIXTURE_TEST_CASE(overloadedOutOperator, testFixture){
        std::ostringstream out;
        out << testList;
        BOOST_TEST_MESSAGE(out.str());
    }

BOOST_AUTO_TEST_SUITE_END()