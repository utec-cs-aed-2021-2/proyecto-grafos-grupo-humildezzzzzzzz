//
// Created by matia on 12/7/2021.
//

#ifndef GRAFOS_PROYECTO_WARSHALL_H
#define GRAFOS_PROYECTO_WARSHALL_H


#include <stack>
#include <iostream>
#include <unordered_map>
#include<algorithm>
#include "../DirectedGraph.h"
#include "../UndirectedGraph.h"

using namespace std;

template<typename TV,typename TE>
class warshall{
private:
    DirectedGraph<TV, TE> *Grafo;
public:
        template<typename T>
        warshall(T* graph){
            Grafo = new DirectedGraph<TV,TE>;
            auto vert=*(graph->get_vertexes());
            int n=vert.size();
            unordered_map<string,int> pc;
            vector<string> revers(n);
            int ind=0;
            for(auto &x:vert){
                pc[x.first]=ind;
                revers[ind]=x.first;
                ind++;
                Grafo->insertVertex(x.first,x.second->data);
            }

            TE dist[n][n];

            for(int i=0;i<n;i++){
                for(int j=0;j<n;j++) dist[i][j]=2147483647;
                dist[i][i]=0;
            }

            for(auto &x:vert){
                for(auto &y:x.second->edges) dist[pc[x.first]][pc[y->vertexes->id]]=y->weight;
            }


            for (int k = 0; k < n; ++k) {
                for (int i = 0; i < n; ++i) {
                    for (int j = 0; j < n; ++j) {
                        if (dist[i][k] < 2147483647 && dist[k][j] < 2147483647) dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                    }
                }
            }

            for(int i=0;i<n;i++){
                for(int j=0;j<n;j++){
                    if(dist[i][j]!=2147483647){
                        Grafo->createEdge(revers[i],revers[j],dist[i][j]);
                    }
                }
            }

        }

    DirectedGraph<TV,TE>* get_grafo(){
        return Grafo;
    }
};

#endif //GRAFOS_PROYECTO_WARSHALL_H
