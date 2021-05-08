//
// Created by student on 08.06.2020.
//

#include "Aquarium.h"
#include "Attraction.h"

AquariumException::AquariumException(const std::string &arg) : logic_error(arg) {}

Aquarium::Aquarium(double baseTicketPrice, int baseCapacity) : BaseTicketPrice(baseTicketPrice),
                                                                        BaseCapacity(baseCapacity) {}

Aquarium::~Aquarium() {
    delete ClientMan;
    delete TicketMan;
    delete MainAttractionList;
}

double Aquarium::getBaseTicketPrice() const {
    return BaseTicketPrice;
}

void Aquarium::setBaseTicketPrice(double baseTicketPrice) {
    if (baseTicketPrice < 0) throw AquariumException("baseTicketPrice cannot be < 0");
    BaseTicketPrice = baseTicketPrice;
}

int Aquarium::getBaseCapacity() const {
    return BaseCapacity;
}

void Aquarium::setBaseCapacity(unsigned int baseCapacity) {
    BaseCapacity = baseCapacity;
}

ClientManager *Aquarium::clients() {
    return ClientMan;
}

TicketManager *Aquarium::tickets() {
    return TicketMan;
}

const AttractionList *Aquarium::attractions() const {
    return MainAttractionList;
}

int Aquarium::getFullCapacity() const {
    int attractionsCapacity = 0;
    for (int i = 0; i < MainAttractionList->getAttractionListSize(); i++)
        attractionsCapacity += MainAttractionList->getAttractionByIndex(i)->getMaxVisitors();
    return attractionsCapacity + getBaseCapacity();
}

void Aquarium::addToAttractionList(double cost, unsigned int maxVisitors, std::string name) {
    if (cost < 0) throw AttractionException("Cost cannot be < 0");
    if (name.empty()) throw AttractionException("Attraction's Name cannot be empty");

    AttractionPtr tmp = std::make_shared<Attraction>(cost, maxVisitors, name);
    MainAttractionList->addAttration(tmp);
}

void Aquarium::removeFromAttractionList(std::string name) {
    MainAttractionList->removeAttraction(name);
}

std::ostream &operator<<(std::ostream &out, const Aquarium &aquarium) {
    out << "Aquarium\n";
    out << "BaseTicketPrice: " << aquarium.getBaseTicketPrice() << "\n";
    out << "BaseCapacity: " << aquarium.getBaseCapacity() << "\n";
    out << "FullCapacity: " << aquarium.getFullCapacity() << "\n";
    out << "Attractions: [" << *aquarium.attractions() << "]\n" << "\n";
    out << *aquarium.TicketMan << "\n";
    out << *aquarium.ClientMan << "\n";
    return out;
}


