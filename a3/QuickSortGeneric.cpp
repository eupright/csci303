#include <algorithms/QuickSortGeneric.h>
#include <entity/Coordinate.h>
#include <entity/MailingAddress.h>


template<class Comparable>
QuickSortGeneric<Comparable>::QuickSortGeneric(vector<Comparable> inputArray) {
    //move avoids making a copy of the vector, which could be costly for large input arrays
    this->array = std::move(inputArray);
}

template<class Comparable>
vector<Comparable> QuickSortGeneric<Comparable>::sort() {
    //we call quick sort on the array
    quicksort(0, array.size() - 1);
    //we return the array
    return array;
}

template<class Comparable>
void QuickSortGeneric<Comparable>::quicksort(int left, int right) {
    //if there are either 0 or 1 elements in the subarray, then return
    if(right <= left){
        return;
    }
    //use median-of-3 to pick the pivot from the left, right, and center values
    int center = (left + right)/2;
    int pivot;
    if(array[left] <= array[right] && array[center] <= array[left]){
        pivot = left;
    } else if(array[right] <= array[left] && array[left] <= array[center]){
        pivot = left;
    } else if(array[right] <= array[left] && array[center] <= array[right]){
        pivot = right;
    } else if(array[left] <= array[right] && array[right] <= array[center]) {
        pivot = right;
    } else if(array[left] <= array[center] && array[center] <= array[right]) {
        pivot = center;
    } else {
        pivot = center;
    }
    //partition the array into an array of values less than the pivot and an array of values greater than the pivot
    //swap the value of the pivot with the last element
    Comparable temp = array[pivot];
    array[pivot] = array[right];
    array[right] = temp;
    pivot = right;
    //traversal
    int i = left; //starts at the first element and points to larger elements
    int j = right - 1; //starts at the next-to-last element and points to smaller elements
    while(i <= j) {
        while(array[i] < array[pivot]){
            i += 1; //move i to the right until it points to a value greater than the pivot
        }
        while(array[pivot] <= array[j]){
            j -= 1; //move j to the left until it points to a value less than the pivot
        }
        if(i < j){ //swap the values
            temp = array[i];
            array[i] = array[j];
            array[j] = temp;
            i += 1;
            j -= 1;
        }
    }
    //swap the pivot element with the element that i points to
    temp = array[pivot];
    array[pivot] = array[i];
    array[i] = temp;
    pivot = i;

    //apply quicksort recursively to the two subarrays
    quicksort(left, pivot - 1);
    quicksort(pivot + 1, right);
}

template class QuickSortGeneric<int>;
template class QuickSortGeneric<Coordinate>;
template class QuickSortGeneric<MailingAddress>;
