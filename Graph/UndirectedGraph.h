#ifndef UNDIRECTEDGRAPH_H
#define UNDIRECTEDGRAPH_H

#include "graph.h"

template<typename TV, typename TE>
Vertex<TV,TE> llegadas(string id, list<Edge<TV, TE>*> arista){
    auto todos_aristas = &(this->vertexes[id])->edges;
    if(id == ((*todos_aristas->begin())->vertexes[0])->id){
        return (*todos_aristas->begin())->vertexes[1]
    }
    else{
        return (*todos_aristas->begin())->vertexes[0]
    }
}

template<typename TV, typename TE>
Vertex<TV,TE> inicios(string id, list<Edge<TV,TE>*> arista){
    auto todos_aristas = &(this->vertexes[id])->edges;
    if(id != ((*todos_aristas->begin())->vertexes[1])->id){
        return (*todos_aristas->begin())->vertexes[0]
    }
    else{
        return (*todos_aristas->begin())->vertexes[1]
    }
}

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
    if(this->vertexes.count(id) == 1){
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
    if(this->vertexes.count(id1) == 0 || this->vertexes.count(id2) == 0){
        return false;
    }
    auto* new_edge = new Edge<TV,TE>;
    new_edge->vertexes[0] = this->vertexes[id1];
    new_edge->vertexes[1] = this->vertexes[id2];
    new_edge->weight = w;

    this->vertexes[id1]->edges.push_back(new_edge);
    this->vertexes[id2]->edges.push_back(new_edge);
    nro_aristas++;

    return true;
}

template<typename TV, typename TE>
bool UnDirectedGraph<TV,TE>::deleteEdges(string id){
    if (this->vertexes.count(id) == 0){
        return false;
    }

    auto aristas_ady = &(this->vertexes[id])->edges; //solo tomo la lista de aristas para ese vertice

    while(!aristas_ady->empty()){
        auto inicio = inicios(id,aristas_ady); //primer vertice de la primera arista
        auto llegada = llegadas(id,aristas_ady)//vertice de llegada de la primera arista

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
    if(this->vertexes.count(id) == 0){
        return false;
    }

    deleteEdges(id);
    this->vertexes.erase(id);
    return true;
}

template<typename TV, typename TE>
bool UnDirectedGraph<TV,TE>::deleteEdge(string id1, string id2){
    if(this->vertexes.count(id1) == 0 || this->vertexes.count(id2) == 0){
        return false;
    }

    auto aristas_ady_id1 = &(this->vertexes[id1])->edges;
    auto llegada1 = llegadas(id1,aristas_ady_id1)
    for(auto i = aristas_ady_id1.begin(); i != aristas_ady_id1.end(); i++){
        if(llegada1->id == id2){
            aristas_ady_id1.erase(i);
        }
    }

    auto aristas_ady_id2 = &(this->vertexes[id2])->edges;
    auto llegada2 = llegadas(id2,aristas_ady_id2)
    for(auto i = aristas_ady_id2.begin(); i != aristas_ady_id2.end(); i++){
        if(llegada2->id == id1){
            aristas_ady_id2.erase(i);
        }
    }
    nro_aristas--;
    return true;
}

template<typename TV, typename TE>
float UnDirectedGraph<TV,TE>::density(){
    std::list<Edge<TV, TE>*> aristas;
    for(auto a =begin(this->vertexes); a!=end(this->vertexes); a++){
        //TO DO
        //Iterar sobre todos los vertices y obtener todas las aristas
    }
    int num_aristas=aristas.size();
    int num_vertices=this->vertexes.size()
    return 2*num_aristas/(num_vertices*(num_vertices-1))
}

template<typename TV, typename TE>
bool UnDirectedGraph<TV,TE>::isDense(float threshold = 0.5){ return this->density()>threshold;}

template<typename TV, typename TE>
bool UnDirectedGraph<TV,TE>::isConnected(){
     std::unordered_map<string, Vertex<TV, TE>*>  visited;
    
}

template<typename TV, typename TE>
bool UnDirectedGraph<TV,TE>::isStronglyConnected(){
    return isConnected();
}

template<typename TV, typename TE>
bool UnDirectedGraph<TV,TE>::empty(){
    return this->vertexes.empty();
}

template<typename TV, typename TE>
void UnDirectedGraph<TV,TE>::clear(){
    for(auto a=begin(this->vertexes); a!=end(this->vertexes); a++){
        //Clearear vector aristas de cada vertice.
    }
    this->vertexes.clear();
}

template<typename TV, typename TE>
void UnDirectedGraph<TV,TE>::displayVertex(string id){
    std::cout<<this->vertexes[id]->data<<std::endl;
}

template<typename TV, typename TE>
bool UnDirectedGraph<TV,TE>::findById(string id){
    return this->vertexes.count(id);
}

template<typename TV, typename TE>
void UnDirectedGraph<TV,TE>::display(){
    for(auto& it: vertexes){
        //Imprimir la data de todos los vértices.
        std::cout<<(it.second)->data<<std::endl;
    }
    
}
#endif