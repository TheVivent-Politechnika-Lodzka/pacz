//
// Created by student on 08.06.2020.
//

#ifndef CARRENTAL_TICKETMANAGER_H
#define CARRENTAL_TICKETMANAGER_H

#include <boost/date_time.hpp>
#include "typedefs.h"
#include "Visitor.h"
#include "Group.h"
#include "Repository.h"
#include "AttractionList.h"
#include "SingleTicket.h"
#include "GroupTicket.h"

namespace pt = boost::posix_time;
namespace gr = boost::gregorian;

class Aquarium;

class TicketManager {
private:
    Repository<TicketPtr> Tickets;
    AttractionList *TemporaryAttractionList = new AttractionList();
    Aquarium *LocalAquarium;

    void checkTicket(const std::string &ticketId, const pt::ptime &activeDate, unsigned int numberOfPeople,
                     const ClientPtr &owner);

public:
    TicketManager(Aquarium *localAquarium);

    virtual ~TicketManager();

    SingleTicketPtr registerTicket(const std::string &ticketId, pt::ptime activeDate, const ClientPtr &owner,
                                   const Visitor visitorType);

    GroupTicketPtr registerTicket(const std::string &ticketId, pt::ptime activeDate, const ClientPtr &owner,
                                  const unsigned int numberOfPeople, const Group groupType);

    const Aquarium *getLocalAquarium() const;

    unsigned int getAmountOfTickets() const;

    std::list<SingleTicketPtr> getSingleTickets() const;

    std::list<GroupTicketPtr> getGroupTickets() const;

    std::list<TicketPtr> getActiveTickets() const;

    std::list<TicketPtr> getArchivedTickets() const;

    TicketPtr getByTicketId(const std::string ticketId) const;

    TicketPtr getByIndex(const unsigned int index) const;

    void addToAttractionList(AttractionPtr attraction);

    void removeFromAttractionList(const std::string name);

    void clearAttractionList();

    const AttractionList *getTemporaryAttractionList() const;

    friend std::ostream &operator<<(std::ostream &out, const TicketManager &ticketManager);
};

std::ostream &operator<<(std::ostream &out, const TicketManager &ticketManager);

#endif //CARRENTAL_TICKETMANAGER_H
