//
// Created by student on 11.06.2020.
//

#include <boost/test/unit_test.hpp>
#include "SingleTicket.h"
#include "GroupTicket.h"
#include "typedefs.h"
#include "Client.h"
#include "AttractionList.h"
#include "Attraction.h"

BOOST_AUTO_TEST_SUITE(TicketTest)

    struct testFixture {
        std::string tId = "2";
        pt::ptime tActivDate = pt::ptime(gr::date(2020, 06, 30));
        pt::ptime tActivDateptr = pt::ptime(gr::date(2020, 07, 20));
        double tBasePrice = 11.09;
        unsigned int tNumberofPeople = 7;
        std::string FirstName = "Adam";
        std::string LastName = "Kapuscinski";
        std::string PESEL = "123456789";
        Visitor tVisitorType = STUDENT;
        Group tGroupType = FAMILY;

        ClientPtr c1 = std::make_shared<Client>(FirstName, LastName, PESEL);

        AttractionList *testList;
        AttractionList *testList1;
        AttractionList *testList2;
        AttractionList *testList3;
        SingleTicketPtr sT1;
        GroupTicketPtr gT1;

        testFixture() {
            testList = new AttractionList();
            testList1 = new AttractionList();
            testList2 = new AttractionList();
            testList3 = new AttractionList();

            AttractionPtr testAttraction1 = std::make_shared<Attraction>(42.0, 1000, "testing");
            testList->addAttration(testAttraction1);
            testList1->addAttration(testAttraction1);
            testList2->addAttration(testAttraction1);
            testList3->addAttration(testAttraction1);

            sT1 = std::make_shared<SingleTicket>("2", tActivDateptr, 20, testList2,
                                                 c1, STUDENT);
            gT1 = std::make_shared<GroupTicket>("2", tActivDateptr, 20, testList3,
                                                c1, 7, FAMILY);

        }

        ~testFixture() {
        }
    };

    BOOST_FIXTURE_TEST_CASE(Constructor, testFixture) {
        ClientPtr c1 = std::make_shared<Client>(FirstName, LastName, PESEL);
        SingleTicketPtr testST1 = std::make_shared<SingleTicket>(tId, tActivDate, tBasePrice, testList, c1,
                                                                 tVisitorType);
        BOOST_CHECK_EQUAL(testST1->getTicketId(), tId);
        BOOST_CHECK_EQUAL(testST1->getActiveDate(), tActivDate);
        BOOST_CHECK_EQUAL(testST1->getAttractions(), testList);
        BOOST_CHECK_EQUAL(testST1->getOwner(), c1);
        BOOST_CHECK_EQUAL(testST1->getBasePrice(), tBasePrice);
        BOOST_CHECK_EQUAL(testST1->getVisitorType(), tVisitorType);
        BOOST_CHECK_EQUAL(testST1->isUsed(), false);

        GroupTicketPtr testGT1 = std::make_shared<GroupTicket>(tId, tActivDate, tBasePrice, testList1, c1,
                                                               tNumberofPeople, tGroupType);
        BOOST_CHECK_EQUAL(testGT1->getTicketId(), tId);
        BOOST_CHECK_EQUAL(testGT1->getActiveDate(), tActivDate);
        BOOST_CHECK_EQUAL(testGT1->getAttractions(), testList1);
        BOOST_CHECK_EQUAL(testGT1->getOwner(), c1);
        BOOST_CHECK_EQUAL(testGT1->getBasePrice(), tBasePrice);
        BOOST_CHECK_EQUAL(testGT1->getNumberOfPeople(), tNumberofPeople);
        BOOST_CHECK_EQUAL(testGT1->getGroupType(), tGroupType);
        BOOST_CHECK_EQUAL(testGT1->isUsed(), false);
    }

    BOOST_FIXTURE_TEST_CASE(setUsed, testFixture) {
        BOOST_CHECK_EQUAL(sT1->isUsed(), false);
        sT1->setUsed();
        BOOST_CHECK_EQUAL(sT1->isUsed(), true);

        BOOST_CHECK_EQUAL(gT1->isUsed(), false);
        gT1->setUsed();
        BOOST_CHECK_EQUAL(gT1->isUsed(), true);
    }

    BOOST_FIXTURE_TEST_CASE(AttractionListConstanceTest, testFixture) {
        BOOST_CHECK(dynamic_cast<const AttractionList *>(sT1->getAttractions()) != nullptr);
        BOOST_CHECK(dynamic_cast<const AttractionList *>(gT1->getAttractions()) != nullptr);
    }

    BOOST_FIXTURE_TEST_CASE(OwnerConstanceTest, testFixture) {
        BOOST_CHECK(dynamic_cast<const Client *>(sT1->getOwner().get()) != nullptr);
        BOOST_CHECK(dynamic_cast<const Client *>(gT1->getOwner().get()) != nullptr);
    }

    BOOST_FIXTURE_TEST_CASE(overloadedOutOperator, testFixture) {
        TicketPtr newTicket = std::make_shared<SingleTicket>("2", tActivDateptr, 20, nullptr,
                                                             c1, BLIND);
        std::ostringstream out;
        out << *newTicket;
        BOOST_TEST_MESSAGE(out.str());
    }

BOOST_AUTO_TEST_SUITE_END()