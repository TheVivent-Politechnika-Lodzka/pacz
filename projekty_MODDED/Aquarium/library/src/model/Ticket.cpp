//
// Created by student on 08.06.2020.
//

#include <iostream>
#include "Ticket.h"
#include "AttractionList.h"
#include "SingleTicket.h"
#include "GroupTicket.h"
#include "Client.h"

TicketException::TicketException(const std::string &arg) : logic_error(arg) {}

Ticket::Ticket(const std::string &ticketId, const pt::ptime &activeData, double basePrice, AttractionList *attractions,
               const ClientPtr &owner) : TicketID(ticketId), ActiveDate(activeData), BasePrice(basePrice),
                                         Attractions(attractions), Owner(owner) {}

Ticket::~Ticket() {
    delete Attractions;
}

const std::string &Ticket::getTicketId() const {
    return TicketID;
}

const pt::ptime &Ticket::getActiveDate() const {
    return ActiveDate;
}

double Ticket::getBasePrice() const {
    return BasePrice;
}

bool Ticket::isUsed() const {
    return IsUsed;
}

const AttractionList *Ticket::getAttractions() const {
    return Attractions;
}

const ClientPtr &Ticket::getOwner() const {
    return Owner;
}

double Ticket::getFinalPrice() const {
    if (Attractions == nullptr) return getBasePrice();
    return (getBasePrice() + Attractions->getTotalCost());
}

void Ticket::setUsed() {
    IsUsed = true;
}

void Ticket::setActiveDate(const pt::ptime &activeDate) {
    ActiveDate = activeDate;
}

void Ticket::print(std::ostream &out) const {
    out << "TicketId: " << getTicketId() << " ";
    out << "ActiveDate: " << getActiveDate() << " ";
    out << "BasePrice: " << getBasePrice() << " ";
    out << "Final Price: " << getFinalPrice() << " ";
    out << "IsUsed: " << (isUsed() ? "yes" : "no") << " ";
    out << "Owner: [";
    if (Owner == nullptr) out << "No Owner";
    else out << *Owner;
    out << "] ";

    out << "AttractionList: [";
    if (Attractions != nullptr)
        out << *getAttractions();
    out << "] ";
}

std::ostream &operator<<(std::ostream &out, const Ticket &ticket) {
    const SingleTicket *tmpST1 = dynamic_cast<const SingleTicket *>(&ticket);
    if (tmpST1 != nullptr) {
        out << *tmpST1 << " ";
    } else {
        const GroupTicket *tmpGT1 = dynamic_cast<const GroupTicket *>(&ticket);
        out << *tmpGT1 << " ";
    }
    return out;
}

