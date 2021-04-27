//
// Created by student on 11.06.2020.
//

#include <boost/test/unit_test.hpp>
#include "typedefs.h"
#include "Client.h"
#include "Repository.h"

BOOST_AUTO_TEST_SUITE(RepositoryTest)

    struct testFixture {

        Repository<ClientPtr> ClientRepo;
        std::string testName = "Adam";
        ClientPtr testClient1 = std::make_shared<Client>(testName, "Kapuściński", "123456789");

        testFixture() {
            ClientRepo.add(testClient1);
        }

        ~testFixture() {

        }
    };


    BOOST_FIXTURE_TEST_CASE(size, testFixture) {
        BOOST_CHECK_EQUAL(ClientRepo.size(), 1);
    }

    BOOST_FIXTURE_TEST_CASE(add, testFixture) {
        ClientPtr newClient = std::make_shared<Client>("Damian", "Szczecinski", "987654321");
        BOOST_CHECK_EQUAL(ClientRepo.size(), 1);
        ClientRepo.add(newClient);
        BOOST_CHECK_EQUAL(ClientRepo.size(), 2);
    }

    BOOST_FIXTURE_TEST_CASE(get, testFixture) {
        BOOST_CHECK_EQUAL(ClientRepo.get(0), testClient1);
    }

    BOOST_FIXTURE_TEST_CASE(find, testFixture) {
        std::string name = testClient1->getFirstName();
        ClientPredicate predicate = [name](ClientPtr client) -> bool {
            return client->getFirstName() == name;
        };
        BOOST_CHECK_EQUAL(ClientRepo.find(predicate), testClient1);
    }

    BOOST_FIXTURE_TEST_CASE(findALL, testFixture) {
        ClientPtr testClient2 = std::make_shared<Client>(testName, "Kapuściński", "123456789");
        ClientRepo.add(testClient2);
        std::string name = testClient1->getFirstName();
        ClientPredicate predicate = [name](ClientPtr client) -> bool {
            return client->getFirstName() == name;
        };
        BOOST_CHECK_EQUAL(ClientRepo.findAll(predicate).size(), 2);
    }

    BOOST_FIXTURE_TEST_CASE(remove, testFixture) {
        BOOST_CHECK_EQUAL(ClientRepo.size(), 1);
        ClientRepo.remove(testClient1);
        BOOST_CHECK_EQUAL(ClientRepo.size(), 0);
    }

BOOST_AUTO_TEST_SUITE_END()