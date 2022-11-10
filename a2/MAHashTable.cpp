#include "utilities/MAHashTable.h"

// constructor
MAHashTable::MAHashTable(int table_size){
    m = table_size;
    table.reserve(m);
    size = 0;
}

long MAHashTable::hashInt(int i) {
    return (i % this->m);
}

long MAHashTable::hashString(string s) {
    long hash = 0;
    for (int i = s.size(); i>=0; i--){
        hash = (R * hash + s[i]) % this->m;
    }
    return hash;
}

long MAHashTable::hashAddress(MailingAddress addr) {
    long street_hash = hashString(addr.street);
    long city_hash = hashString(addr.city);
    long state_hash = hashString(addr.state);
    long zip_hash = hashInt(addr.zipcode);
    long hash = (((((street_hash * R + city_hash) % this->m) * R + state_hash) % this->m) * R + zip_hash) % this->m;
    return hash;
}

void MAHashTable::insert(MailingAddress addr) {
    long hash_value = hashAddress(addr);
    table[hash_value].push_back(addr);
    sort(table[hash_value].begin(), table[hash_value].end(), addr.compareAddress);
    this->size = this->size + 1;
}

bool MAHashTable::contains(MailingAddress addr) {
    for(int i = 0; i < this->m; i++){
        for(int j = 0; j < table[i].size(); j++){
            if(addr.equals(table[i][j])){
                return true;
            }
        }
    }
    return false;
}

float MAHashTable::getLoadFactor() {
    float load_factor = (this->size / (float) this->m);
    return load_factor;
}

void MAHashTable::print() {
    for(int i = 0; i < this->m; i++){
        cout << i << "-> [";
        for(int j = 0; j < table[i].size(); j++){
            cout << table[i][j].toString();
            if(table[i].size() != 1 && j != (table[i].size() - 1)){
                cout << "; ";
            }
        }
        cout << "]" << endl;
    }
}

