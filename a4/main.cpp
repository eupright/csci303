#include <iostream>
#include <fstream>
#include "graph/Vertex.h"
#include "graph/Graph.h"
#include "entity/City.h"
#include "entity/StringElement.h"
#include "algorithms/DijkstraAlgorithm.h"

void buildGraphOfCities();

void buildGraphOfStringElements();

void buildDirectedGraph();

void runDijkstraAlgorithm(Graph *graph, Object *sourceObj, Object *targetObj, bool printTree);

int main() {
    buildGraphOfStringElements();
    cout << "-------------------------------------" << endl;
    buildGraphOfCities();
    cout << "-------------------------------------" << endl;
    buildDirectedGraph();
    return 0;
}

void buildGraphOfStringElements() {

    //----------------
    //objects to be stored in the graph

    Object *A = new StringElement("A");
    Object *B = new StringElement("B");
    Object *C = new StringElement("C");
    Object *D = new StringElement("D");
    Object *E = new StringElement("E");
    Object *F = new StringElement("F");
    Object *G = new StringElement("G");
    Object *H = new StringElement("H");
    Object *I = new StringElement("I");
    Object *J = new StringElement("J");

    //------------------
    //building the graph

    auto *undirectedGraph = new Graph(true);
    undirectedGraph->addEdge(A, B, 20);
    undirectedGraph->addEdge(A, C, 12);
    undirectedGraph->addEdge(A, D, 9);
    undirectedGraph->addEdge(B, C, 11);
    undirectedGraph->addEdge(B, E, 13);
    undirectedGraph->addEdge(D, F, 10);
    undirectedGraph->addEdge(C, D, 3);
    undirectedGraph->addEdge(C, E, 4);
    undirectedGraph->addEdge(C, G, 17);
    undirectedGraph->addEdge(E, H, 6);
    undirectedGraph->addEdge(F, G, 7);
    undirectedGraph->addEdge(F, I, 8);
    undirectedGraph->addEdge(G, H, 16);
    undirectedGraph->addEdge(G, I, 5);
    undirectedGraph->addEdge(G, J, 18);
    undirectedGraph->addEdge(H, J, 2);
    undirectedGraph->addEdge(I, J, 21);

    //----------------
    //printing the graph

    cout << endl << "* Graph of strings: " << endl;
    undirectedGraph->print();

    //----------------
    //running Dijkstra's algorithm

    runDijkstraAlgorithm(undirectedGraph, A, H, true);

    delete (undirectedGraph);
}

void buildGraphOfCities() {

    //----------------
    //cities to be stored in the graph

    City *seattle = new City("Seattle");
    City *sanFrancisco = new City("San Francisco");
    City *losAngeles = new City("Los Angeles");
    City *riverside = new City("Riverside");
    City *phoenix = new City("Phoenix");
    City *dallas = new City("Dallas");
    City *houston = new City("Houston");
    City *miami = new City("Miami");
    City *atlanta = new City("Atlanta");
    City *chicago = new City("Chicago");
    City *detroit = new City("Detroit");
    City *boston = new City("Boston");
    City *newYork = new City("New York");
    City *philadelphia = new City("Philadelphia");
    City *washington = new City("Washington");

    //------------------
    //building the graph

    auto *undirectedGraph = new Graph(true);
    undirectedGraph->addEdge(seattle, sanFrancisco, 678);
    undirectedGraph->addEdge(seattle, chicago, 1737);
    undirectedGraph->addEdge(sanFrancisco, riverside, 386);
    undirectedGraph->addEdge(sanFrancisco, losAngeles, 348);
    undirectedGraph->addEdge(losAngeles, riverside, 50);
    undirectedGraph->addEdge(losAngeles, phoenix, 357);
    undirectedGraph->addEdge(riverside, phoenix, 307);
    undirectedGraph->addEdge(riverside, chicago, 1704);
    undirectedGraph->addEdge(phoenix, dallas, 887);
    undirectedGraph->addEdge(phoenix, houston, 1015);
    undirectedGraph->addEdge(dallas, chicago, 805);
    undirectedGraph->addEdge(dallas, atlanta, 721);
    undirectedGraph->addEdge(dallas, houston, 225);
    undirectedGraph->addEdge(houston, atlanta, 702);
    undirectedGraph->addEdge(houston, miami, 968);
    undirectedGraph->addEdge(miami, atlanta, 604);
    undirectedGraph->addEdge(miami, washington, 923);
    undirectedGraph->addEdge(atlanta, chicago, 588);
    undirectedGraph->addEdge(atlanta, washington, 543);
    undirectedGraph->addEdge(chicago, detroit, 238);
    undirectedGraph->addEdge(detroit, boston, 613);
    undirectedGraph->addEdge(detroit, newYork, 482);
    undirectedGraph->addEdge(detroit, washington, 396);
    undirectedGraph->addEdge(boston, newYork, 190);
    undirectedGraph->addEdge(newYork, philadelphia, 81);
    undirectedGraph->addEdge(philadelphia, washington, 123);


    //----------------
    //printing the graph

    cout << endl << "* Graph of cities: " << endl;
    undirectedGraph->print();

    //----------------
    //running Dijkstra's algorithm

    runDijkstraAlgorithm(undirectedGraph, riverside, philadelphia, true);

    //running it on San Fransisco
    runDijkstraAlgorithm(undirectedGraph, sanFrancisco, atlanta, false);

    delete (undirectedGraph);
}

void buildDirectedGraph(){
    //opening the file with the graph data
    string filePath = "../data/graph.csv";
    auto *directedGraph = new Graph(false);
    fstream graphFile;

    graphFile.open(filePath, ios::in);

    string vertex1, vertex2, stringWeight;
    double weight;
    //reading in the data and adding edges to the graph
    while (!graphFile.eof()) {
        getline(graphFile,vertex1, ',');
        Object *object1 = new StringElement(vertex1);

        getline(graphFile, vertex2, ',');
        Object *object2 = new StringElement(vertex2);

        getline(graphFile, stringWeight);
        weight = stod(stringWeight);

        directedGraph->addEdge(object1, object2, weight);
    }
    graphFile.close();

    //----------------
    //printing the graph

    cout << endl << "* Directed graph of nodes: " << endl;
    directedGraph->print();
    cout << endl;

    //----------------
    //running Dijkstra's algorithm
    Object *node1 = new StringElement("node1");
    Object *node2 = new StringElement("node2");
    Object *node15 = new StringElement("node15");
    Object *node58 = new StringElement("node58");
    Object *node63 = new StringElement("node63");

    //shortest path from node1 to node2
    runDijkstraAlgorithm(directedGraph, node1, node2, false);

    //shortest path from node1 to node63
    runDijkstraAlgorithm(directedGraph, node1, node63, false);

    //shortest path from node15 to node58
    runDijkstraAlgorithm(directedGraph, node15, node58, false);

    delete (directedGraph);
}

/*
 * Runs Dijkstra's algorithm on the provided graph using source object.
 * It prints the result of the algorithm and also the shortest path from the source object to the target object.
 */
void runDijkstraAlgorithm(Graph *graph, Object *sourceObj, Object *targetObj, bool printTree) {
    auto *algorithm = new DijkstraAlgorithm(graph);
    DijkstraOutput *output = algorithm->findShortestPaths(sourceObj);

    if (output != nullptr) {
        if (printTree){
            cout << endl << "* Dijkstra's result: " << endl;
            output->print();
            cout << endl;
        }
        cout << "* Shortest path between " << graph->getVertex(sourceObj, false)->toString();
        cout << " and " << graph->getVertex(targetObj, false)->toString() << ":" << endl;
        output->printShortestPath(targetObj);
        cout << endl;
    } else {
        cout << "No output" << endl;
    }

    delete (output);
    delete (algorithm);
}
