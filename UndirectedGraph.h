#ifndef UNDIRECTEDGRAPH_H
#define UNDIRECTEDGRAPH_H

#include "graph.h"

template<typename TV, typename TE>
class UnDirectedGraph : public Graph<TV, TE>{

    int nro_aristas = 0;

    UnDirectedGraph() = default;
    UnDirectedGraph(string id, TV vertex){
        this->insertVertex(id,vertex)
    }

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
bool UnDirectedGraph<TV,TE>::insertVertex(string id, TV vertex){
    if(this->vertexes.find(id) != this->vertexes.end()){
        return false;
    }
    auto *new_vertex = new Vertex<TV,TE>;
    new_vertex->data = vertex;
    new_vertex->id = id;
    this->vertexes[id] = new_vertex;
    return true;
}

template<typename TV, typename TE>
bool UnDirectedGraph<TV,TE>::createEdge(string id1, string id2, TE w){
    if(this->vertexes.find(id1) != this->vertexes.end() || this->vertexes.find(id2) != this->vertexes.end()){
        return false;
    }
    auto* new_edge = new Edge<TV,TE>;
    new_edge->vertexes[0] = this->vertexes[id1];
    new_edge->vertexes[1] = this->vertexes[id2];
    new_edge->weight = w;

    this->vertexes[id1]->edges.push_back(new_edge);

    auto* new_edge2 = new Edge<TV,TE>;
    new_edge2->vertexes[0] = this->vertexes[id1];
    new_edge2->vertexes[1] = this->vertexes[id2];
    new_edge2->weight = w;

    this->vertexes[id2]->edges.push_back(new_edge2);
    nro_aristas++;

    return true;
}

template<typename TV, typename TE>
bool UnDirectedGraph<TV,TE>::deleteEdges(string id){
    if (this->vertexes.find(id) == this->vertexes.end()){
        return false;
    }

    auto aristas_ady = &(this->vertexes[id])->edges; //solo tomo la lista de aristas para ese vertice

    while(!aristas_ady->empty()){
        auto inicio = (*aristas_ady->begin())->vertexes[0]; //primer vertice de la primera arista
        auto llegada = (*aristas_ady->begin())->vertexes[1]; //vertice de llegada de la primera arista

        for(auto i = (llegada->edges).begin(); i != (llegada->edges).end(); i++){ //recorro las demas aristas adyacentes al nodo de llegada
            if((*i)->vertexes[1] == inicio){ //si su vertice de llegada es igual al primer vertice de nuestra arista a eliminar
                (llegada->edges).erase(i); //borro la arista
                nro_aristas--;
                break;
            }
        }
        aristas_ady->pop_front(); //eliminamos la primera arista de nuestra lista de aristas adyacentes
    }
    return true;
}

template<typename TV, typename TE>
bool UnDirectedGraph<TV,TE>::deleteVertex(string id){
    if(this->vertexes.find(id) != this->vertexes.end()){
        return false;
    }

    deleteEdges(id);
    this->vertexes.erase(id);
    return true;
}

template<typename TV, typename TE>
bool UnDirectedGraph<TV,TE>::deleteEdge(string id1, string id2){
    if(this->vertexes.find(id1) != this->vertexes.end() || this->vertexes.find(id2) != this->vertexes.end()){
        return false;
    }

    auto aristas_ady_id1 = &(this->vertexes[id1])->edges;
    for(auto i = aristas_ady_id1.begin(); i != aristas_ady_id1.end(); i++){
        if(((*i)->vertexes[1])->id == id2){
            aristas_ady_id1.erase(i);
        }
    }

    auto aristas_ady_id2 = &(this->vertexes[id2])->edges;
    for(auto i = aristas_ady_id2.begin(); i != aristas_ady_id2.end(); i++){
        if(((*i)->vertexes[1])->id == id1){
            aristas_ady_id2.erase(i);
        }
    }
    nro_aristas--;
    return true;
}

#endif