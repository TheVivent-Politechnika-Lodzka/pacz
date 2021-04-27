//
// Created by student on 11.06.2020.
//
#include <boost/test/unit_test.hpp>
#include "Client.h"

BOOST_AUTO_TEST_SUITE(ClientTest)

    struct testFixture {
        std::string FirstName = "Adam";
        std::string LastName = "Kapuscinski";
        std::string PESEL = "123456789";

        Client *testClient;

        testFixture() {
            testClient = new Client(FirstName, LastName, PESEL);
        }

        ~testFixture() {
            delete testClient;
        }
    };

    BOOST_FIXTURE_TEST_CASE(Constructor, testFixture) {
        Client newClient(FirstName, LastName, PESEL);
        BOOST_CHECK_EQUAL(newClient.getFirstName(), FirstName);
        BOOST_CHECK_EQUAL(newClient.getLastName(), LastName);
        BOOST_CHECK_EQUAL(newClient.getPesel(), PESEL);
        BOOST_CHECK_EQUAL(newClient.isArchived(), false);
    }

    BOOST_FIXTURE_TEST_CASE(setFirstName, testFixture) {
        std::string newFirstName = "Damian";
        testClient->setFirstName(newFirstName);
        BOOST_CHECK_EQUAL(testClient->getFirstName(), newFirstName);
    }

    BOOST_FIXTURE_TEST_CASE(setEmptyFirstName_Negative, testFixture) {
        BOOST_CHECK_THROW(testClient->setFirstName(""), ClientException);
    }

    BOOST_FIXTURE_TEST_CASE(setLastName, testFixture) {
        std::string newLastName = "Szczecinski";
        testClient->setLastName(newLastName);
        BOOST_CHECK_EQUAL(testClient->getLastName(), newLastName);
    }

    BOOST_FIXTURE_TEST_CASE(setEmptyLastName_Negative, testFixture) {
        BOOST_CHECK_THROW(testClient->setLastName(""), ClientException);
    }

    BOOST_FIXTURE_TEST_CASE(setArchived, testFixture) {
        BOOST_CHECK_EQUAL(testClient->isArchived(), false);
        testClient->setArchived();
        BOOST_CHECK_EQUAL(testClient->isArchived(), true);
    }

    BOOST_FIXTURE_TEST_CASE(overloadedOutOperator, testFixture){
        std::ostringstream out;
        out << *testClient;
        BOOST_TEST_MESSAGE(out.str());
    }

BOOST_AUTO_TEST_SUITE_END()