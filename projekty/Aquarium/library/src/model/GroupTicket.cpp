//
// Created by student on 08.06.2020.
//

#include "GroupTicket.h"

GroupTicket::GroupTicket(const std::string &ticketId, const pt::ptime &activeData, double basePrice,
                         AttractionList *attractions, const ClientPtr &owner, unsigned int numberOfPeople,
                         Group groupType) : Ticket(ticketId, activeData, basePrice, attractions, owner),
                                            NumberOfPeople(numberOfPeople), GroupType(groupType) {}

unsigned int GroupTicket::getNumberOfPeople() const {
    return NumberOfPeople;
}

double GroupTicket::getFinalPrice() const {
    double suma = Ticket::getFinalPrice();
    if (GroupType == FAMILY) {
        suma *= (1.0 - (getNumberOfPeople() / 10.0));
    } else if (GroupType == TOUR) {
        if (getNumberOfPeople() > 20) suma *= 0.5;
        else suma *= (1.0 - (getNumberOfPeople()) / 50.0);
    }
    return suma;
}

Group GroupTicket::getGroupType() const {
    return GroupType;
}

void GroupTicket::changeDate(pt::ptime tmp_time) {

    if (pt::second_clock::local_time() < (getActiveDate() - pt::hours(168))) {
        Ticket::setActiveDate(tmp_time);
    } else {
        throw TicketException("You have entered the wrong date.");
    }

}

std::ostream &operator<<(std::ostream &out, const GroupTicket &groupTicket) {
    out << "GroupTicket for: " << groupToString(groupTicket.getGroupType()) << " ";
    out << "NumberOfPeople: " << groupTicket.getNumberOfPeople() << " ";
    groupTicket.print(out);
    return out;
}

std::string groupToString(Group group) {

    std::string result;
    switch (group) {
        case FAMILY:
            result = "FAMILY";
            break;
        case TOUR:
            result = "TOUR";
            break;
        default:
            result = "UNKNOWN";
    }
    return result;

}
