//
// Created by student on 08.06.2020.
//

#ifndef CARRENTAL_TICKET_H
#define CARRENTAL_TICKET_H

#include <list>
#include <string>
#include <boost/date_time.hpp>
#include "typedefs.h"

namespace pt = boost::posix_time;
namespace gr = boost::gregorian;

class AttractionList;

class Ticket {
private:
    std::string TicketID;
    pt::ptime ActiveDate;
    double BasePrice;
    bool IsUsed = false;
    AttractionList *Attractions;
    ClientPtr Owner;

protected:
    void setActiveDate(const pt::ptime &activeDate);

    void print(std::ostream &out) const;

public:
    Ticket(const std::string &ticketId, const pt::ptime &activeData, double basePrice, AttractionList *attractions,
           const ClientPtr &owner);

    virtual ~Ticket();

    double getBasePrice() const;

    const std::string &getTicketId() const;

    const pt::ptime &getActiveDate() const;

    bool isUsed() const;

    const AttractionList *getAttractions() const;

    const ClientPtr &getOwner() const;

    virtual double getFinalPrice() const;

    virtual void changeDate(pt::ptime tmp_time) = 0;

    void setUsed();

    friend std::ostream &operator<<(std::ostream &out, const Ticket &ticket);

};

std::ostream &operator<<(std::ostream &out, const Ticket &ticket);


class TicketException : public std::logic_error {
public:
    explicit TicketException(const std::string &arg);
};

#endif //CARRENTAL_TICKET_H
