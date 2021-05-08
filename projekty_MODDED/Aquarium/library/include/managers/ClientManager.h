//
// Created by student on 08.06.2020.
//

#ifndef CARRENTAL_CLIENTMANAGER_H
#define CARRENTAL_CLIENTMANAGER_H


#include "typedefs.h"
#include "Repository.h"

class Aquarium;

class ClientManager {
private:
    Repository<ClientPtr> Clients;
    Aquarium *LocalAquarium;
public:
    ClientManager(Aquarium *localAquarium);

    virtual ~ClientManager();

    const Aquarium *getLocalAquarium() const;

    ClientPtr registerClient(const std::string firstName, const std::string lastName, const std::string pesel);

    std::list<ClientPtr> getArchivedClients() const;

    std::list<ClientPtr> getActiveClients() const;

    ClientPtr getByPesel(const std::string pesel) const;

    ClientPtr getByIndex(const unsigned int index) const;

    void archiveClient(const std::string pesel);

    friend std::ostream &operator<<(std::ostream &out, const ClientManager &clientManager);

};

std::ostream &operator<<(std::ostream &out, const ClientManager &clientManager);

#endif //CARRENTAL_CLIENTMANAGER_H
