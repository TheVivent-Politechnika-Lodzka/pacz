//
// Created by student on 08.06.2020.
//


#include "SingleTicket.h"

double SingleTicket::getFinalPrice() const {
    double suma = Ticket::getFinalPrice();
    switch (VisitorType) {
        case (STUDENT): {
            suma *= (0.5);
            break;
        }
        case (SENIOR): {
            suma *= (0.2);
            break;
        }
        case (KID): {
            suma *= (0.7);
            break;
        }
        case (BLIND): {
            suma = 0;
            break;
        }
        case (NORMAL): {
            break;
        }
        default: {
            break;
        }
    }
    return suma;
}

void SingleTicket::changeDate(pt::ptime tmp_time) {

    if (pt::second_clock::local_time() < (getActiveDate() - pt::hours(72))) {
        Ticket::setActiveDate(tmp_time);
    } else {
        throw TicketException("You have entered the wrong date.");
    }

}

SingleTicket::SingleTicket(const std::string &ticketId, const pt::ptime &activeData, double basePrice,
                           AttractionList *attractions, const ClientPtr &owner, Visitor visitorType) : Ticket(ticketId,
                                                                                                              activeData,
                                                                                                              basePrice,
                                                                                                              attractions,
                                                                                                              owner),
                                                                                                       VisitorType(
                                                                                                               visitorType) {}

Visitor SingleTicket::getVisitorType() const {
    return VisitorType;
}

std::ostream &operator<<(std::ostream &out, const SingleTicket &singleTicket) {
    out << "SignleTicket for: " << visitorToString(singleTicket.getVisitorType()) << " ";
    singleTicket.print(out);
    return out;
}

std::string visitorToString(Visitor visitor) {

    std::string result;
    switch (visitor) {
        case STUDENT:
            result = "STUDENT";
            break;
        case SENIOR:
            result = "SENIOR";
            break;
        case KID:
            result = "KID";
            break;
        case BLIND:
            result = "BLIND";
            break;
        case NORMAL:
            result = "NORMAL";
            break;
        default:
            result = "UNKNOWN";
    }
    return result;

}
