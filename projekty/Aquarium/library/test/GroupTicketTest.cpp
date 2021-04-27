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

BOOST_AUTO_TEST_SUITE(GroupTicketTest)

    struct testFixture {
        std::string tId = "2";
        pt::ptime tActivDate = pt::ptime(gr::date(2020, 06, 30));
        pt::ptime tActivDateptr = pt::ptime(gr::date(2020, 07, 20));
        unsigned int tNumberofPeople = 7;
        std::string FirstName = "Adam";
        std::string LastName = "Kapuscinski";
        std::string PESEL = "123456789";
        Group tGroupType = FAMILY;

        ClientPtr c1 = std::make_shared<Client>(FirstName, LastName, PESEL);

        AttractionList *testList;
        AttractionList *testList1;

        GroupTicketPtr gT1;
        GroupTicketPtr gT2;

        testFixture() {
            testList = new AttractionList();
            testList1 = new AttractionList();

            AttractionPtr testAttraction1 = std::make_shared<Attraction>(42.0, 1000, "testing");
            testList->addAttration(testAttraction1);
            testList1->addAttration(testAttraction1);

            gT1 = std::make_shared<GroupTicket>("2", tActivDateptr, 20, testList,
                                                c1, 7, FAMILY);
            gT2 = std::make_shared<GroupTicket>("2", tActivDateptr, 20, testList1,
                                                c1, 7, TOUR);

        }

        ~testFixture() {
        }
    };

    BOOST_FIXTURE_TEST_CASE(Constructor, testFixture) {
        //sprawdzone w TicketTest.cpp
    }

    BOOST_FIXTURE_TEST_CASE(getFinalPrice, testFixture) {
        BOOST_TEST(gT1->getFinalPrice() == 18.6, boost::test_tools::tolerance(0.1));
        BOOST_TEST(gT2->getFinalPrice() == 53.32, boost::test_tools::tolerance(0.1));
    }

    BOOST_FIXTURE_TEST_CASE(changeDate, testFixture) {
        BOOST_CHECK_EQUAL(gT1->getActiveDate(), tActivDateptr);
        gT1->changeDate(tActivDate);
        BOOST_CHECK_EQUAL(gT1->getActiveDate(), tActivDate);
        gT1->changeDate(pt::second_clock::local_time() + pt::hours(168) + pt::seconds(1));
        BOOST_CHECK_EQUAL(gT1->getActiveDate(), pt::second_clock::local_time() + pt::hours(168) + pt::seconds(1));
        //zmiana daty na mniej niż 7 dni w przyszłość [negatywny]
        gT1->changeDate(pt::second_clock::local_time() + pt::hours(167) + pt::minutes(59) + pt::seconds(59));
        BOOST_CHECK_THROW(gT1->changeDate(tActivDate), TicketException);
    }

    BOOST_FIXTURE_TEST_CASE(overloadedOutOperator, testFixture){
        std::ostringstream out;
        out << *gT1;
        BOOST_TEST_MESSAGE(out.str());
    }

BOOST_AUTO_TEST_SUITE_END()