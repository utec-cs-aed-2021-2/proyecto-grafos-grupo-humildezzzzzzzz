#ifndef NONDIRECTEDGRAPH_H
#define NONDIRECTEDGRAPH_H

#include "graph.h"

template<typename TV, typename TE>
class DirectedGraph : public Graph<TV, TE>{
    private:
    int nro_arsistas;
    public:

    DirectedGraph() = default;
    DirectedGraph(string id, TV vertex){ //LISTO
        this->insertVertex(id,vertex)
    }

    ~DirectedGraph();
    bool insertVertex(string id, TV vertex); //LISTO 
    bool createEdge(string id1, string id2, TE w); //LISTO
    bool deleteVertex(string id); //LISTO
    bool deleteEdges(string id); //LISTO
    bool deleteEdge(string id1, string id2); //LISTO
    TE &operator()(string start, string end); //LISTO
    float density(); //LISTO
    bool isDense(float threshold = 0.5); //LISTO
    bool isConnected();
    bool isStronglyConnected();
    bool empty(); //LISTO
    void clear(); //LISTO
    void displayVertex(string id); //PREGUNTAR AL PROFESOR 
    bool findById(string id); //LISTO
    void display(); //LISTO
};

template<typename TV, typename TE>
bool DirectedGraph<TV,TE>::insertVertex(string id, TV vertex){
    if(this->vertexes.count(id) == 1){
        return false;
    }
    Vertex<TV, TE>* vertice = new Vertex<TV, TE>;
    vertice->data=vertex;
    vertice->id = id;
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
    for(auto i = this->vertexes.begin(); i != this->vertexes.end(); i++){ //Iteramos todos los vertices menos el que va a eliminar
        if((*i).second != this->vertexes[id]){
            auto aristas = (*i).second->edges;
            for(auto j = aristas.begin(); j != aristas.end(); j++){//aristas de dichos vertices que no va a eliminar
                if((*j)->vertexes[1] == this->vertexes[id]){
                    aristas.erase(j);
                    nro_arsistas-- //ATENCION: No estoy seguro si se deba poner esto pero porsiaca xd
                    break;
                }
            }
        }
    }
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
        nro_arsistas--;
        aristas_ady->pop_front();
    }
    return true;
};

template<typename TV, typename TE>
bool DirectedGraph<TV,TE>::deleteEdge(string id1, string id2){
    if(this->vertexes.count(id1) == 0 || this->vertexes.count(id2) == 0){
        return false;
    }

    auto aristas_ady_id1 = &(this->vertexes[id1])->edges;
    for(auto i = aristas_ady_id1.begin(); i != aristas_ady_id1.end(); i++){
        if(((*i)->vertexes[1])->id == id2){
            aristas_ady_id1.erase(i);
            nro_aristas--;
            return true;
        }
    }
    return false;
};

template<typename TV, typename TE>
TE& DirectedGraph<TV,TE>::operator()(string start, string end){
    if(!findById(start)){
        cout<<"No existe vertice"<<endl;
        return -1;
    }
    auto aristas = this->vertexes[start]->edges;
    for(auto i:aristas){
        if(i->vertexes[0] == this->vertexes[end] || i->vertexes[1] == this->vertexes[end]){
            return i->weight;
        }
    }
    cout<<"La conexion no existe"<<endl;
    return -1;
}

template<typename TV, typename TE>
float DirectedGraph<TV,TE>::density(){
    int vertices = this->vertexes.size();
    return 2 * nro_arsistas / ((float) vertices * (V - 1));
}

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
        string id = i.first; //PRIMER VERTICE DE INICIO
        auto aristas = (this->vertexes[id])->edges; //sus aristas adyacentes

        for(auto j:aristas){ //recorres sus aristas
            string ids = (j->vertexes[1])->id //almacenas sus vertices de llegada
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