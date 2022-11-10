#include <iostream>
#include <vector>
#include <fstream>
#include <entity/Coordinate.h>
#include <algorithms/InsertionSortIntegers.h>
#include <algorithms/InsertionSortGeneric.h>
#include <algorithms/InsertionSortGenericWithComparator.h>
#include <algorithms/QuickSortIntegers.h>
#include <algorithms/QuickSortGeneric.h>
#include <algorithms/QuickSortGenericWithComparator.h>
#include <comparator/CoordinateYXComparator.h>
#include <comparator/MAByStateComparator.h>
#include "utilities/ArrayUtilities.h"

using namespace std;

int main() {
    //INTEGER SORTING
    //opening the file with the integer data
    string filePath = "../data/numbers.txt";
    vector<int> unsortedIntArray;
    fstream numbersFile;
    numbersFile.open(filePath, ios::in);

    //reading in the numbers line by line
    string line;
    while (getline(numbersFile, line)) {
        unsortedIntArray.push_back(stoi(line));
    }
    numbersFile.close();

//    cout << "Size: " << unsortedIntArray.size() << endl;
//    cout << "Unsorted array of integers: " << endl;
//    ArrayUtilities<int>::printArray(unsortedIntArray);

    //sorting and print the numbers
    cout << "Sorting the integers with QuickSort" << endl;
    vector<int> sortedIntArray = QuickSortIntegers(unsortedIntArray).sort();
    cout << "Sorted integer array: " << endl;
    ArrayUtilities<int>::printArray(sortedIntArray);


    //COORDINATE SORTING
    //opening the file with the coordinate data
    filePath = "../data/coordinates.txt";
    vector<Coordinate> unsortedCoordinates;
    fstream coordinatesFile;

    coordinatesFile.open(filePath, ios::in);

    string xString, yString;
    int x, y;
    //reading in the coordinates and inserting them into the unsorted vector
    while (!coordinatesFile.eof()) {
        getline(coordinatesFile,xString , ',');
        x = stoi(xString);
        getline(coordinatesFile, yString);
        y = stoi(yString);

        Coordinate coord(x,y);

        unsortedCoordinates.push_back(coord);
    }
    coordinatesFile.close();

//    cout << "Size: " << unsortedCoordinates.size() << endl;
//    cout << "Unsorted array of coordinates: " << endl;
//    ArrayUtilities<Coordinate>::printArray(unsortedCoordinates);

    //sorting and printing the coordinates
    cout << "Sorting the coordinates with QuickSort" << endl;
    vector<Coordinate> sortedCoordinates = QuickSortGeneric<Coordinate>(unsortedCoordinates).sort();
    cout << "Sorted coordinates, first by x, and then by y: ";
    ArrayUtilities<Coordinate>::printArray(sortedCoordinates);


    //ADDRESS SORTING
    //opening the file with the address data
    filePath = "../data/addresses.txt";
    fstream addressesFile;
    vector<MailingAddress> unsortedAddresses;

    addressesFile.open(filePath, ios::in);

    string street, city, state, zipcode;
    int zip;
    //reading in the addresses and inserting them into the unsorted vector
    while (!addressesFile.eof()) {
        getline(addressesFile,street, ',');
        getline(addressesFile, city, ',');
        getline(addressesFile, state, ',');
        getline(addressesFile, zipcode);
        zip = stoi(zipcode);

        MailingAddress addr(street, city, state, zip);
        unsortedAddresses.push_back(addr);
    }
    addressesFile.close();

//    cout << "Size: " << unsortedAddresses.size() << endl;
//    cout << "Unsorted array of mailing addresses: " << endl;
//    ArrayUtilities<MailingAddress>::printArray(unsortedAddresses);

    //sorting the addresses using the overloaded < operator (in by-street order)
    cout << "Sorting the addresses with QuickSort" << endl;
    vector<MailingAddress> sortedAddresses = QuickSortGeneric<MailingAddress>(unsortedAddresses).sort();
    cout << "Sorted addresses in by-street order: ";
    ArrayUtilities<MailingAddress>::printArray(sortedAddresses);

    //sorting the addresses with a comparator (in by-state order)
    QuickSortGenericWithComparator<MailingAddress> algorithm = QuickSortGenericWithComparator<MailingAddress>(unsortedAddresses);
    Comparator<MailingAddress> *comparator2 = new MAByStateComparator();
    vector<MailingAddress> sortedAddresses2 = algorithm.sort(comparator2);
    cout << "Sorted coordinates in by-state order: ";
    ArrayUtilities<MailingAddress>::printArray(sortedAddresses2);

    return 0;
}