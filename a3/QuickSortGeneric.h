#ifndef SORTING_QUICKSORTGENERIC_H
#define SORTING_QUICKSORTGENERIC_H

#include <vector>

using namespace std;

/*
 * Quicksort implementation for vectors of comparable objects
 */

template <class Comparable>
class QuickSortGeneric {
private:
    vector<Comparable> array;

    //method that implements quicksort.
    //it receives the left and right indices that indicate the portion of the array that will be sorted
    void quicksort(int left, int right);
public:
    //constructor of the class
    explicit QuickSortGeneric(vector<Comparable> inputArray) ;

    //sorts the elements from array
    //it returns a vector with the sorted elements
    vector<Comparable> sort() ;


};



#endif //SORTING_QUICKSORTGENERIC_H
