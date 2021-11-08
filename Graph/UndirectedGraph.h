#ifndef UNDIRECTEDGRAPH_H
#define UNDIRECTEDGRAPH_H

#include "graph.h"
#include <set>
#include <stack>

template<typename TV, typename TE>
class UnDirectedGraph : public Graph<TV, TE>{
private:
    int nro_aristas = 0;
public:
    UnDirectedGraph() = default; //LISTO
    UnDirectedGraph(string id, TV vertex){ //LISTO
        this->insertVertex(id,vertex);
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
    int size(){return this->vertexes.size();};
    int count(string id){return this->vertexes.count(id);};
};

template<typename TV, typename TE>
bool UnDirectedGraph<TV,TE>::insertVertex(string id, TV vertex){
    if(this->count(id) == 1){
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
    new_edge->weight = w;
    new_edge->vertexes=this->vertexes[id2];
    this->vertexes[id1]->edges.push_back(new_edge);

    new_edge->vertexes = this->vertexes[id1];
    
    this->vertexes[id2]->edges.push_back(new_edge);

    nro_aristas++;

    return true;
}

template<typename TV, typename TE>
bool UnDirectedGraph<TV,TE>::deleteEdges(string id){
    if (this->vertexes.count(id) == 0){
        return false;
    }

    auto aristas_ady = (this->vertexes[id])->edges; //solo tomo la lista de aristas para ese vertice
/*
    while(!aristas_ady.empty()){
        auto inicio = inicios(id,aristas_ady); //primer vertice de la primera arista
        auto llegada = llegadas(id,aristas_ady);//vertice de llegada de la primera arista

        for(auto i = (llegada.edges).begin(); i != (llegada.edges).end(); i++){ //recorro las demas aristas adyacentes al nodo de llegada
            if((*i)->vertexes[1] == inicio){ //si su vertice de llegada es igual al primer vertice de nuestra arista a eliminar
                (llegada.edges).erase(i); //borro la arista
                nro_aristas--;
                break;
            }
        }
        aristas_ady.pop_front(); //eliminamos la primera arista de nuestra lista de aristas adyacentes
    }
    */
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
    /*
    auto llegada1 = llegadas(id1,aristas_ady_id1);
    for(auto i = aristas_ady_id1.begin(); i != aristas_ady_id1.end(); i++){
        if(llegada1->id == id2){
            aristas_ady_id1.erase(i);
        }
    }

    auto aristas_ady_id2 = &(this->vertexes[id2])->edges;
    auto llegada2 = llegadas(id2,aristas_ady_id2);
    for(auto i = aristas_ady_id2.begin(); i != aristas_ady_id2.end(); i++){
        if(llegada2->id == id1){
            aristas_ady_id2.erase(i);
        }
    }
    */
    nro_aristas--;
    return true;
}

template<typename TV, typename TE>
float UnDirectedGraph<TV,TE>::density(){
    int Vertices = this->vertexes.size();
    return 2 * this->nro_aristas / ((float) Vertices * (Vertices - 1));
}

template<typename TV, typename TE>
bool UnDirectedGraph<TV,TE>::isDense(float threshold){ return this->density()>threshold;}

template<typename TV, typename TE>
bool UnDirectedGraph<TV,TE>::isConnected(){
    std::set<string> visitados;
    std::stack<Vertex<TV,TE>*> st;

    string primero = (*this->vertexes.begin()).first;
    visitados.insert(primero); //insertas el primer nodo
    auto aristas = (*this->vertexes.begin()).second->edges; //escojes sus aristas

    for(auto i:aristas){ // recorres sus aristas
        Vertex<TV,TE>* adj = i->vertexes; //tomas vertice de llegada
        if(visitados.find(adj->id) == visitados.end()){ //verificas si esta en la lista de visitados
            st.push(adj); //si no estas, lo pusheas al stack
        }
    }
    
    while(!st.empty()){
        Vertex<TV,TE>* top = st.top(); //escojes el top de la pila 
        st.pop(); //lo eliminas
        visitados.insert(top->id); //lo insertas en los visitados

        for(auto i: top->edges){ //recorres sus aristas
            Vertex<TV,TE>* adj = i->vertexes; // tomas sus vertices de llegada
            if(visitados.find(adj->id) == visitados.end()){ //si no fue visitado
                st.push(adj); //lo pusheas en la pila
            }
        }
    }

    if(visitados.size() == this->vertexes.size()){
        return true;
    }
    return false;
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
            string ids = (j->vertexes)->id;
            bool visitado = false;
            for(auto &k:visited){
                if((k.first == id && k.second == ids) || (k.first == ids && k.second == id)){
                    visitado = true;
                    break;
                }
            }

            if(!visitado){
                visited.push_back(make_pair(id,ids));
                std::cout<<"peso del vertice "<<id<<" al vertice "<<ids<<" es "<< j->weight<<endl;
            }
        }
    }
}

template<typename TV,typename TE>
TE& UnDirectedGraph<TV,TE>::operator()(string start, string end){
    if(!findById(start)){
        std::cout<<"No existe el vertice"<<endl;
        return *(new int(0));
    }
    auto aristas = (this->vertexes[start])->edges; //aristas de nuestro vertice de inicio
    for(auto i: aristas){
        if(i->vertexes == this->vertexes[end]){
            return i->weight;
        }
    }
    std::cout<<"No existe la conexion"<<endl;
    return *(new int(0));
}

template<typename TV,typename TE>
UnDirectedGraph<TV,TE>::~UnDirectedGraph(){
    while(this->size() != 0){
        deleteVertex(this->vertexes.begin()->first);
    }
}
#endif