//
// Created by student on 08.06.2020.
//

#ifndef CARRENTAL_AQUARIUM_H
#define CARRENTAL_AQUARIUM_H


#include <stdexcept>
#include "ClientManager.h"
#include "TicketManager.h"
#include "AttractionList.h"

class Aquarium {
private:
    ClientManager *ClientMan = new ClientManager(this);
    TicketManager *TicketMan = new TicketManager(this);
    AttractionList *MainAttractionList = new AttractionList();
    double BaseTicketPrice;
    int BaseCapacity;
public:
    Aquarium(double baseTicketPrice, int baseCapacity);

    virtual ~Aquarium();

    ClientManager *clients();

    TicketManager *tickets();

    const AttractionList *attractions() const;

    double getBaseTicketPrice() const;

    int getBaseCapacity() const;

    int getFullCapacity() const;

    void setBaseTicketPrice(double baseTicketPrice);

    void setBaseCapacity(unsigned int baseCapacity);

    void addToAttractionList(double cost, unsigned int maxVisitors, std::string name);

    void removeFromAttractionList(std::string name);

    friend std::ostream &operator<<(std::ostream &out, const Aquarium &aquarium);

};

std::ostream &operator<<(std::ostream &out, const Aquarium &aquarium);

class AquariumException : public std::logic_error {
public:
    explicit AquariumException(const std::string &arg);
};

#endif //CARRENTAL_AQUARIUM_H
