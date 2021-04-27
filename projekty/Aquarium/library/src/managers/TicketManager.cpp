//
// Created by student on 08.06.2020.
//
#include <iostream>
#include "TicketManager.h"
#include "Ticket.h"
#include "SingleTicket.h"
#include "GroupTicket.h"
#include "Aquarium.h"
#include "AttractionList.h"
#include "Attraction.h"
#include "Client.h"


TicketManager::TicketManager(Aquarium *localAquarium) : LocalAquarium(localAquarium) {}


void TicketManager::checkTicket(const std::string &ticketId, const pt::ptime &activeDate, unsigned int numberOfPeople,
                                const ClientPtr &owner) {
    //check if ticketId is empty
    if (ticketId.empty()) throw TicketException("Ticket needs ticket ID");

    //check if ticket already exists:
    TicketPredicate predicate = [ticketId](TicketPtr ticket) -> bool {
        return ticket->getTicketId() == ticketId;
    };
    if (Tickets.find(predicate) != nullptr)
        throw TicketException("Ticket with this id already exists");

    //check if date is not from past
    if (activeDate != pt::not_a_date_time &&
        activeDate < pt::second_clock::local_time())
        throw TicketException("You cant create Ticket for past time");

    predicate = [activeDate](TicketPtr ticket) -> bool {
        return ticket->getActiveDate().date() == activeDate.date();
    };

    std::list<TicketPtr> ticketsThisDate = Tickets.findAll(predicate);

    //check if there is enough space in Aquarium
    int PeopleThisDay = 0;
    for (TicketPtr ptr : ticketsThisDate) {
        GroupTicket *tmp = dynamic_cast<GroupTicket *>(ptr.get());
        if (tmp == nullptr) PeopleThisDay++;
        else PeopleThisDay += tmp->getNumberOfPeople();
    }

    PeopleThisDay += numberOfPeople;
    if (PeopleThisDay > LocalAquarium->getFullCapacity())
        throw TicketException("Not enough space for new ticket this date");

    //check if there is enough space for all attractions
    for (int i = 0; i < TemporaryAttractionList->getAttractionListSize(); i++) {
        std::string attractionName = TemporaryAttractionList->getAttractionByIndex(i)->getAttractionName();
        PeopleThisDay = 0;
        //count people on attraction this date
        for (const TicketPtr &ptr : ticketsThisDate)
            if (ptr->getAttractions()->getAttractionByName(attractionName) != nullptr) {
                GroupTicket *tmp = dynamic_cast<GroupTicket *>(ptr.get());
                if (tmp == nullptr) PeopleThisDay++;
                else PeopleThisDay += tmp->getNumberOfPeople();
            };
        //check if there is enough space
        if (PeopleThisDay + numberOfPeople >
            LocalAquarium->attractions()->getAttractionByName(attractionName)->getMaxVisitors())
            throw TicketException("There is not enough space for attraction " + attractionName + "this date");
    }

    //check if client exists in Aquarium
    if (owner != nullptr &&
        owner.get() != LocalAquarium->clients()->getByPesel(owner->getPesel()).get())
        throw TicketException("This client is not in Aquarium");

    return;
}

SingleTicketPtr TicketManager::registerTicket(const std::string &ticketId, pt::ptime activeDate, const ClientPtr &owner,
                                              const Visitor visitorType) {


    if (activeDate == pt::not_a_date_time) activeDate = pt::second_clock::local_time();

    checkTicket(ticketId, activeDate, 1, owner);

    SingleTicketPtr tmp = std::make_shared<SingleTicket>(
            ticketId, activeDate, LocalAquarium->getBaseTicketPrice(), TemporaryAttractionList->clone(), owner,
            visitorType);

    Tickets.add(tmp);
    clearAttractionList();
    return tmp;
}

GroupTicketPtr TicketManager::registerTicket(const std::string &ticketId, pt::ptime activeDate, const ClientPtr &owner,
                                             const unsigned int numberOfPeople, Group groupType) {

    if (activeDate == pt::not_a_date_time) activeDate = pt::second_clock::local_time();

    checkTicket(ticketId, activeDate, numberOfPeople, owner);

    if (groupType == FAMILY &&
        (numberOfPeople < 2 || numberOfPeople > 5))
        throw TicketException("Family Ticket must have min 2 numberOfPeople and max of 5");
    if (groupType == TOUR &&
        numberOfPeople < 5)
        throw TicketException("Tour Ticket must have min 5 numberOfPeople");

    GroupTicketPtr tmp = std::make_shared<GroupTicket>(
            ticketId, activeDate, LocalAquarium->getBaseTicketPrice(), TemporaryAttractionList->clone(), owner,
            numberOfPeople, groupType);

    Tickets.add(tmp);
    clearAttractionList();
    return tmp;
}

void TicketManager::addToAttractionList(AttractionPtr attraction) {
    if (LocalAquarium->attractions()->getAttractionByName(attraction->getAttractionName()).get() ==
        attraction.get())
        TemporaryAttractionList->addAttration(attraction);
    else throw AttractionListException("Attraction must be from local Aquarium");
}

void TicketManager::removeFromAttractionList(std::string name) {
    TemporaryAttractionList->removeAttraction(name);
}

void TicketManager::clearAttractionList() {
    int sum = TemporaryAttractionList->getAttractionListSize();
    for (int i = 0; i < sum; i++)
        removeFromAttractionList(TemporaryAttractionList->getAttractionByIndex(0)->getAttractionName());
}

const AttractionList *TicketManager::getTemporaryAttractionList() const {
    return TemporaryAttractionList;
}

const Aquarium *TicketManager::getLocalAquarium() const {
    return LocalAquarium;
}

TicketManager::~TicketManager() {
    delete TemporaryAttractionList;
}

unsigned int TicketManager::getAmountOfTickets() const {
    return Tickets.size();
}

std::list<SingleTicketPtr> TicketManager::getSingleTickets() const {

    std::list<SingleTicketPtr> result;
    TicketPredicate predicate = [](TicketPtr ticket) -> bool {
        return dynamic_cast<SingleTicket *>(ticket.get()) != nullptr;
    };

    std::list<TicketPtr> tmp = Tickets.findAll(predicate);
    for (TicketPtr ptr : tmp)
        result.push_back(std::dynamic_pointer_cast<SingleTicket>(ptr));

    return result;
}

std::list<GroupTicketPtr> TicketManager::getGroupTickets() const {

    std::list<GroupTicketPtr> result;
    TicketPredicate predicate = [](TicketPtr ticket) -> bool {
        return dynamic_cast<GroupTicket *>(ticket.get()) != nullptr;
    };

    std::list<TicketPtr> tmp = Tickets.findAll(predicate);
    for (TicketPtr ptr : tmp)
        result.push_back(std::dynamic_pointer_cast<GroupTicket>(ptr));

    return result;
}

std::list<TicketPtr> TicketManager::getActiveTickets() const {

    std::list<TicketPtr> result;
    TicketPredicate predicate = [](TicketPtr ticket) -> bool {
        return (!ticket->isUsed() &&
                (ticket->getActiveDate() > pt::second_clock::local_time()));
    };

    result = Tickets.findAll(predicate);

    return result;
}

std::list<TicketPtr> TicketManager::getArchivedTickets() const {

    std::list<TicketPtr> result;
    TicketPredicate predicate = [](TicketPtr ticket) -> bool {
        return (ticket->isUsed() ||
                (ticket->getActiveDate() < pt::second_clock::local_time()));
    };

    result = Tickets.findAll(predicate);

    return result;
}

TicketPtr TicketManager::getByTicketId(std::string ticketId) const {
    TicketPredicate predicate = [ticketId](TicketPtr ticket) -> bool {
        return ticket->getTicketId() == ticketId;
    };
    return Tickets.find(predicate);
}

TicketPtr TicketManager::getByIndex(const unsigned int index) const {
    return Tickets.get(index);
}

std::ostream &operator<<(std::ostream &out, const TicketManager &ticketManager) {
    out << "TicketManager\n";
    for (int i = 0; i < ticketManager.Tickets.size(); i++) {
        out << *ticketManager.getByIndex(i) << "\n";
    }
    return out;
}


