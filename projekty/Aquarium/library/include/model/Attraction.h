//
// Created by student on 08.06.2020.
//

#ifndef CARRENTAL_ATTRACTION_H
#define CARRENTAL_ATTRACTION_H


#include <string>
#include <stdexcept>

class Attraction {
private:
    double Cost;
    unsigned int MaxVisitors;
    std::string AttractionName;
public:
    Attraction(double cost, unsigned int maxVisitors, const std::string &attractionName);

    double getCost() const;

    int getMaxVisitors() const;

    const std::string &getAttractionName() const;

    void setCost(double cost);

    void setMaxVisitors(unsigned int maxVisitors);

    void setAttractionName(const std::string &attractionName);

    friend std::ostream &operator<<(std::ostream &out, const Attraction &attraction);
};

std::ostream &operator<<(std::ostream &out, const Attraction &attraction);

class AttractionException : public std::logic_error {
public:
    explicit AttractionException(const std::string &arg);
};

#endif //CARRENTAL_ATTRACTION_H
