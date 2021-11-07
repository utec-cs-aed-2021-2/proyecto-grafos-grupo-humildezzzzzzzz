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
private:
    int nro_aristas = 0;
public:
    UnDirectedGraph() = default; //LISTO
    UnDirectedGraph(string id, TV vertex){ //LISTO
        this->insertVertex(id,vertex)
    }
    ~UnDirectedGraph();

    bool insertVertex(string id, TV vertex); //LISTO
    bool createEdge(string id1, string id2, TE w); //LISTO
    bool deleteVertex(string id); //LISTO
    bool deleteEdges(string id); //LISTO
    bool deleteEdge(string id1, string id2); //LISTO
    TE &operator()(string start, string end); //LISTO
    float density(); //LISTO
    bool isDense(float threshold = 0.5); //LISTO
    bool isConnected(); 
    bool isStronglyConnected(); //LISTO
    bool empty(); //LISTO
    void clear(); //LISTO
    void displayVertex(string id); //LISTO
    bool findById(string id); //LISTO
    void display(); //LISTO
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
    int Vertices = this->vertexes.size();
    return 2 * this->nro_aristas / ((float) V * (V - 1));
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
    while(!this->vertexes.empty()){
        auto i = *this->vertexes.begin();
        deleteVertex(i.first);
    }
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
}

template<typename TV,typename TE>
TE& UnDirectedGraph<TV,TE>::operator()(string start, string end){
    if(!findById(start)){
        std::cout<<"No existe el vertice"<<endl;
        return -1;
    }
    auto aristas = (this->vertex[start])->edges; //aristas de nuestro vertice de inicio
    for(auto i: aristas){
        if(i->vertexes[0] == this->vertexes[end] || i->vertexes[1] == this->vertexes[end]){
            return i->weight
        }
    }
    std::cout<<"No existe la conexion"<<endl;
    return -1;
}

template<typename TV,typename TE>
UnDirectedGraph<TV,TE>::~UnDirectedGraph(){
    while(this->vertexes.size() != 0){
        deleteVertex((*this->vertexes.begin()).first);
    }
}
#endif