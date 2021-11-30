#include "../UndirectedGraph.h"
#include "../DirectedGraph.h"
#include <map>
#include <unordered_map>
#include <string>
#include <deque>
#include <unordered_set>
#include <queue>

template<typename TV,typename TE>
struct Comparator{ //Comparador para la priority queue
    bool operator()(const pair<Vertex<TV,TE>*, TE>& p1, const pair<Vertex<TV,TE>*, TE>& p2){
        if(p1.second > p2.second){
            return true;
        }
        return false;
    }
};

template<typename TV,typename TE>
class Astar{
private:
    map<string,string> Ida; //mapa que nos indica a donde se dirige un nodo
    deque<string> path; //almacena nuestro camino de nodos que se recorrera en el grafo
    UnDirectedGraph<TV,TE>* result; //Nos mostrara el resultado en forma de grafo
public:

    explicit Astar(Graph<TV,TE>* grafo, string inicio, string fin, unordered_map<string,TE> heuristica){
        priority_queue<pair<Vertex<TV,TE>*, TE>, vector<pair<Vertex<TV,TE>*, TE>>, Comparator<TV,TE>> open; //Nos indicara de manera ordenada los nodos abiertos para recorrer
        unordered_set<string> open1; //set de nodos abiertos
        unordered_set<string> close; //set de nodos ya recorridos

        map<string, TE> scoreG;
        scoreG[inicio] = 0; //costo inicial o coste realista
        map<string, TE> scoreF;
        scoreF[inicio] = heuristica[inicio]; //coste ideal para llegar a nuestro destino
        
        auto vertexes = *(grafo->get_vertexes());

        open.push(make_pair(vertexes[inicio], scoreF[inicio])); //Pusheamos el primer nodo

        while(!open.empty()){
            Vertex<TV,TE>* current = open.top().first;
            open.pop(); //lo sacamos del open set
            if(current->id == fin){ //Si el id del nodo actual es el mismo que nuestro nodo final
                cout<<current->id<<" tiene un coste de "<<scoreG[current->id]<<" y si se incluye la heuristica se tendria de coste "<<scoreF[current->id]<<endl;
                cout<<"--------------BACKTRACKING--------------"<<endl;
                construir_camino(current->id,grafo,inicio); //Reconstruimos el camino
                return;
            }

            close.insert(current->id); //Lo incluimos en el set de nodos tomados
            for(auto i = current->edges.begin(); i != current->edges.end(); i++){ //For para sacar nuestro menor coste para llegar al final
                string aux = (*i)->vertexes->id; //auxiliar toma el nodo de llegada del nodo actual
                if(close.find(aux) != close.end()){ //si ese nodo ha sido tomado, entonces continua
                    continue;
                }
                TE scoreG_posible = scoreG[current->id] + (*i)->weight; //calculamos el coste ideal para llegar al destino

                //Este if toma los nodos candidatos a para llegar al final
                if(open1.find(aux) == open1.end()){ //Si en nuestro set de nodos abierto no esta el nodo de llegada, entonces se calculan los costes
                    Ida[aux] = current->id; 
                    scoreG[aux] = scoreG_posible; //Realista
                    scoreF[aux] = scoreG_posible + heuristica[aux]; //Ideal segun heuristica
                    open.push(make_pair((*i)->vertexes, scoreF[aux])); //Se incluye en la priority_queue de nodos abiertos
                    open1.insert(aux); //Se incluye en el set de nodos abiertos
                }

                if(scoreG_posible >= scoreG[(*i)->vertexes->id]){ //Si el score candidato es mayor o igual al que tenemos ahorita
                    continue; //continuamos
                }

                Ida[aux] = current->id; //Se incluye en el camino 
                scoreG[aux] = scoreG_posible; //El score posible es ahora nuestro actual score
                scoreF[aux] = scoreG_posible + heuristica[(*i)->vertexes->id]; //Score ideal tomando heuristica 
            }
        }
    }

    void construir_camino(string current, Graph<TV,TE>* grafo, const string& inicio){
        path.push_front(current);
        result = new UnDirectedGraph<TV,TE>;

        while(Ida.find(current) != Ida.end() && current != inicio){
            auto vertexes = *(grafo->get_vertexes()); //Si el nodo actual ha sido visitado y es diferente al nodo de inicio
            Vertex<TV,TE>* v1 = vertexes[current]; //Tomamos el nodo actual

            result->insertVertex(v1->id,v1->data); //Lo incluimos en el grafo
            current = Ida[current]; //tomamos el siguiente nodo que conecta con nuestro actual nodo

            Vertex<TV,TE>* v2 = vertexes[current]; //tomamos el siguiente nodo
            result->insertVertex(v2->id,v2->data); //lo insertamos en nuestro grafo
            TE p = 0; //peso

            for(auto i = v1->edges.begin(); i != v1->edges.end(); i++){ //for para obtener el peso de la conexion entre los nodos
                if(current == (*i)->vertexes->id){
                    p = (*i)->weight; //Se le suma el peso
                }
            }
            result->createEdge(v1->id,v2->id,p); //Creamos la arista
            cout<<v1->id<<" su padre es "<<v2->id<<endl;
            path.push_front(current); //pusheamos al camino
        }
    }

    void display(){
        cout<<"------- CAMINO FINAL ----------"<<endl;
        for(auto& i:path){
            cout<<i<<" -> ";
        }
        cout<<endl;
    }
    UnDirectedGraph<TV,TE>* get_grafo(){
        return result;
    }
};
