//
// Created by student on 11.06.2020.
//

#include <boost/test/unit_test.hpp>
#include "Aquarium.h"
#include "AttractionList.h"
#include "Attraction.h"
#include "Client.h"
#include "SingleTicket.h"
#include "GroupTicket.h"

BOOST_AUTO_TEST_SUITE(TicketManagerTest)

    struct testFixture {
        double baseTicketPrice = 13.69;
        unsigned int baseCapacity = 10;

        std::string testAttractionName = "Rollercoaster z Magdą Gessler";
        double baseAttractionPrice1 = 0.01;
        double baseAttractionPrice2 = 100;
        unsigned int AttractionCapacity1 = 1;
        unsigned int AttractionCapacity2 = 5;

        AttractionPtr testAttraction1;
        AttractionPtr testAttraction2;

        Aquarium *testAquarium;
        TicketManager *testTicketManager;
        ClientPtr testClient;

        testFixture() {
            testAquarium = new Aquarium(baseTicketPrice, baseCapacity);
            testAquarium->clients()->registerClient("Damian", "Szczeciński", "123654789");
            testTicketManager = testAquarium->tickets();
            testClient = testAquarium->clients()->getByIndex(0);
            testAquarium->addToAttractionList(baseAttractionPrice1, AttractionCapacity1, testAttractionName);
            testAquarium->addToAttractionList(baseAttractionPrice2, AttractionCapacity2, "Kevin sam w Oceanarium");
            testAttraction1 = testAquarium->attractions()->getAttractionByIndex(0);
            testAttraction2 = testAquarium->attractions()->getAttractionByIndex(1);
        }

        ~testFixture() {
            delete testAquarium;
        }
    };

    BOOST_FIXTURE_TEST_CASE(Constructor, testFixture) {
        BOOST_CHECK_EQUAL(testTicketManager->getLocalAquarium(), testAquarium);
    }

    BOOST_FIXTURE_TEST_CASE(addToAttractionList, testFixture) {
        BOOST_CHECK_EQUAL(testTicketManager->getTemporaryAttractionList()->getAttractionListSize(), 0);
        testTicketManager->addToAttractionList(testAttraction1);
        BOOST_CHECK_EQUAL(testTicketManager->getTemporaryAttractionList()->getAttractionListSize(), 1);
    }

    BOOST_FIXTURE_TEST_CASE(addAttractionNotFromAquariumToAttractionList_Negative, testFixture) {
        AttractionPtr newAttraction = std::make_shared<Attraction>(baseAttractionPrice1, AttractionCapacity1,
                                                                   testAttractionName);
        BOOST_CHECK_THROW(testTicketManager->addToAttractionList(newAttraction), AttractionListException);
    }

    BOOST_FIXTURE_TEST_CASE(clearAttractionList, testFixture) {
        testTicketManager->addToAttractionList(testAttraction1);
        testTicketManager->addToAttractionList(testAttraction2);
        BOOST_CHECK_EQUAL(testTicketManager->getTemporaryAttractionList()->getAttractionListSize(), 2);
        testTicketManager->clearAttractionList();
        BOOST_CHECK_EQUAL(testTicketManager->getTemporaryAttractionList()->getAttractionListSize(), 0);
    }

    BOOST_FIXTURE_TEST_CASE(registerSingleTicket_noAttractionList, testFixture) {
        std::string newTicketId = "całun śmierci";
        SingleTicketPtr tmpTicket = testTicketManager->registerTicket(newTicketId, pt::not_a_date_time, testClient,
                                                                      NORMAL);
        BOOST_CHECK_EQUAL(tmpTicket->getTicketId(), newTicketId);
        BOOST_CHECK_EQUAL(tmpTicket->getActiveDate(), pt::second_clock::local_time());
        BOOST_CHECK_EQUAL(tmpTicket->getOwner(), testClient);
        BOOST_CHECK_EQUAL(tmpTicket->getVisitorType(), NORMAL);
    }

    BOOST_FIXTURE_TEST_CASE(registerSingleTicket_withAttractionList, testFixture) {
        testTicketManager->addToAttractionList(testAttraction1);
        testTicketManager->addToAttractionList(testAttraction2);
        SingleTicketPtr tmpTicket = testTicketManager->registerTicket("całun śmierci", pt::not_a_date_time, testClient,
                                                                      NORMAL);
        BOOST_CHECK_EQUAL(tmpTicket->getAttractions()->getAttractionListSize(), 2);
    }

    BOOST_FIXTURE_TEST_CASE(registerSingleTicketWithOwnerOutsideAquarium_Negative, testFixture) {
        ClientPtr newClient = std::make_shared<Client>("Adam", "Kapuściński", "456623432");
        BOOST_CHECK_THROW(testTicketManager->registerTicket("całun śmierci", pt::not_a_date_time, newClient, NORMAL),
                          TicketException);
    }

    BOOST_FIXTURE_TEST_CASE(registerSingleTicketWithoutOwner_Positive, testFixture) {
        BOOST_CHECK_NO_THROW(testTicketManager->registerTicket("całun śmierci", pt::not_a_date_time, nullptr, NORMAL));
    }

    BOOST_FIXTURE_TEST_CASE(registerExistingSingleTicket_Negative, testFixture) {
        //nie może być dwóch Ticketów o tym samym TicketId
        std::string newTicketId = "całun śmierci";
        testTicketManager->registerTicket(newTicketId, pt::not_a_date_time, testClient, NORMAL);
        BOOST_CHECK_THROW(testTicketManager->registerTicket(newTicketId, pt::not_a_date_time, testClient, STUDENT),
                          TicketException);
    }


    BOOST_FIXTURE_TEST_CASE(registerSingleTicketWithoutSpaceInAquarium_noAttractionList_Negative, testFixture) {
        for (int i = 0; i < testAquarium->getFullCapacity(); i++)
            testTicketManager->registerTicket("całun śmierci" + std::to_string(i), pt::not_a_date_time, testClient,
                                              NORMAL);

        BOOST_CHECK_THROW(testTicketManager->registerTicket("całun śmierci", pt::not_a_date_time, testClient, NORMAL),
                          TicketException);

    }

    BOOST_FIXTURE_TEST_CASE(registerSingleTicketWithoutSpaceInAttraction_withAttractionList_Negative, testFixture) {
        testTicketManager->addToAttractionList(testAttraction1);
        testTicketManager->registerTicket("całun śmierci", pt::not_a_date_time, testClient, NORMAL);
        testTicketManager->addToAttractionList(testAttraction1);
        BOOST_CHECK_THROW(testTicketManager->registerTicket("dementor", pt::not_a_date_time, testClient, NORMAL),
                          TicketException);
    }

    BOOST_FIXTURE_TEST_CASE(registerGroupTicket, testFixture) {
        Group newGroupType = FAMILY;
        int newNumberOfPeople = 5;
        std::string newTicketId = "dziołcha";

        GroupTicketPtr tmp = testTicketManager->registerTicket(newTicketId, pt::not_a_date_time, nullptr,
                                                               newNumberOfPeople, newGroupType);
        BOOST_CHECK_EQUAL(tmp->getGroupType(), newGroupType);
        BOOST_CHECK_EQUAL(tmp->getNumberOfPeople(), newNumberOfPeople);
        BOOST_CHECK_EQUAL(tmp->getTicketId(), newTicketId);
        BOOST_CHECK_EQUAL(tmp->getOwner(), nullptr);
    }

    BOOST_FIXTURE_TEST_CASE(registerGroupTicketWithoutSpaceInAquarium_noAttractionList_Negative, testFixture) {
        testTicketManager->registerTicket("Adam Małysz", pt::not_a_date_time, nullptr, 5, FAMILY);
        testTicketManager->registerTicket("Mariusz Pudzianowski", pt::not_a_date_time, nullptr, 5, TOUR);
        testTicketManager->registerTicket("Jan Paweł II", pt::not_a_date_time, nullptr, 5, TOUR);
        BOOST_CHECK_THROW(
                testTicketManager->registerTicket("Dorota Wellman się nie mieści", pt::not_a_date_time, nullptr, 5,
                                                  FAMILY), TicketException);
    }

    BOOST_FIXTURE_TEST_CASE(registerGroupTicketWithoutSpaceInAttraction_withAttractionList_Negative, testFixture) {
        testTicketManager->addToAttractionList(testAttraction2);
        testTicketManager->registerTicket("Mariusz Pudzianowski", pt::not_a_date_time, nullptr, 5, TOUR);
        testTicketManager->addToAttractionList(testAttraction2);
        BOOST_CHECK_THROW(
                testTicketManager->registerTicket("Rober Kubica nie zdążył", pt::not_a_date_time, nullptr, 5, TOUR),
                TicketException);
    }

    BOOST_FIXTURE_TEST_CASE(registerGroupTicketWithWrongNumberOfPeople_Family_Negative, testFixture) {
        BOOST_CHECK_THROW(
                testTicketManager->registerTicket("Rober Kubica nie zdążył 1", pt::not_a_date_time, nullptr, 1, FAMILY),
                TicketException);
        BOOST_CHECK_NO_THROW(
                testTicketManager->registerTicket("Rober Kubica nie zdążył 2", pt::not_a_date_time, nullptr, 2,
                                                  FAMILY));
        BOOST_CHECK_NO_THROW(
                testTicketManager->registerTicket("Rober Kubica nie zdążył 3", pt::not_a_date_time, nullptr, 5,
                                                  FAMILY));
        BOOST_CHECK_THROW(
                testTicketManager->registerTicket("Rober Kubica nie zdążył 4", pt::not_a_date_time, nullptr, 6, FAMILY),
                TicketException);
    }

    BOOST_FIXTURE_TEST_CASE(registerGroupTicketWithWronfNumberOfPeople_Tour_Negative, testFixture) {
        BOOST_CHECK_THROW(
                testTicketManager->registerTicket("Rober Kubica nie zdążył 1", pt::not_a_date_time, nullptr, 4, TOUR),
                TicketException);
        BOOST_CHECK_NO_THROW(
                testTicketManager->registerTicket("Rober Kubica nie zdążył 2", pt::not_a_date_time, nullptr, 5, TOUR));
        BOOST_CHECK_NO_THROW(
                testTicketManager->registerTicket("Rober Kubica nie zdążył 3", pt::not_a_date_time, nullptr, 10, TOUR));
    }

    BOOST_FIXTURE_TEST_CASE(getSingleTickets, testFixture) {
        testTicketManager->registerTicket("Rober Kubica zdążył", pt::not_a_date_time, nullptr, 5, TOUR);
        testTicketManager->registerTicket("Rober Kubica", pt::not_a_date_time, nullptr, 5, TOUR);
        testTicketManager->registerTicket("całun śmierci", pt::not_a_date_time, testClient, NORMAL);
        testTicketManager->registerTicket("dementor", pt::not_a_date_time, testClient, NORMAL);
        BOOST_CHECK_EQUAL(testTicketManager->getSingleTickets().size(), 2);

    }

    BOOST_FIXTURE_TEST_CASE(getGroupTickets, testFixture) {
        testTicketManager->registerTicket("Rober Kubica zdążył", pt::not_a_date_time, nullptr, 5, TOUR);
        testTicketManager->registerTicket("Rober Kubica", pt::not_a_date_time, nullptr, 5, TOUR);
        testTicketManager->registerTicket("całun śmierci", pt::not_a_date_time, testClient, NORMAL);
        testTicketManager->registerTicket("dementor", pt::not_a_date_time, testClient, NORMAL);
        BOOST_CHECK_EQUAL(testTicketManager->getGroupTickets().size(), 2);

    }

    BOOST_FIXTURE_TEST_CASE(getArchivedTickets, testFixture) {
        GroupTicketPtr tmpGR1 = testTicketManager->registerTicket("Rober Kubica zdążył", pt::not_a_date_time, nullptr,
                                                                  5, TOUR);
        GroupTicketPtr tmpGR2 = testTicketManager->registerTicket("Rober Kubica", pt::ptime(gr::date(2030, 06, 30)),
                                                                  nullptr, 5, TOUR);
        SingleTicketPtr tmpST1 = testTicketManager->registerTicket("całun śmierci", pt::ptime(gr::date(2030, 06, 30)),
                                                                   testClient, NORMAL);
        tmpGR1->setUsed();
        tmpGR2->changeDate(pt::ptime(gr::date(2000, 06, 30)));
        BOOST_CHECK_EQUAL(testTicketManager->getArchivedTickets().size(), 2);
    }

    BOOST_FIXTURE_TEST_CASE(getActiveTickets, testFixture) {
        GroupTicketPtr tmpGR1 = testTicketManager->registerTicket("Rober Kubica zdążył", pt::not_a_date_time, nullptr,
                                                                  5, TOUR);
        GroupTicketPtr tmpGR2 = testTicketManager->registerTicket("Rober Kubica", pt::ptime(gr::date(2030, 06, 30)),
                                                                  nullptr, 5, TOUR);
        SingleTicketPtr tmpST1 = testTicketManager->registerTicket("całun śmierci", pt::ptime(gr::date(2030, 06, 30)),
                                                                   testClient, NORMAL);
        tmpGR1->setUsed();
        tmpGR2->changeDate(pt::ptime(gr::date(2000, 06, 30)));
        BOOST_CHECK_EQUAL(testTicketManager->getActiveTickets().size(), 1);
    }

    BOOST_FIXTURE_TEST_CASE(getByTicketId, testFixture) {
        GroupTicketPtr tmpGR1 = testTicketManager->registerTicket("Rober Kubica zdążył", pt::not_a_date_time, nullptr,
                                                                  5, TOUR);
        GroupTicketPtr tmpGR2 = testTicketManager->registerTicket("Rober Kubica", pt::ptime(gr::date(2030, 06, 30)),
                                                                  nullptr, 5, TOUR);
        BOOST_CHECK_EQUAL(testTicketManager->getByTicketId("Rober Kubica")->getTicketId(), tmpGR2->getTicketId());
    }

    BOOST_FIXTURE_TEST_CASE(getByIndex, testFixture) {
        GroupTicketPtr tmpGR1 = testTicketManager->registerTicket("Rober Kubica zdążył", pt::not_a_date_time, nullptr,
                                                                  5, TOUR);
        GroupTicketPtr tmpGR2 = testTicketManager->registerTicket("Rober Kubica", pt::ptime(gr::date(2030, 06, 30)),
                                                                  nullptr, 5, TOUR);
        BOOST_CHECK_EQUAL(testTicketManager->getByIndex(0)->getTicketId(), tmpGR1->getTicketId());
    }

    BOOST_FIXTURE_TEST_CASE(overloadedOutOperator, testFixture){
        std::ostringstream out;
        out << *testTicketManager;
        BOOST_TEST_MESSAGE(out.str());
    }

BOOST_AUTO_TEST_SUITE_END()