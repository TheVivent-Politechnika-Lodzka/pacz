//
// Created by student on 08.06.2020.
//

#ifndef CARRENTAL_CLIENT_H
#define CARRENTAL_CLIENT_H


#include <string>

class Client {
private:
    std::string FirstName;
    std::string LastName;
    std::string PESEL;
    bool IsArchived = false;
public:
    Client(const std::string &firstName, const std::string &lastName, const std::string &pesel);

    const std::string &getFirstName() const;

    const std::string &getLastName() const;

    const std::string &getPesel() const;

    bool isArchived() const;

    void setArchived();

    void setFirstName(const std::string &firstName);

    void setLastName(const std::string &lastName);

    friend std::ostream &operator<<(std::ostream &out, const Client &client);
};

std::ostream &operator<<(std::ostream &out, const Client &client);

class ClientException : public std::logic_error {
public:
    explicit ClientException(const std::string &arg);
};


#endif //CARRENTAL_CLIENT_H
