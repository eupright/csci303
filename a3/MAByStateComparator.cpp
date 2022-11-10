#include "comparator/MAByStateComparator.h"


bool MAByStateComparator::lessThan(MailingAddress &addr1, MailingAddress &addr2) {
    //By-state order: first by state, then by city, then by zipcode, and then by street
    if (addr1.getState() < addr2.getState()){
        return true;
    } else if (addr1.getState() == addr2.getState()) {
        if (addr1.getCity() < addr2.getCity()){
            return true;
        } else if (addr1.getCity() == addr2.getCity()){
            if (addr1.getZipCode() < addr2.getZipCode()) {
                return true;
            } else if (addr1.getZipCode() == addr2.getZipCode()){
                if (addr1.getStreet() < addr2.getStreet()) {
                    return true;
                } else {
                    return false;
                }
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

bool MAByStateComparator::equals(MailingAddress &addr1, MailingAddress &addr2) {
    return addr1.equals(addr2);
}
