#include <stack>
#include <unordered_set>
#include "../DirectedGraph.h"
#include "../UndirectedGraph.h"

template<typename TV,typename TE>
class dfs{
private:
    DirectedGraph<TV,TE>* Grafo;

public:
    dfs() = default;

    dfs(UnDirectedGraph<TV,TE>* graph, string vertex_id){
        std::set<string> visitados;
        std::stack<Vertex<TV,TE>*> st;
        auto temp = *(graph->get_vertexes());
        auto primero=temp[vertex_id];

        Grafo = new DirectedGraph<TV,TE>;
        Grafo->insertVertex(vertex_id,primero->data);

        st.push(primero);

        while(!st.empty()){
            auto actual = st.top();
            st.pop();
            visitados.insert(actual->id);
            for(auto &a : temp[actual->id]->edges){
                if(visitados.count(a->vertexes->id)==0){
                    Grafo->insertVertex(a->vertexes->id,a->vertexes->data);
                    Grafo->createEdge(actual->id,a->vertexes->id,a->weight);
                    st.push(a->vertexes);
                }
            }
        }
    }

    dfs(DirectedGraph<TV,TE>* graph, string vertex_id){
        std::set<string> visitados;
        std::stack<Vertex<TV,TE>*> st;
        auto temp = *(graph->get_vertexes());
        auto primero=temp[vertex_id];

        Grafo = new DirectedGraph<TV,TE>;
        Grafo->insertVertex(vertex_id,primero->data);

        st.push(primero);

        while(!st.empty()){
            auto actual = st.top();
            st.pop();
            visitados.insert(actual->id);
            for(auto &a : temp[actual->id]->edges){
                if(visitados.count(a->vertexes->id)==0){
                    Grafo->insertVertex(a->vertexes->id,a->vertexes->data);
                    Grafo->createEdge(actual->id,a->vertexes->id,a->weight);
                    st.push(a->vertexes);
                }
            }
        }
    }

    DirectedGraph<TV,TE>* get_grafo(){
        return Grafo;
    }

};
