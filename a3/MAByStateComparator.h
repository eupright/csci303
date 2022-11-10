#ifndef SORTING_MABYSTATECOMPARATOR_H
#define SORTING_MABYSTATECOMPARATOR_H

#include "Comparator.h"
#include "entity/MailingAddress.h"

/*
 * A Comparator of Mailing Addresses. It inherits from Comparator<MailingAddress>
 *
 * It defines a by-state order
 *
 * In other words, the order is first determined by state, then city, then zipcode, and then street
 *
 */
class MAByStateComparator: public Comparator<MailingAddress> {


    //returns true if addr1 < addr2
    //returns false otherwise
    bool lessThan(MailingAddress &addr1, MailingAddress &addr2) override ;

    //returns true if addr1 == addr2
    //returns false otherwise
    bool equals(MailingAddress &addr1, MailingAddress &addr2) override;

};



#endif //SORTING_MABYSTATECOMPARATOR_H
