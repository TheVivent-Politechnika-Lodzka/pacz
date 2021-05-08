//
// Created by student on 11.06.2020.
//

#ifndef CARRENTAL_TYPEDEFS_H
#define CARRENTAL_TYPEDEFS_H

#include <memory>
#include <functional>

class Client;

typedef std::shared_ptr<Client> ClientPtr;
typedef std::function<bool(ClientPtr)> ClientPredicate;

class Ticket;

typedef std::shared_ptr<Ticket> TicketPtr;
typedef std::function<bool(TicketPtr)> TicketPredicate;

class SingleTicket;

typedef std::shared_ptr<SingleTicket> SingleTicketPtr;

class GroupTicket;

typedef std::shared_ptr<GroupTicket> GroupTicketPtr;

class Attraction;

typedef std::shared_ptr<Attraction> AttractionPtr;
typedef std::function<bool(AttractionPtr)> AttractionPredicate;

#endif //CARRENTAL_TYPEDEFS_H
