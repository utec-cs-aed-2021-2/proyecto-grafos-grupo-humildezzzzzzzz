#include "../UndirectedGraph.h"
#include "../DirectedGraph.h"
#include <map>
#include <unordered_map>
#include <string>
#include <deque>
#include <unordered_set>
#include <queue>

/*
template<typename TV,typename TE>
struct Comparator{ //Comparador para la priority queue
    bool operator()(const pair<Vertex<TV,TE>*, TE>& p1, const pair<Vertex<TV,TE>*, TE>& p2){
        if(p1.second > p2.second){
            return true;
        }
        return false;
    }
};
*/
template<typename TV,typename TE>
class BestBFS{
private:
    map<string,string> Ida; //mapa que nos indica a donde se dirige un nodo
    deque<string> path; //almacena nuestro camino de nodos que se recorrera en el grafo
    UnDirectedGraph<TV,TE>* result= new UnDirectedGraph<TV,TE>; //Nos mostrara el resultado en forma de grafo
public:

    explicit BestBFS(Graph<TV,TE>* grafo, string inicio, string fin, unordered_map<string,TE> heuristica){
        //priority_queue<pair<Vertex<TV,TE>*, TE>, vector<pair<Vertex<TV,TE>*, TE>>, Comparator<TV,TE>> open; //Nos indicara de manera ordenada los nodos abiertos para recorrer
        //unordered_set<string> open1; //set de nodos abiertos
        //unordered_set<string> close; //set de nodos ya recorridos
/*
        map<string, TE> scoreG;
        scoreG[inicio] = 0; //costo inicial o coste realista
        map<string, TE> scoreF;
        scoreF[inicio] = heuristica[inicio]; //coste ideal para llegar a nuestro destino
*/
        auto vertexes = *(grafo->get_vertexes());
        auto current = vertexes[inicio];
        auto weight = heuristica[current->id];
        auto Inicial = *vertexes[inicio];
        result->insertVertex(Inicial.id, Inicial.data);
        auto edge = *(current->edges.begin());

        while(heuristica[current->id]!=0){


            for(auto i = current->edges.begin(); i != current->edges.end(); i++){

                if(heuristica[(*i)->vertexes[0].id]<weight){
                    edge = *(i);
                    weight = heuristica[edge->vertexes[0].id];
                }

            }

            Inicial = *current;
            *current = (edge->vertexes[0]);
            result->insertVertex(current->id, current->data);
            result->createEdge(Inicial.id, current->id, edge->weight);


        }


    }

    UnDirectedGraph<TV,TE>* get_grafo(){
        return result;
    }
};
