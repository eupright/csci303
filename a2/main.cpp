//including other code
#include <iostream>
#include <fstream>
#include <string>
#include "utilities/MailingAddress.h"
#include "utilities/MAHashTable.h"

//including a namespace
using namespace std;

//code for BONUS
int main(int argc, char *argv[]) {
    string absolute_path = argv[1];
    ifstream addresses;
    string street, city, state, zipcode;
    MailingAddress addr;
    MAHashTable hash_table_97(97);
    MAHashTable hash_table_127(127);

    //addresses.open("/Users/college/Desktop/CSCI303/repo-eupright/a2/hashing/addresses.txt", ios::in);
    addresses.open(absolute_path, ios::in);

    //reading in the addresses and inserting them into the hash table
    while (!addresses.eof()) {
            getline(addresses,street, ',');
            addr.street = street;

            getline(addresses, city, ',');
            addr.city = city;

            getline(addresses, state, ',');
            addr.state = state;

            getline(addresses, zipcode);
            addr.zipcode = stoi(zipcode);

            //cout << addr.toString() << endl;
            hash_table_97.insert(addr);
            hash_table_127.insert(addr);
        }
    addresses.close();
    //printing the hash tables and load factors for bonus
    hash_table_97.print();
    cout << hash_table_97.getLoadFactor() << endl;
    hash_table_127.print();
    cout << hash_table_127.getLoadFactor() << endl;

    //MailingAddress test_addr_1("450 Highland Ave", "Salem", "MA", 1970);
    //MailingAddress test_addr_2("450 Highland Avenue", "Salem", "MA", 1970);
    //cout << hash_table.contains(test_addr_1) << endl;
    //cout << hash_table.contains(test_addr_2) << endl;


    return 0;
}
