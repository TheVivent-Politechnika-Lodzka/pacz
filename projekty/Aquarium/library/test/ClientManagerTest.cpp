//
// Created by student on 11.06.2020.
//

#include <boost/test/unit_test.hpp>
#include "ClientManager.h"
#include "Client.h"
#include "Aquarium.h"

BOOST_AUTO_TEST_SUITE(ClientManagerTest)

    struct testFixture {


        Aquarium *testAquarium;
        ClientManager *testClientManager;

        testFixture() {
            testAquarium = new Aquarium(6, 9);
            testClientManager = testAquarium->clients();
        }

        ~testFixture() {
            delete testAquarium;
        }
    };

    BOOST_FIXTURE_TEST_CASE(Constructor, testFixture) {
        BOOST_CHECK_EQUAL(testClientManager->getLocalAquarium(), testAquarium);
    }

    BOOST_FIXTURE_TEST_CASE(registerClient, testFixture) {
        std::string tmpFn = "Eustachy";
        std::string tmpLn = "Motyka";
        std::string tmpPESEL = "gdzieJestMuriel";
        ClientPtr tmpCl1 = testClientManager->registerClient(tmpFn, tmpLn, tmpPESEL);
        BOOST_CHECK_EQUAL(tmpCl1->getFirstName(), tmpFn);
        BOOST_CHECK_EQUAL(tmpCl1->getLastName(), tmpLn);
        BOOST_CHECK_EQUAL(tmpCl1->getPesel(), tmpPESEL);
        BOOST_CHECK_EQUAL(tmpCl1->isArchived(), false);
    }

    BOOST_FIXTURE_TEST_CASE(registerExistingClient_Negative, testFixture) {
        //klienci identyfikowaniS są po PESELu
        std::string PESEL = "Piosenkarz";
        testClientManager->registerClient("Paweł", "Golec", PESEL);
        BOOST_CHECK_THROW(testClientManager->registerClient("Łukasz", "Golec", PESEL), ClientException);
    }

    BOOST_FIXTURE_TEST_CASE(getArchivedClients, testFixture) {
        ClientPtr tmpCl1 = testClientManager->registerClient("Weronika", "Pacyniak", "ANALmajster");
        ClientPtr tmpCl2 = testClientManager->registerClient("Paweł", "Jaśpiński", "Pierdolot/ALLmajster");
        ClientPtr tmpCl3 = testClientManager->registerClient("Daniel", "Rutkowski", "POBImajster");
        ClientPtr tmpCl4 = testClientManager->registerClient("Damian", "Szafarczyk", "PEJSmajster");
        ClientPtr tmpCl5 = testClientManager->registerClient("Adam", "Kapuściński", "SYSOPmajster");
        tmpCl1->setArchived();
        tmpCl3->setArchived();
        tmpCl5->setArchived();
        BOOST_CHECK_EQUAL(testClientManager->getArchivedClients().size(), 3);
    }

    BOOST_FIXTURE_TEST_CASE(getActiveClients, testFixture) {
        ClientPtr tmpCl1 = testClientManager->registerClient("Janusz", "Nosacz", "MamBojoweZadanie");
        ClientPtr tmpCl2 = testClientManager->registerClient("Grażyna", "Nosacz", "PoproszęKierownika");
        ClientPtr tmpCl3 = testClientManager->registerClient("Pioter", "Nosacz", "AleTate");
        tmpCl2->setArchived();
        BOOST_CHECK_EQUAL(testClientManager->getActiveClients().size(), 2);
    }

    BOOST_FIXTURE_TEST_CASE(getByPesel, testFixture) {
        std::string pesel1 = "GrubeBity";
        std::string pesel2 = "LastKrysmas";
        ClientPtr tmpCl1 = testClientManager->registerClient("Tiger", "Rapier", pesel1);
        ClientPtr tmpCl2 = testClientManager->registerClient("Kobra", "Rapier", pesel2);
        BOOST_CHECK_EQUAL(testClientManager->getByPesel(pesel1)->getPesel(), tmpCl1->getPesel());
        BOOST_CHECK_EQUAL(testClientManager->getByPesel(pesel2)->getPesel(), tmpCl2->getPesel());
    }

    BOOST_FIXTURE_TEST_CASE(getByIndex, testFixture) {
        ClientPtr tmpCl1 = testClientManager->registerClient("Dorota", "Welman", "GrubaSprawa");
        ClientPtr tmpCl2 = testClientManager->registerClient("Marcin", "Prokop", "Windows10Pro'kop");
        BOOST_CHECK_EQUAL(testClientManager->getByIndex(0)->getPesel(), tmpCl1->getPesel());
        BOOST_CHECK_EQUAL(testClientManager->getByIndex(1)->getPesel(), tmpCl2->getPesel());
    }

    BOOST_FIXTURE_TEST_CASE(archiveClient, testFixture) {
        ClientPtr tmpCl1 = testClientManager->registerClient("Zbyszko", "z Bogdańca", "gdzieDanusia?");
        ClientPtr tmpCl2 = testClientManager->registerClient("Jagienka", "ze Zgorzelic", "wiecznyNr2");
        tmpCl1->setArchived();
        BOOST_CHECK_EQUAL(tmpCl1->isArchived(), true);
        BOOST_CHECK_EQUAL(tmpCl2->isArchived(), false);
    }

    BOOST_FIXTURE_TEST_CASE(overloadedOutOperator, testFixture){
        std::ostringstream out;
        out << *testClientManager;
        BOOST_TEST_MESSAGE(out.str());
    }

BOOST_AUTO_TEST_SUITE_END()