//
// Created by student on 08.06.2020.
//

#ifndef CARRENTAL_SINGLETICKET_H
#define CARRENTAL_SINGLETICKET_H

#include "Ticket.h"
#include "Visitor.h"

class SingleTicket : public Ticket {
private:
    Visitor VisitorType;
public:
    SingleTicket(const std::string &ticketId, const pt::ptime &activeData, double basePrice,
                 AttractionList *attractions, const ClientPtr &owner, Visitor visitorType);

    double getFinalPrice() const override;

    Visitor getVisitorType() const;

    void changeDate(pt::ptime tmp_time) override;

    friend std::ostream &operator<<(std::ostream &out, const SingleTicket &singleTicket);
};

std::ostream &operator<<(std::ostream &out, const SingleTicket &singleTicket);

std::string visitorToString(Visitor visitor);

#endif //CARRENTAL_SINGLETICKET_H
