#ifndef HASHING_MAHASHTABLE_H
#define HASHING_MAHASHTABLE_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "utilities/MailingAddress.h"

using namespace std;

class MAHashTable {
public:
    int m;
    const static int R = 31;
    vector<vector<MailingAddress>> table;
    int size;

    MAHashTable(int table_size);

     long hashInt(int i);
     long hashString(string s);
     long hashAddress(MailingAddress addr);

    void insert(MailingAddress addr);
    bool contains(MailingAddress addr);
    float getLoadFactor();
    void print();

};


#endif //HASHING_MAHASHTABLE_H
