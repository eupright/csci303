#ifndef SORTING_QUICKSORTGENERICWITHCOMPARATOR_H
#define SORTING_QUICKSORTGENERICWITHCOMPARATOR_H

#include <vector>
#include "comparator/Comparator.h"

using namespace std;

/*
 * Quick sort implementation for vectors of Comparable objects
 * Comparable is any type of object (e.g., string, int, MailingAddress, etc.)
 *
 * The sort method uses a Comparator which determines the order of Comparable objects
 */
template <class Comparable>
class QuickSortGenericWithComparator {
private:
    //the vector that insertion sort aims to sort
    vector<Comparable> array;

    //method that implements quicksort.
    //it receives the left and right indices that indicate the portion of the array that will be sorted
    void quicksort(Comparator<Comparable> *comparator, int left, int right);
public:

    //constructor of the class
    explicit QuickSortGenericWithComparator(vector<Comparable> inputArray);

    //sorts the elements from array in the order specified by comparator
    //it returns a vector with the sorted elements
    vector<Comparable> sort(Comparator<Comparable> *comparator) ;

};

#endif //SORTING_QUICKSORTGENERICWITHCOMPARATOR_H
