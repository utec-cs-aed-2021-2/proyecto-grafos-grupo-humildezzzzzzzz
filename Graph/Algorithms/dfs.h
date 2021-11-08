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

    dfs(UnDirectedGraph<TV,TE>* &graph, string vertex_id){
        std::unordered_set<string> visitados;
        std::stack<pair<string, Vertex<TV,TE>*>> st;
        string primero;

        auto temp = graph->vertexes;
        auto aux = graph->vertexes[vertex_id];
        Grafo = new DirectedGraph<TV,TE>;
        Grafo->insertVertex(vertex_id,aux->data);

        for(auto &i : temp){
            primero = i.first;
            visitados.insert(primero);
            st.push(make_pair(primero,((temp.second)->edges)->vertexes));

            while(!st.empty()){
                pair<string,Vertex<TV,TE>*> actual = st.top();
                st.pop();
                string id;
                Vertex<TV,TE>* to_insert;
                id = actual.first;
                to_insert = actual.second;

                if(visitados.find(to_insert->id) == visitados.end()){
                    visitados.insert(to_insert->id);
                    Grafo->insertVertex(to_insert->id,to_insert->data);
                    Grafo->insertEdge(id,to_insert->id,1);
                }

                for(auto &a : to_insert->edges){
                    if(visitados.find(a->vertexes->id) == visitados.end()){
                        st.push(make_pair(to_insert->id,a->vertexes));
                    }
                }
            }
        }
    }

    dfs(DirectedGraph<TV,TE>* &graph, string vertex_id){
        std::unordered_set<string> visitados;
        std::stack<pair<string, Vertex<TV,TE>*>> st;
        string primero;

        auto temp = graph->vertexes;
        auto aux = graph->vertexes[vertex_id];
        Grafo = new DirectedGraph<TV,TE>;
        Grafo->insertVertex(vertex_id,aux->data);

        for(auto &i : temp){
            primero = i.first;
            visitados.insert(primero);
            st.push(make_pair(primero,((temp.second)->edges)->vertexes));

            while(!st.empty()){
                pair<string,Vertex<TV,TE>*> actual = st.top();
                st.pop();
                string id;
                Vertex<TV,TE>* to_insert;
                id = actual.first;
                to_insert = actual.second;

                if(visitados.find(to_insert->id) == visitados.end()){
                    visitados.insert(to_insert->id);
                    Grafo->insertVertex(to_insert->id,to_insert->data);
                    Grafo->insertEdge(id,to_insert->id,1);
                }

                for(auto &a : to_insert->edges){
                    if(visitados.find(a->vertexes->id) == visitados.end()){
                        st.push(make_pair(to_insert->id,a->vertexes));
                    }
                }
            }
        }
    }
};