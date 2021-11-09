#include <queue>
#include <set>
#include "../DirectedGraph.h"
#include "../UndirectedGraph.h"

template<typename TV,typename TE>
class bfs{
private:
    DirectedGraph<TV,TE>* Grafo;

public:
    bfs() = default;

    bfs(UnDirectedGraph<TV,TE>* graph, string vertex_id){
        std::set<string> visitados;
        std::queue<Vertex<TV,TE>*> q;
        auto temp = *(graph->get_vertexes());
        auto primero=temp[vertex_id];

        Grafo = new DirectedGraph<TV,TE>;
        Grafo->insertVertex(vertex_id,primero->data);

        q.push(primero);

        while(!q.empty()){
            auto actual = q.front();
            q.pop();
            visitados.insert(actual->id);
            for(auto &a : temp[actual->id]->edges){
                if(visitados.count(a->vertexes->id)==0){
                    Grafo->insertVertex(a->vertexes->id,a->vertexes->data);
                    Grafo->createEdge(actual->id,a->vertexes->id,a->weight);
                    q.push(a->vertexes);
                }
            }
        }
    }

    bfs(DirectedGraph<TV,TE>* graph, string vertex_id){
        std::set<string> visitados;
        std::queue<Vertex<TV,TE>*> q;
        auto temp = *(graph->get_vertexes());
        auto primero=temp[vertex_id];

        Grafo = new DirectedGraph<TV,TE>;
        Grafo->insertVertex(vertex_id,primero->data);

        q.push(primero);
        

        while(!q.empty()){
            auto actual = q.front();
            q.pop();
            visitados.insert(actual->id);
            for(auto &a : temp[actual->id]->edges){
                if(visitados.count(a->vertexes->id)==0){
                    Grafo->insertVertex(a->vertexes->id,a->vertexes->data);
                    Grafo->createEdge(actual->id,a->vertexes->id,a->weight);
                    q.push(a->vertexes);
                }
            }
        }
    }

    DirectedGraph<TV,TE>* get_grafo(){
        return Grafo;
    }

};
