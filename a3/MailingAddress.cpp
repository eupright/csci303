#include <entity/MailingAddress.h>

MailingAddress::MailingAddress(string street, string city, string state, int zipCode) {
    //move avoids making copies of the parameters
    this->street = std::move(street);
    this->city = std::move(city);
    this->state = std::move(state);
    this->zipCode = zipCode;
}

bool MailingAddress::equals(const MailingAddress &addr) {
    if (this->street != addr.street) return false;
    if (this->city != addr.city) return false;
    if (this->state != addr.state) return false;
    return zipCode == addr.zipCode;
}

string MailingAddress::toString() {
    string str = "{";
    str.append(street).append(", ").append(city).append(", ").append(state).append(", ").append(
            to_string(zipCode)).append("}");
    return str;
}

//returns true if this < addr, starting by street, city, state, and then zipcode (in alphabetical order)
bool  MailingAddress::operator<(MailingAddress const &addr) {
    //By-street order: first by street, then by city, then by state, and then by zipcode
    if (this->street < addr.street){
        return true;
    } else if (this->street == addr.street) {
        if (this->city < addr.city){
            return true;
        } else if (this->city == addr.city){
            if (this->state < addr.state) {
                return true;
            } else if (this->state == addr.state){
                return (this->zipCode < addr.zipCode);
            } else {
                return false;
            }
        } else {
            return false;
        }
    } else {
        return false;
    }
}

bool  MailingAddress::operator<=(MailingAddress const &addr) {
    return *this < addr || this->equals(addr);
}

string MailingAddress::getStreet() {
    return street;
}

string MailingAddress::getCity() {
    return city;
}

string MailingAddress::getState() {
    return state;
}

int MailingAddress::getZipCode() {
    return zipCode;
}
