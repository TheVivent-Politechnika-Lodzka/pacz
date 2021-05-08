//
// Created by student on 08.06.2020.
//

#include "ClientManager.h"
#include "Aquarium.h"
#include "Client.h"

ClientManager::ClientManager(Aquarium *localAquarium) : LocalAquarium(localAquarium) {}

ClientManager::~ClientManager() {

}

const Aquarium *ClientManager::getLocalAquarium() const {
    return LocalAquarium;
}

ClientPtr
ClientManager::registerClient(const std::string firstName, const std::string lastName, const std::string pesel) {

    if (firstName.empty()) throw ClientException("Client needs first name");

    if (lastName.empty()) throw ClientException("Client needs last name");

    if (pesel.empty()) throw ClientException("Client needs PESEL");

    ClientPredicate predicate = [pesel](ClientPtr client) -> bool {
        return client->getPesel() == pesel;
    };

    if (Clients.find(predicate) != nullptr)
        throw ClientException("Client with this PESEL already exists");

    ClientPtr tmp = std::make_shared<Client>(firstName, lastName, pesel);

    Clients.add(tmp);

    return tmp;
}

std::list<ClientPtr> ClientManager::getArchivedClients() const {

    std::list<ClientPtr> result;
    ClientPredicate predicate = [](ClientPtr client) -> bool {
        return (client->isArchived());
    };

    result = Clients.findAll(predicate);
    return result;
}

std::list<ClientPtr> ClientManager::getActiveClients() const {

    std::list<ClientPtr> result;
    ClientPredicate predicate = [](ClientPtr client) -> bool {
        return (!client->isArchived());
    };

    result = Clients.findAll(predicate);
    return result;
}

ClientPtr ClientManager::getByPesel(const std::string pesel) const {
    ClientPredicate predicate = [pesel](ClientPtr client) -> bool {
        return client->getPesel() == pesel;
    };
    return Clients.find(predicate);
}

ClientPtr ClientManager::getByIndex(const unsigned int index) const {
    return Clients.get(index);
}

void ClientManager::archiveClient(const std::string pesel) {

}

std::ostream &operator<<(std::ostream &out, const ClientManager &clientManager) {
    out << "ClentManager\n";
    for (int i = 0; i < clientManager.Clients.size(); i++) {
        out << *clientManager.getByIndex(i) << "\n";
    }
    return out;
}
