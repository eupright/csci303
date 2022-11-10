#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <cmath>
#include <comparator/CoordinateYXComparator.h>
#include <algorithms/QuickSortGeneric.h>
#include <algorithms/QuickSortGenericWithComparator.h>
#include "utilities/ArrayUtilities.h"

using namespace std;

/*
 * We create an alias (ClosestPointsResult) for the result of the closest pair algorithm
 *
 * ClosestPointsResult is a tuple of three elements:
 * 1. The first point in the pair of closest points
 * 2. The second point in the pair of closest points
 * 3. The distance between the points
 */
typedef tuple<Coordinate, Coordinate, double> ClosestPointsResult;

//-----------------------------------------------
//function declarations. See their implementation below to know about their API specification.

ClosestPointsResult *closestPoints(vector<Coordinate> &points);

ClosestPointsResult *closestPoints(vector<Coordinate> &pointsByX, vector<Coordinate> &pointsByY, int left, int right);

double computeDistance(Coordinate p1, Coordinate p2);

void runAlgorithm(vector<Coordinate> &points);

vector<Coordinate> readPoints();

//-----------------------------------------------

int main() {

    //read the points from the "coordinates.txt" file
    vector<Coordinate> filePoints = readPoints();

    //list of test cases
    vector<vector<Coordinate>> testCases{
            vector<Coordinate>(), //empty vector of points
            vector<Coordinate>{Coordinate(3, 3)}, //just one point
            vector<Coordinate>{Coordinate(3, 3), Coordinate(3, 1)}, //just two points
            vector<Coordinate>{Coordinate(3, 3), Coordinate(3, 20), Coordinate(3, 1)}, //p1 and p3 are the closest
            vector<Coordinate>{Coordinate(3, 113), Coordinate(3, 20), Coordinate(3, 1)}, //p2 and p3 are the closest
            vector<Coordinate>{Coordinate(3, 113), Coordinate(3, 20), Coordinate(3, 1001)}, //p1 and p2 are the closest
            filePoints, //all the points from the file
            vector<Coordinate>(filePoints.begin(), filePoints.begin() + 10), //the first 10 points from the file
            vector<Coordinate>(filePoints.begin(), filePoints.begin() + 20), //the first 20 points from the file
            vector<Coordinate>(filePoints.begin(), filePoints.begin() + 30) //the first 30 points from the file
    };

    //for each test case, run the algorithm
    for (auto testPoints: testCases) {
        runAlgorithm(testPoints);
        cout << "-----------------" << endl;
    }
    

    return 0;
}

/*
 * Run the closest-points algorithm on the input vector of points and
 * prints the vector and the algorithm output on the terminal
 */
void runAlgorithm(vector<Coordinate> &points) {

    //print the input
    cout << "Input points: " << points.size() << endl;
    ArrayUtilities<Coordinate>::printArray(points);

    //run the algorithm and return the closest points
    ClosestPointsResult *clsPoints = closestPoints(points);

    //print the output
    cout << "Closest points:" << endl;
    if (clsPoints != nullptr) {

        //we use the get<i> function on the tuple to get the i-th element from the tuple
        auto point1 = get<0>(*clsPoints);
        auto point2 = get<1>(*clsPoints);
        double distance = get<2>(*clsPoints);

        cout << point1.toString() << " - " << point2.toString() << endl
             << "distance: " << distance << endl;
    } else {
        cout << "Undefined for the input!" << endl;
    }
}

/*
 * Function that returns the closest points in the provided list of points.
 */
ClosestPointsResult *closestPoints(vector<Coordinate> &points) {

    //sort the points by the x- and y-coordinates using quicksort
    vector<Coordinate> sortedPointsByX = QuickSortGeneric<Coordinate>(points).sort();
    vector<Coordinate> sortedPointsByY = QuickSortGenericWithComparator<Coordinate>(points,
                                                                                    new CoordinateYXComparator()).sort();
    //call the recursive function that implements the closest points algorithm
    return closestPoints(sortedPointsByX, sortedPointsByY, 0, sortedPointsByX.size());
}


/*
 * Recursive function that implements and runs the closest-points algorithm on the provided lists of points.
 *
 * The left and right indices indicate the portion of the lists that will be processed by the algorithm at each recursive step,
 * i.e., the algorithm returns the closest points within that portion only.
 *
 * Input:
 * pointsByX: list of points sorted by the x-coordinate
 * pointsByY: the same list of points, but sorted by the y-coordinate
 * left: the index that indicates the start of the sublist to be processed
 * right: the index that indicates the end of the sublist to be processed
 *
 * Output:
 * The closes points (and their distance) or nullptr if the sublists (as defined by left and right) have less than 2 points
 */
ClosestPointsResult *closestPoints(vector<Coordinate> &pointsByX, vector<Coordinate> &pointsByY, int left, int right) {

    //IMPORTANT: Always use the left and right indices in the code below.
    //Remember that they determine the sublist of points that needs to be processed

    //-----------------------------------------
    //these are the base cases

    int size = right - left; //size of the sublist to be processed
    if (size < 2) return nullptr; //there is no solution for this case

    //if there are only two points, just return them and their distance
    if (size == 2) {

        double distance = computeDistance(pointsByX[left], pointsByX[right-1]);

        auto *result = new ClosestPointsResult;
        *result = make_tuple(pointsByX[left], pointsByX[right - 1], distance);

        return result;
        //return new ClosestPointsResult(p1, p2, distance);
    } else {
        //if there are only three points, compare their distance directly and determine/return the closest pair
        if (size == 3) {

            auto *result = new ClosestPointsResult;
            //three possible cases/distances
            //(1)distance between pt1 and pt2
            //(2)distance between pt1 and pt3
            //(3)distance between pt2 and pt3
            double distance1 = computeDistance(pointsByX[left], pointsByX[left+1]);
            double distance2 = computeDistance(pointsByX[left], pointsByX[right-1]);
            double distance3 = computeDistance(pointsByX[left+1], pointsByX[right-1]);

            if (distance1 < distance2 && distance1 < distance3) {
                //when (1) is the closest pair
                *result = make_tuple(pointsByX[left], pointsByX[left + 1], distance1);
            }
            else if (distance2 < distance1 && distance2 < distance3) {
                //when (2) is the closest pair
                *result = make_tuple(pointsByX[left], pointsByX[right-1], distance2);
            }
            else {
                //when (3) is the closest pair
                *result = make_tuple(pointsByX[left + 1], pointsByX[right - 1], distance3);
            }

            return result;
        }
    }

    //-----------------------------------------
    //determine the middle index that divides the points into halves and run the current function recursively on each half
    int center = (left + right)/2;

    ClosestPointsResult *leftResult = closestPoints(pointsByX, pointsByY, left, center);
    ClosestPointsResult *rightResult = closestPoints(pointsByX, pointsByY, center, right);


    //-----------------------------------------
    //determine the closest pair between the closest pairs from both halves (returned by the recursive calls)
    //save the "delta" (i.e., the minimum distance) from the distance of both closest pairs of points
    auto *closestPair = new ClosestPointsResult;
    double delta = -1;

    if (get<2>(*leftResult) < get<2>(*rightResult)){
        delta = get<2>(*leftResult);
        closestPair = leftResult;
    }
    else {
        delta = get<2>(*rightResult);
        closestPair = rightResult;
    }


    //-----------------------------------------
    //filter the points whose x-coordinate fall within the middle "2*delta" strip
    //(i.e., points that are "delta"-distance apart from the middle point)
    center = pointsByY.size() / 2;
    auto middlePoints = vector<Coordinate>();
    for (int point = 0; point < pointsByY.size(); point++) {
        if (pointsByY[point].x < (center + delta) && pointsByY[point].x > (center - delta))
            middlePoints.push_back(pointsByY[point]);
    }


    //-----------------------------------------
    //process the points in middle strip:
    //for each point in the strip, starting from the one with the lowest y-coordinate, compute its distance with
    //the next 7 points.
    //if that distance is smaller than the "delta" distance, update "delta" and also the closest points to be returned
    for (int i = 0; i < middlePoints.size(); i++){
        for (int j = 1; j <= 7; ++j) {
            if (i+j < middlePoints.size()) {
                double distance = computeDistance(middlePoints[i], middlePoints[i + j]);
                if (distance < delta) {
                    delta = distance;
                    *closestPair = make_tuple(middlePoints[i], middlePoints[i + j], distance);
                }
            }
        }
    }

    //return the closest points and their distance
    return closestPair;

}

/*
 * Computes the Euclidean distance between the two provided points
 */
double computeDistance(Coordinate p1, Coordinate p2) {

    double xdiff = (p1.x - p2.x) * (p1.x - p2.x);
    double ydiff = (p1.y - p2.y) * (p1.y - p2.y);

    return sqrt((xdiff + ydiff));
}

/*
 * Function that reads the points from the file "../data/coordinates.txt"
 */
vector<Coordinate> readPoints() {

    string filePath = "../data/coordinates.txt";
    auto coordinates = vector<Coordinate>();

    fstream coordinatesFile;

    coordinatesFile.open(filePath, ios::in);

    string xString, yString;
    int x, y;
    //reading in the coordinates and inserting them into the coordinates vector
    while (!coordinatesFile.eof()) {
        getline(coordinatesFile,xString , ',');
        x = stoi(xString);
        getline(coordinatesFile, yString);
        y = stoi(yString);

        Coordinate coord(x,y);

        coordinates.push_back(coord);
    }
    coordinatesFile.close();

    return coordinates;
}

