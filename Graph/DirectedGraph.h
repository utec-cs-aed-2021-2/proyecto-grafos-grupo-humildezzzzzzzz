#ifndef NONDIRECTEDGRAPH_H
#define NONDIRECTEDGRAPH_H

#include "graph.h"

template<typename TV, typename TE>
class DirectedGraph : public Graph<TV, TE>{
    public:
    bool insertVertex(string id, TV vertex);  
    bool createEdge(string id1, string id2, TE w);
    bool deleteVertex(string id);
    bool deleteEdges(string id);
    bool deleteEdge(string id1, string id2);
    TE &operator()(string start, string end);
    float density();
    bool isDense(float threshold = 0.5);
    bool isConnected();
    bool isStronglyConnected();
    bool empty();
    void clear();
    void displayVertex(string id);
    bool findById(string id);
    void display();
};

template<typename TV, typename TE>
bool DirectedGraph<TV,TE>::insertVertex(string id, TV vertex){
    if(this->vertexes.count(id) == 1){
        return false;
    }
    Vertex<TV, TE>* vertice = new Vertex<TV, TE>;
    vertice->data=vertex;
    vertexes[id]=vertice;
    return true;
}

template<typename TV, typename TE>
bool DirectedGraph<TV,TE>::createEdge(string id1, string id2, TE w){
    if(this->vertexes.count(id1) == 0 || this->vertexes.count(id2) == 0){
        return false;
    }
    auto* new_edge = new Edge<TV,TE>;
    new_edge->vertexes[0] = this->vertexes[id1];
    new_edge->vertexes[1] = this->vertexes[id2];
    new_edge->weight = w;

    this->vertexes[id1]->edges.push_back(new_edge);
    nro_aristas++;

    return true;
}

#endif