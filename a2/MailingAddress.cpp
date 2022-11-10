#include "utilities/MailingAddress.h"


// default constructor
MailingAddress::MailingAddress(){
    street = "";
    city = "";
    state = "";
    zipcode = -1;
}

// parameterized constructor
MailingAddress::MailingAddress(string street_input, string city_input, string state_input, int zipcode_input){
    street = street_input;
    city = city_input;
    state = state_input;
    zipcode = zipcode_input;
}


bool MailingAddress::equals(MailingAddress addr) {
    if(this->street == addr.street && this->city == addr.city && this->state == addr.state && this->zipcode == addr.zipcode){
        return true;
    } else {
        return false;
    }

}

string MailingAddress::toString() {
    string address = "{" + this->street + ", " + this->city + ", " + this->state + ", " + to_string(this->zipcode) + "}";
    return address;
}

bool MailingAddress::compareAddress(MailingAddress addr_1, MailingAddress addr_2) {
    if(addr_1.state == addr_2.state){
        if(addr_1.city == addr_2.city){
            if(addr_1.zipcode == addr_2.zipcode){
                if(addr_1.street == addr_2.street){
                    return false;
                } else {
                    return(addr_1.street.compare(addr_2.street) < 0);
                }
            } else {
                return(addr_1.zipcode < addr_2.zipcode);
            }
        } else {
            return(addr_1.city.compare(addr_2.city) < 0);
        }
    } else {
        return(addr_1.state.compare(addr_2.state) < 0);
    }
}