#ifndef TOOLS_INTRO_MAILINGADDRESS_H
#define TOOLS_INTRO_MAILINGADDRESS_H

#include <iostream>
#include <string>

using namespace std;

class MailingAddress {
public:
    // attributes
    string street;
    string city;
    string state;
    int zipcode;
    // default constructor
    MailingAddress();
    // parameterized constructor
    MailingAddress(string street, string city, string state, int zipcode);
    // methods
    bool equals(MailingAddress addr);
    string toString();
    static bool compareAddress(MailingAddress addr_1, MailingAddress addr_2);




};

#endif //TOOLS_INTRO_MAILINGADDRESS_H
