//
// Created by student on 11.06.2020.
//

#include <boost/test/unit_test.hpp>
#include "Aquarium.h"

BOOST_AUTO_TEST_SUITE(AquariumTest)

    struct testFixture {

        Aquarium *testAquarium;
        double baseTicketPrice = 21.37;
        unsigned int baseCapacity = 1;

        testFixture() {
            testAquarium = new Aquarium(baseTicketPrice, baseCapacity);
            testAquarium->addToAttractionList(10, 1, "Rollercoaster z nagrodami");
        }

        ~testFixture() {
            delete testAquarium;
        }
    };

    BOOST_FIXTURE_TEST_CASE(Constructor, testFixture) {
        Aquarium *newAquarium = new Aquarium(baseTicketPrice, baseCapacity);
        BOOST_CHECK_EQUAL(newAquarium->getBaseTicketPrice(), baseTicketPrice);
        BOOST_CHECK_EQUAL(newAquarium->getBaseCapacity(), baseCapacity);
        delete newAquarium;
    }

    BOOST_FIXTURE_TEST_CASE(getFullCapacity_withAttractionList, testFixture) {
        BOOST_CHECK_EQUAL(testAquarium->getFullCapacity(), 2);
    }

    BOOST_FIXTURE_TEST_CASE(setBaseTicketPrice, testFixture) {
        double newPrice = 11;
        BOOST_CHECK_EQUAL(testAquarium->getBaseTicketPrice(), baseTicketPrice);
        testAquarium->setBaseTicketPrice(newPrice);
        BOOST_CHECK_EQUAL(testAquarium->getBaseTicketPrice(), newPrice);
    }

    BOOST_FIXTURE_TEST_CASE(setNegativeBaseTicketPrice, testFixture) {
        BOOST_CHECK_THROW(testAquarium->setBaseTicketPrice(-10), AquariumException);
    }

    BOOST_FIXTURE_TEST_CASE(setBaseCapacity, testFixture) {
        double newCapacity = 11;
        BOOST_CHECK_EQUAL(testAquarium->getBaseCapacity(), baseCapacity);
        testAquarium->setBaseCapacity(newCapacity);
        BOOST_CHECK_EQUAL(testAquarium->getBaseCapacity(), newCapacity);
    }

    //poniższe sprawdzić po prostu przy pomocy dynamic_cast, czy zwracany wskaźnik jest odpowiedniego typu

    BOOST_FIXTURE_TEST_CASE(clients, testFixture) {
        BOOST_CHECK(dynamic_cast<ClientManager *>(testAquarium->clients()) != nullptr);
    }

    BOOST_FIXTURE_TEST_CASE(tickets, testFixture) {
        BOOST_CHECK(dynamic_cast<TicketManager *>(testAquarium->tickets()) != nullptr);
    }

    BOOST_FIXTURE_TEST_CASE(attractions, testFixture) {
        BOOST_CHECK(dynamic_cast<const AttractionList *>(testAquarium->attractions()) != nullptr);
    }

    BOOST_FIXTURE_TEST_CASE(overloadedOutOperator, testFixture){
        std::ostringstream out;
        out << *testAquarium;
        BOOST_TEST_MESSAGE(out.str());
    }

BOOST_AUTO_TEST_SUITE_END()