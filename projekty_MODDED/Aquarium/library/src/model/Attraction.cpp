//
// Created by student on 08.06.2020.
//

#include "Attraction.h"
#include <iostream>

AttractionException::AttractionException(const std::string &arg) : logic_error(arg) {}

double Attraction::getCost() const {
    return Cost;
}

void Attraction::setCost(double cost) {
    if (cost < 0) throw AttractionException("Cost cannot be < 0");
    Cost = cost;
}

int Attraction::getMaxVisitors() const {
    return MaxVisitors;
}

void Attraction::setMaxVisitors(unsigned int maxVisitors) {
    MaxVisitors = maxVisitors;
}

const std::string &Attraction::getAttractionName() const {
    return AttractionName;
}

void Attraction::setAttractionName(const std::string &attractionName) {
    if (attractionName.empty()) throw AttractionException("Attraction's Name cannot be empty");
    AttractionName = attractionName;
}

Attraction::Attraction(double cost, unsigned int maxVisitors, const std::string &attractionName) : Cost(cost),
                                                                                                   MaxVisitors(
                                                                                                           maxVisitors),
                                                                                                   AttractionName(
                                                                                                           attractionName) {}

std::ostream &operator<<(std::ostream &out, const Attraction &attraction) {
    out << "AttractionName: " << attraction.getAttractionName() << " ";
    out << "Cost: " << attraction.getCost() << " ";
    out << "MaxVisitors: " << attraction.getMaxVisitors() << " ";
    return out;
}
