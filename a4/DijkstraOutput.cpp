#include "algorithms/DijkstraOutput.h"

//constructor
DijkstraOutput::DijkstraOutput(Graph *graph, unordered_map<int, double> *dist, unordered_map<int, int> *prev) {
    this->graph = graph;
    this->dist = dist;
    this->prev = prev;
}

//prints this output
void DijkstraOutput::print() {
    //dist[]: {V1 -> dist[V1]}, {V2 -> dist[V2]},..., {Vn -> dist[Vn]}
    //prev[]: {V1 -> prev[V1]}, {V2 -> prev[V2]},..., {Vn -> prev[Vn]}
    //Vn is the string representation of Vn
    string distOutput = "dist[]: ";
    for(auto it = this->dist->begin(); it != this->dist->end(); it++){
        distOutput.append("{").append(this->graph->getVertex(it->first)->toString());
        distOutput.append(" -> ");
        stringstream sstream;
        sstream.setf(std::ios::fixed);
        sstream.precision(2); //the distance is formatted using two decimals
        sstream << it->second;
        string distStr = sstream.str();
        distOutput.append("dist[").append(distStr).append("]}, ");
    }
    //remove the extra ", " off the end of the output string
    distOutput.erase(distOutput.end() - 2, distOutput.end());
    cout << distOutput << endl;

    string prevOutput = "prev[]: ";
    for(auto iter = this->prev->begin(); iter != this->prev->end(); iter++){
        prevOutput.append("{").append(this->graph->getVertex(iter->first)->toString());
        prevOutput.append(" -> prev[");
        prevOutput.append(this->graph->getVertex(iter->second)->toString());
        //stringstream sstream;
        //sstream << iter->second;
        //string prevStr = sstream.str();
        //prevOutput.append(prevStr);
        prevOutput.append("]}, ");
    }
    //remove the extra ", " off the end of the output string
    prevOutput.erase(prevOutput.end() - 2, prevOutput.end());
    cout << prevOutput << endl;

}

//prints the shortest path from the source vertex to targetObj
void DijkstraOutput::printShortestPath(Object *targetObj) {
    //Vs -> V2 -> … -> Vt, Total cost: dist[Vt]
    //Vx is the string representation of the vertex Vx
    string output = ", Total cost: dist[";

    Vertex *v = this->graph->getVertex(targetObj, false);

    auto iter = dist->find(v->getId());
    stringstream sstream;
    sstream.setf(std::ios::fixed);
    sstream.precision(2); //the distance is formatted using two decimals
    sstream << iter->second;
    string distStr = sstream.str();
    output.append(distStr).append("]");

    auto it = prev->find(v->getId());
    int parentId = it->second;
    //while prev[v] != v
    while (v->getId() != parentId){
       //insert the vertex into the front of the output string
       output.insert(0, v->toString());
       output.insert(0, " -> ");

       //reassign the current vertex to be the parent of the previous vertex
       auto it = prev->find(parentId);
       v = this->graph->getVertex(it->first);
       //get the new parent vertex
       parentId = it->second;
    }

    //insert the source vertex at the front of the output string
    output.insert(0, v->toString());

    cout << output << endl;
}

//destructor
DijkstraOutput::~DijkstraOutput() {
    delete (dist);
    delete (prev);
}
