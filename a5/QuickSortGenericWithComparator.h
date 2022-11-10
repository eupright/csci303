#ifndef SORTING_QUICKSORT_GEN_COMP_H
#define SORTING_QUICKSORT_GEN_COMP_H

#include <vector>
#include "comparator/Comparator.h"

using namespace std;

/*
 * Quicksort implementation for generic objects with a Comparator
 * It uses median-of-three to select the pivot.
 * It uses the partitioning strategy covered in the lecture.
 */
template <class Comparable>
class QuickSortGenericWithComparator {
private:
    vector<Comparable> array;
    //the comparator of this algorithm
    Comparator<Comparable>* comparator;

    //method that implements quicksort.
    //it receives the left and right indices that indicate the portion of the array that will be sorted
    void quicksort(int left, int right);

    //returns the index of the median between left, center, and right elements, where center = floor((right - left) / 2)
    int medianOfThree(int left, int right);
public:
    //constructor of the class
    explicit QuickSortGenericWithComparator(vector<Comparable> inputArray, Comparator<Comparable>* comparator) ;

    //sorts the elements from array
    //it returns a vector with the sorted elements
    vector<Comparable> sort() ;


};

#endif //SORTING_QUICKSORT_GEN_COMP_H
