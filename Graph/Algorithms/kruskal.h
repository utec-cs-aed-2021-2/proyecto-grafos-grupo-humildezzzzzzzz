#include <stack>
#include <unordered_map>
#include<algorithm>
#include "../DirectedGraph.h"
#include "../UndirectedGraph.h"

template<typename TV,typename TE>
class kruskal{
private:
    struct nodo{
        int id,sz;
        nodo(){}
    };
    DirectedGraph<TV, TE> *Grafo;
    vector<nodo> aux;
public:
    kruskal(UnDirectedGraph<TV,TE>* graph){
        Grafo = new DirectedGraph<TV,TE>;
        if(graph->isConnected()==0){
            cout<<"No se puede hallar un arbol de expansion"<<endl;
        }else {
            unordered_map<string, int> mapeo;
            auto lista = *(graph->get_vertexes());
            int n = lista.size(), i = 0;
            vector<pair<TE, pair<string, string>>> vec;
            aux.resize(n);
            for (auto &x:lista) mapeo[x.first] = i, i++;
            i=0;
            for (int i = 0; i < n; i++) aux[i].sz = 0, aux[i].id = i;

            for (auto &x:lista) {
                for (auto &y:x.second->edges) vec.push_back({y->weight, {x.first, y->vertexes->id}});
            }
            sort(vec.begin(), vec.end());

            for(auto &x:vec){
                int a=mapeo[x.second.first],b=mapeo[x.second.second];
                if(are_connected(a,b)) continue;
                else{
                    Grafo->insertVertex(x.second.first,lista[x.second.first]->data);
                    Grafo->insertVertex(x.second.second,lista[x.second.second]->data);
                    Grafo->createEdge(x.second.first,x.second.second,x.first);
                    Union(a,b);
                }
            }
        }
    }
    int Find(int x){
        while(x != aux[x].id){
            aux[x].id = aux[aux[x].id].id;
            x = aux[x].id;
        }
        return x;
    }

    void Union(int a,int b){
        auto p = Find(a);
        auto q = Find(b);
        if(aux[p].sz > aux[q].sz){
            aux[q].id = aux[p].id;
            aux[p].sz += aux[q].sz;
        }
        else{
            aux[p].id = aux[q].id;
            aux[q].sz += aux[p].sz;
        }
    }

    bool are_connected(int a,int b){
        int x=Find(a);
        int y=Find(b);
        return x==y;
    }
    DirectedGraph<TV,TE>* get_grafo(){
        return Grafo;
    }
};
