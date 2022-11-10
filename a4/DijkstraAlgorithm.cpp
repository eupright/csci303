#include "algorithms/DijkstraAlgorithm.h"

//constructor
DijkstraAlgorithm::DijkstraAlgorithm(Graph *pGraph) {
    graph = pGraph;
    this->dist = new unordered_map<int, double>();
    this->prev = new unordered_map<int, int>();
    this->unknown = new unordered_set<int>();
}

//destructor
DijkstraAlgorithm::~DijkstraAlgorithm() {
    delete (dist);
    delete (prev);
    delete unknown;
}

//runs the algorithm on source vertex (data) v
DijkstraOutput *DijkstraAlgorithm::findShortestPaths(Object *v) {
    Vertex *source = graph->getVertex(v, true);

    initialize(source);

    //while unknown is not empty
    while (unknown->size() != 0){
        //find the vertex with the shortest path in unknown
        Vertex *vertex = findMinDistVertex();

        //remove that vertex from unknown
        unknown->erase(vertex->getId());

        //relax the edges of the vertex
        relaxOutGoingEdges(vertex);
    }

    return new DijkstraOutput(graph, new unordered_map<int, double>(*dist), new unordered_map<int, int>(*prev));
}


//performs the initialization step of the algorithm
void DijkstraAlgorithm::initialize(Vertex *pVertex) {

    //every time there is an initialization, start over
    delete dist;
    delete prev;
    delete unknown;
    this->dist = new unordered_map<int, double>();
    this->prev = new unordered_map<int, int>();
    this->unknown = new unordered_set<int>();

    //dist[v] = infinity
    //prev[v] = -1 (a non-applicable vertex ID)
    //unknown = all vertices
    unordered_map<int, Vertex *> *vertices;
    vertices = this->graph->getVertices(); //returns an unordered_map of vertices indexed by a vertex id
    for(auto vertex = vertices->begin(); vertex != vertices->end(); vertex++){
        dist->insert({vertex->first, numeric_limits<int>::max()});
        prev->insert({vertex->first, -1});
        unknown->insert(vertex->first);
    }
    //dist[s] = 0
    auto it = dist->find(pVertex->getId());
    it->second = 0;
    //prev[s] = s
    auto iter = prev->find(pVertex->getId());
    iter->second = pVertex->getId();
    //unknown -= s
    unknown->erase(pVertex->getId());

    //relax all outgoing edges of s:
    vector<Edge *> *outgoingEdges = this->graph->getOutGoingEdges(pVertex);
    //for each x adjacent to s
    for(Edge *edge : *outgoingEdges){
        //dist[x] = weight(s -> x)
        auto it = dist->find(edge->getTarget()->getId());
        it->second = edge->getWeight();
        //prev[x] = s
        auto iter = prev->find(edge->getTarget()->getId());
        iter->second = pVertex->getId();
    }

}

//finds the vertex with the minimum dist from the unknown vertices
Vertex *DijkstraAlgorithm::findMinDistVertex() {
    int minDist = numeric_limits<int>::max();
    int minVertexId = -1;
    Vertex *minVertex = nullptr;

    //for every vertex in unknown
    for(int vertexId : *unknown){
        auto it = dist->find(vertexId);
        //check the dist[v] to see if it's the minimum distance
        if(it->second < minDist){
            //if yes, update the min distance and min vertexId
            minDist = it->second;
            minVertexId = vertexId;
        }
    }

    //return the vertex with the minimum dist[v]
    minVertex = this->graph->getVertex(minVertexId);
    return minVertex;
}

//relaxes the outgoing edges of v
void DijkstraAlgorithm::relaxOutGoingEdges(Vertex *v) {

    //for each w adjacent to v
    auto *neighbors = new unordered_set<Vertex *>();
    neighbors = this->graph->getOutgoingNeighbors(v->getData());

    for(Vertex *w : *neighbors){
        auto itw = dist->find(w->getId());
        double distw = itw->second;
        auto itv = dist->find(v->getId());
        double distv = itv->second;
        Edge *edge = this->graph->getEdge(v, w);

        //if dist[w] > dist[v] + weight(v,w)
        if (distw > distv + edge->getWeight()){
            //dist[w] = dist[v] + weight(v,w)
            itw->second = distv + edge->getWeight();
            //prev[w] = v
            auto it = prev->find(w->getId());
            it->second = v->getId();
        }
    }

}