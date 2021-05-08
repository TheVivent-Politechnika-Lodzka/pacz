//
// Created by student on 08.06.2020.
//

#ifndef CARRENTAL_GROUPTICKET_H
#define CARRENTAL_GROUPTICKET_H

#include "Ticket.h"
#include "Group.h"

class GroupTicket : public Ticket {
private:
    unsigned int NumberOfPeople;
    Group GroupType;
public:
    GroupTicket(const std::string &ticketId, const pt::ptime &activeData, double basePrice, AttractionList *attractions,
                const ClientPtr &owner, unsigned int numberOfPeople, Group groupType);

    unsigned int getNumberOfPeople() const;

    Group getGroupType() const;

    double getFinalPrice() const override;

    void changeDate(pt::ptime tmp_time) override;

    friend std::ostream &operator<<(std::ostream &out, const GroupTicket &groupTicket);
};

std::ostream &operator<<(std::ostream &out, const GroupTicket &groupTicket);

std::string groupToString(Group group);

#endif //CARRENTAL_GROUPTICKET_H
