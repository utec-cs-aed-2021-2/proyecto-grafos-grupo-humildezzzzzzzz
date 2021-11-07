#ifndef NONDIRECTEDGRAPH_H
#define NONDIRECTEDGRAPH_H

#include "graph.h"

template<typename TV, typename TE>
class DirectedGraph : public Graph<TV, TE>{
    public:

    DirectedGraph() = default;
    DirectedGraph(string id, TV vertex){ //LISTO
        this->insertVertex(id,vertex)
    }

    ~DirectedGraph();
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

template<typename TV, typename TE>
bool DirectedGraph<TV,TE>:: deleteVertex(string id){
    if(this->vertexes.count(id) == 0){
        return false;
    }

    deleteEdges(id);
    this->vertexes.erase(id);
    return true;
};

template<typename TV, typename TE>
bool DirectedGraph<TV,TE>:: deleteEdges(string id){
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
};

template<typename TV, typename TE>
bool DirectedGraph<TV,TE>::deleteEdge(string id1, string id2){
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
    nro_aristas--;
    return true;
};

template<typename TV, typename TE>
TE& DirectedGraph<TV,TE>::operator()(string start, string end); // Creo que declare esto mal xd revisar

template<typename TV, typename TE>
    float DirectedGraph<TV,TE>::density();

template<typename TV, typename TE>
    bool DirectedGraph<TV,TE>::isDense(float threshold = 0.5){ return this->density()>threshold;};

template<typename TV, typename TE>
    bool DirectedGraph<TV,TE>::isConnected();

template<typename TV, typename TE>
    bool DirectedGraph<TV,TE>::isStronglyConnected();

template<typename TV, typename TE>
    bool DirectedGraph<TV,TE>::empty(){
          return this->vertexes.empty();
    };

template<typename TV, typename TE>
    void DirectedGraph<TV,TE>::clear(){
        while(!this->vertexes.empty()){
        auto i = *this->vertexes.begin();
        deleteVertex(i.first);
    }
    };

template<typename TV, typename TE>
    void DirectedGraph<TV,TE>::displayVertex(string id){
        std::cout<<this->vertexes[id]->data<<std::endl;
    };

template<typename TV, typename TE>
    bool DirectedGraph<TV,TE>::findById(string id){
        return this->vertexes.count(id);
    };

template<typename TV, typename TE>
    void DirectedGraph<TV,TE>::display(){
        vector<pair<string,string>> visited;

    for(auto i:this->vertexes){
        string id = i.first;
        auto aristas = (this->vertexes[id])->edges;

        for(auto j:aristas){
            string ids = (j->vertexes[1])->id
            bool visitado = false;
            for(auto &k:visited){
                if((k.first == id && k.second == ids) || (k.first == ids && k.second == id)){
                    visitado = true;
                    break;
                }
            }

            if(!visitado){
                visited.push_back(make_pair(id,ids));
                std::cout<<"peso del vertice "<<id<<" al vertice "<<ids<<" es "<< (*j)->weight<<endl;
            }
        }
    }
    };


template<typename TV, typename TE>
DirectedGraph<TV,TE>::~DirectedGraph(){
    while(this->vertexes.size() != 0){
        deleteVertex((*this->vertexes.begin()).first);
    }
}

#endif