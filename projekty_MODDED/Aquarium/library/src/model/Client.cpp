//
// Created by student on 08.06.2020.
//

#include <sstream>
#include "Client.h"

ClientException::ClientException(const std::string &arg) : logic_error(arg) {}

Client::Client(const std::string &firstName, const std::string &lastName, const std::string &pesel) : FirstName(
        firstName), LastName(lastName), PESEL(pesel) {}

const std::string &Client::getFirstName() const {
    return FirstName;
}

const std::string &Client::getLastName() const {
    return LastName;
}

const std::string &Client::getPesel() const {
    return PESEL;
}

bool Client::isArchived() const {
    return IsArchived;
}

void Client::setArchived() {
    IsArchived = true;
}

void Client::setFirstName(const std::string &firstName) {
    if (firstName.empty()) throw ClientException("CLient's FirstName cannot be empty");
    FirstName = firstName;
}

void Client::setLastName(const std::string &lastName) {
    if (lastName.empty()) throw ClientException("CLient's LastName cannot be empty");
    LastName = lastName;
}

std::ostream &operator<<(std::ostream &out, const Client &client) {
    out << "First Name: " << client.getFirstName() << " ";
    out << "Last Name: " << client.getLastName() << " ";
    out << "PESEL: " << client.getPesel() << " ";
    out << "Is Archived: " << (client.isArchived() ? "yes" : "no") << " ";
    return out;
}
