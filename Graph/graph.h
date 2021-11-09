#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <vector>
#include <unordered_map>

using namespace std;

template<typename TV, typename TE>
struct Edge;

template<typename TV, typename TE>
struct Vertex;

template<typename TV, typename TE>
class Graph;

//////////////////////////////////////////////////////

template<typename TV, typename TE>
struct Edge {
    Vertex<TV, TE>* vertexes; // un array de vertices donde almacena 2 nodos que estan conectados
    TE weight; //peso de la arista
};

template<typename TV, typename TE>
struct Vertex {
    TV data; //Data del vertice
    string id;
    std::list<Edge<TV, TE>*> edges; //lista de aristas a las cuales esta conectada el nodo
};

template<typename TV, typename TE>
class Graph{
protected:    
    std::unordered_map<string, Vertex<TV, TE>*>  vertexes; //key = id del nodo, value = vertice
public:
    virtual bool insertVertex(string id, TV vertex) = 0;   
    virtual bool createEdge(string id1, string id2, TE w) = 0;     
    virtual bool deleteVertex(string id) = 0;     
    virtual bool deleteEdge(string id1, string id2) = 0;   
    virtual TE &operator()(string start, string end)= 0;  
    virtual float density() = 0;
    virtual bool isDense(float threshold = 0.5) = 0;
    virtual bool isConnected()= 0;
    virtual bool isStronglyConnected()=0;
    virtual bool empty()=0;
    virtual void clear()= 0;
    virtual void displayVertex(string id)= 0;
    virtual bool findById(string id) = 0;
    virtual void display() = 0;
    virtual unordered_map<string,Vertex<TV,TE>*>* get_vertexes() = 0;
};

#endif