//
// Created by student on 11.06.2020.
//


#include <boost/test/unit_test.hpp>
#include "SingleTicket.h"
#include "typedefs.h"
#include "Client.h"
#include "AttractionList.h"
#include "Attraction.h"

BOOST_AUTO_TEST_SUITE(SingleTicketTest)

    struct testFixture {
        std::string tId = "2";
        pt::ptime tActivDate = pt::ptime(gr::date(2020, 06, 30));
        pt::ptime tActivDateptr = pt::ptime(gr::date(2020, 07, 20));
        double tBasePrice = 11.09;
        std::string FirstName = "Adam";
        std::string LastName = "Kapuscinski";
        std::string PESEL = "123456789";
        Visitor tVisitorType = STUDENT;

        ClientPtr c1 = std::make_shared<Client>(FirstName, LastName, PESEL);

        AttractionList *testList;
        SingleTicketPtr sT1;


        testFixture() {

            testList = new AttractionList();

            AttractionPtr testAttraction1 = std::make_shared<Attraction>(42.0, 1000, "testing");

            testList->addAttration(testAttraction1);

            sT1 = std::make_shared<SingleTicket>("2", tActivDateptr, 20, testList,
                                                 c1, STUDENT);
//          https://www.youtube.com/watch?v=hfjHJneVonE
        }

        ~testFixture() {
        }
    };

    BOOST_FIXTURE_TEST_CASE(Constructor, testFixture) {
        //sprawdzone w TicketTest.cpp
    }

    BOOST_FIXTURE_TEST_CASE(getActualPrice, testFixture) {
        BOOST_CHECK_EQUAL(sT1->getFinalPrice(), 31);
    }

    BOOST_FIXTURE_TEST_CASE(changeDate, testFixture) {
        BOOST_CHECK_EQUAL(sT1->getActiveDate(), tActivDateptr);
        sT1->changeDate(tActivDate);
        BOOST_CHECK_EQUAL(sT1->getActiveDate(), tActivDate);
        sT1->changeDate(pt::second_clock::local_time() + pt::hours(72) + pt::seconds(1));
        BOOST_CHECK_EQUAL(sT1->getActiveDate(), pt::second_clock::local_time() + pt::hours(72) + pt::seconds(1));
        //ustawienie daty na mniej niż 3 dni w przyszłość [negatywny]
        sT1->changeDate(pt::second_clock::local_time() + pt::hours(71) + pt::minutes(59) + pt::seconds(59));
        BOOST_CHECK_THROW(sT1->changeDate(tActivDate), TicketException);
    }

    BOOST_FIXTURE_TEST_CASE(overloadedOutOperator, testFixture){
        std::ostringstream out;
        out << *sT1;
        BOOST_TEST_MESSAGE(out.str());
    }

BOOST_AUTO_TEST_SUITE_END()