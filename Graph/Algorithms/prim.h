#include <stack>
#include <iostream>
#include <unordered_map>
#include<algorithm>
#include "../DirectedGraph.h"
#include "../UndirectedGraph.h"
using namespace std;

template<typename TV,typename TE>
class prim{
private:
    DirectedGraph<TV, TE> *Grafo;
    struct edge_temp{
        TE w = 1e9;
        string to = "";
        edge_temp()= default;
        bool operator<(edge_temp const& other) const {
            return w < other.w;
        }
    };
public:
    prim(UnDirectedGraph<TV,TE>* graph){
        Grafo = new DirectedGraph<TV,TE>;
        TE total_w=0;

        set<edge_temp> q;
        unordered_map<string,edge_temp> min_e;
        unordered_map<string,bool> selected;
        auto vert=*(graph->get_vertexes());
        int n=graph->get_vertexes()->size();
        edge_temp temp;
        temp.w=0;temp.to=(vert.begin()->first);
        q.insert(temp);

        for (int i = 0; i <n; ++i) {
            if (q.empty()) {
                cout << "No MST!" << endl;
                exit(0);
            }

            string v = q.begin()->to;
            selected[v] = true;
            TE peso=q.begin()->w;
            total_w += q.begin()->w;
            q.erase(q.begin());

            if (min_e[v].to != ""){
                Grafo->insertVertex(v,vert[v]->data);
                Grafo->insertVertex(min_e[v].to,vert[min_e[v].to]->data);
                Grafo->createEdge(v,min_e[v].to,peso);
                cout << v << " " << min_e[v].to << ' '<<vert[v]->data<<endl;
            }

            for (auto &x : vert[v]->edges) {
                if (selected[x->vertexes->id]==0 && (x->weight) < min_e[x->vertexes->id].w) {
                    temp.w=min_e[x->vertexes->id].w;
                    temp.to=x->vertexes->id;
                    q.erase(temp);
                    min_e[x->vertexes->id] = {(x->weight), v};
                    q.insert({(x->weight),x->vertexes->id });
                }
            }
        }
    }

    DirectedGraph<TV,TE>* get_grafo(){
        return Grafo;
    }
};
