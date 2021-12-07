//
// Created by matia on 12/7/2021.
//

#ifndef GRAFOS_PROYECTO_BELLMAN_H
#define GRAFOS_PROYECTO_BELLMAN_H

#include <stack>
#include <iostream>
#include <unordered_map>
#include<algorithm>
#include "../DirectedGraph.h"
#include "../UndirectedGraph.h"
using namespace std;

template<typename TV,typename TE>
class bellman{
private:
    DirectedGraph<TV, TE> *Grafo;
public:
        template<typename T>
        bellman(T* graph,string from){
            Grafo = new DirectedGraph<TV,TE>;
            auto vert=*(graph->get_vertexes());
            unordered_map<string,TE> dist;

            for(auto &x:vert){
                Grafo->insertVertex(x.first,x.second->data);
                dist[x.first] = 2147483647;
            }
            dist[from]=0;
            for(;;){
                bool any=0;
                for(auto &x:vert){
                    for(auto &y:x.second->edges){
                        if(dist[x.first]<2147483647){
                            if(dist[y->vertexes->id]>dist[x.first]+y->weight){
                                dist[y->vertexes->id]=dist[x.first]+y->weight;
                                any=1;
                            }
                        }
                    }
                }
                if(any==0) break;
            }
            for(auto &x:dist){
                if(x.second!=2147483647) Grafo->createEdge(from,x.first,x.second);
            }
        }

    DirectedGraph<TV,TE>* get_grafo(){
        return Grafo;
    }
};


#endif //GRAFOS_PROYECTO_BELLMAN_H
