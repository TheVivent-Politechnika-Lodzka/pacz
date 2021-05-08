//
// Created by student on 08.06.2020.
//

#ifndef CARRENTAL_ATTRACTIONLIST_H
#define CARRENTAL_ATTRACTIONLIST_H


#include <vector>
#include "typedefs.h"

class AttractionList {
private:
    std::vector<AttractionPtr> Attractions;
public:
    AttractionList();

    AttractionPtr getAttractionByIndex(const int index) const;

    AttractionPtr getAttractionByName(const std::string name) const;

    int getAttractionListSize() const;

    double getTotalCost() const;

    void addAttration(AttractionPtr attraction);

    void removeAttraction(const std::string name);

    //wykorzystany wzorzec projektowy:
    //http://cpp0x.pl/kursy/Wzorce-projektowe/Wzorce-kreacyjne/prototyp/166
    AttractionList *clone() const;

    AttractionList(const AttractionList *copy);

    friend std::ostream &operator<<(std::ostream &out, const AttractionList &attractionList);
};

std::ostream &operator<<(std::ostream &out, const AttractionList &attractionList);

class AttractionListException : public std::logic_error {
public:
    explicit AttractionListException(const std::string &arg);
};

#endif //CARRENTAL_ATTRACTIONLIST_H
