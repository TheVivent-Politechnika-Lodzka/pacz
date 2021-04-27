//
// Created by student on 08.06.2020.
//

#include <algorithm>
#include <iostream>
#include "AttractionList.h"
#include "Attraction.h"


AttractionListException::AttractionListException(const std::string &arg) : logic_error(arg) {}

AttractionPtr AttractionList::getAttractionByIndex(int index) const {
    return Attractions[index];
}

int AttractionList::getAttractionListSize() const {
    if (Attractions.empty()) return 0;
    return Attractions.size();
}

double AttractionList::getTotalCost() const {
    double result = 0;
    for (AttractionPtr ptr : Attractions) {
        result += ptr->getCost();
    }
    return result;
}

void AttractionList::addAttration(AttractionPtr attraction) {
    for (AttractionPtr ptr : Attractions) {
        if (ptr->getAttractionName() == attraction->getAttractionName())
            throw AttractionListException("Cannot add two identical Attractions to AttractionList");
    }

    //zachowywanie KOPII Attraction
    Attractions.push_back(std::make_shared<Attraction>(*attraction));
}

void AttractionList::removeAttraction(std::string name) {
    AttractionPredicate predicate = [name](AttractionPtr attraction) -> bool {
        return attraction->getAttractionName() == name;
    };
    auto new_end = std::remove_if(Attractions.begin(), Attractions.end(), predicate);
    Attractions.erase(new_end, Attractions.end());
}

AttractionPtr AttractionList::getAttractionByName(std::string name) const {
    for (AttractionPtr ptr : Attractions)
        if (ptr->getAttractionName() == name) return ptr;
    return nullptr;
}

AttractionList::AttractionList() {}

AttractionList::AttractionList(const AttractionList *copy) {
    for (int i = 0; i < copy->getAttractionListSize(); i++)
        this->addAttration(copy->Attractions[i]);
}

AttractionList *AttractionList::clone() const {
    return new AttractionList(this);
}


std::ostream &operator<<(std::ostream &out, const AttractionList &attractionList) {
    out << "AttractionListSize: " << attractionList.getAttractionListSize() << " ";
    out << "AttractionListTotalCost: " << attractionList.getTotalCost() << " ";
    out << "Attractions: [";
    for (AttractionPtr ptr : attractionList.Attractions)
        out << "[" << *ptr << "]";
    out << "]";
    return out;
}
