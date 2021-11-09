#ifndef NONDIRECTEDGRAPH_H
#define NONDIRECTEDGRAPH_H

#include "graph.h"


template<typename TV, typename TE>
class DirectedGraph : public Graph<TV, TE>{
    private:
    int nro_aristas;
    public:

    DirectedGraph() = default;
    DirectedGraph(string id, TV vertex){ //LISTO
        this->insertVertex(id,vertex);
    }

    ~DirectedGraph();
    bool insertVertex(string id, TV vertex); //LISTO 
    bool createEdge(string id1, string id2, TE w); //LISTO
    bool deleteVertex(string id); //LISTO
    bool deleteEdges(string id); //LISTO
    void printeo();
    bool deleteEdge(string id1, string id2); //LISTO
    TE &operator()(string start, string end); //LISTO
    float density(); //LISTO
    bool isDense(float threshold = 0.5); //LISTO
    bool findById(string id); //LISTO
    bool isStronglyConnected(); //LISTO
    bool isConnected(); //LISTO
    bool empty(); //LISTO
    void clear(); //LISTO
    void displayVertex(string id); //PREGUNTAR AL PROFESOR 
    void display(); //LISTO
    unordered_map<string, Vertex<TV, TE>*>*  get_vertexes();
};

template<typename TV,typename TE>
unordered_map<string,Vertex<TV,TE>*>* DirectedGraph<TV,TE>::get_vertexes(){
    return &(this->vertexes);
};

template<typename TV, typename TE>
bool DirectedGraph<TV,TE>::insertVertex(string id, TV vertex){
    if(this->vertexes.count(id) == 1) return false;
    Vertex<TV, TE>* vertice = new Vertex<TV, TE>;
    vertice->data=vertex;
    vertice->id = id;
    this->vertexes[id]=vertice;
    return true;
}

template<typename TV, typename TE>
bool DirectedGraph<TV,TE>::createEdge(string id1, string id2, TE w){
    if(this->vertexes.count(id1) == 0 || this->vertexes.count(id2) == 0) return false;
    auto* new_edge = new Edge<TV,TE>;
    new_edge->vertexes = this->vertexes[id2];
    new_edge->weight = w;
    this->vertexes[id1]->edges.push_back(new_edge);
    nro_aristas++;
    return true;
}

template<typename TV, typename TE>
bool DirectedGraph<TV,TE>::  deleteVertex(string id){
    if(this->vertexes.count(id) == 0) return false;
    deleteEdges(id);
    for(auto i = this->vertexes.begin(); i != this->vertexes.end(); i++){
        if((*i).first != id){
            for(auto j = (*i).second->edges.begin(); j != (*i).second->edges.end(); j++){
                if((*j)->vertexes->id == id){
                    (*i).second->edges.erase(j);
                    nro_aristas--;
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
    if (this->vertexes.count(id) == 0) return false;
    nro_aristas=nro_aristas-this->vertexes[id]->edges.size();
    this->vertexes[id]->edges.clear();
    return true;
};

template<typename TV, typename TE>
void DirectedGraph<TV,TE>:: display(){
    for(auto i = this->vertexes.begin(); i != this->vertexes.end(); i++) { //Iteramos todos los vertices menos el que va a elimina
        cout<<"From "<<(*i).first<<endl;
        for(auto &x:(*i).second->edges){
            cout<<"To "<<x->vertexes->id<<" with "<<x->weight<<endl;
        }
        cout<<endl;
    }
};

template<typename TV, typename TE>
bool DirectedGraph<TV,TE>::deleteEdge(string id1, string id2){
    if(this->vertexes.count(id1) == 0 || this->vertexes.count(id2) == 0) return false;

    auto aristas_ady_id1 = &(this->vertexes[id1])->edges;
    for(auto i = aristas_ady_id1->begin(); i != aristas_ady_id1->end(); i++){
        if(((*i)->vertexes)->id == id2){
            aristas_ady_id1->erase(i);
            nro_aristas--;
            return true;
        }
    }
    return false;
};

template<typename TV, typename TE>
TE& DirectedGraph<TV,TE>::operator()(string start, string end){
    if(this->vertexes.count(start)==0 || this->vertexes.count(end)==0 ){
        cout<<"No existe vertice"<<endl;
        return *(new int(-1));
    }
    for(auto &i:this->vertexes[start]->edges){
        if(i->vertexes->id == end) return i->weight;
    }
    cout<<"La conexion no existe"<<endl;
    return *(new int(-1));
}

template<typename TV, typename TE>
float DirectedGraph<TV,TE>::density(){
    int vertices = this->vertexes.size();
    return 2 * nro_aristas / ((float) vertices * (vertices - 1));
}

template<typename TV, typename TE>
    bool DirectedGraph<TV,TE>::isDense(float threshold){ return this->density()>threshold;};

template<typename TV, typename TE>
    bool DirectedGraph<TV,TE>::isConnected(){
        std::set<pair<string,string>> caminos;
        std::set<string> visitados;
        std::stack<string> st;
        string primero;
        for(auto& a:this->vertexes){
            primero = a.first;
            visitados.insert(primero); //insertas el primer nodo
            st.push(primero);
            while(!st.empty()){
                auto actual = st.top(); //escojes el top de la pila
                st.pop(); //lo eliminas
                visitados.insert(actual); //lo insertas en los visitados
                for(auto &i: this->vertexes[actual]->edges){ //recorres sus aristas
                    if(visitados.count(i->vertexes->id) == 0){ //si no fue visitado
                        caminos.insert({primero,i->vertexes->id});
                        st.push(i->vertexes->id); //lo pusheas en la pila
                    }
                }
            }
            visitados.clear();
        }
        for(auto &x:this->vertexes){
            for(auto &y:this->vertexes){
                string a=x.second->id,b=y.second->id;
                if(a!=b){
                    if(caminos.count({a,b})==0 && caminos.count({b,a})==0) return 0;
                }
            }
        }
        return 1;
    };

template<typename TV, typename TE>
    bool DirectedGraph<TV,TE>::isStronglyConnected(){
        std::set<string> visitados;
        std::stack<string> st;
        string primero;
        for(auto& a:this->vertexes){
            primero = a.first;
            visitados.insert(primero); //insertas el primer nodo
            st.push(primero);
            while(!st.empty()){
                auto actual = st.top(); //escojes el top de la pila
                st.pop(); //lo eliminas
                visitados.insert(actual); //lo insertas en los visitados
                for(auto &i: this->vertexes[actual]->edges){ //recorres sus aristas
                    if(visitados.count(i->vertexes->id) == 0){ //si no fue visitado
                        st.push(i->vertexes->id); //lo pusheas en la pila
                    }
                }
            }
            if(visitados.size() != this->vertexes.size()) return false;
            visitados.clear();
            }
        return true;
    };

template<typename TV, typename TE>
bool DirectedGraph<TV,TE>::findById(string id){
    return this->vertexes.count(id);
};


template<typename TV, typename TE>
bool DirectedGraph<TV,TE>::empty(){
    return this->vertexes.empty();
};

template<typename TV, typename TE>
void DirectedGraph<TV,TE>::clear(){
    for(auto &x:this->vertexes){
        x.second->edges.clear();
        delete x.second;
    }
    this->vertexes.clear();
};

template<typename TV, typename TE>
void DirectedGraph<TV,TE>::displayVertex(string id){
    std::cout<<this->vertexes[id]->data<<std::endl;
};

template<typename TV, typename TE>
DirectedGraph<TV,TE>::~DirectedGraph(){
    while(this->vertexes.size() != 0){
        deleteVertex((*this->vertexes.begin()).first);
    }
}

#endif
