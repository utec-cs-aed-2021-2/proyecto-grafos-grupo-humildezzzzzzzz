#include "../UndirectedGraph.h"
#include "../DirectedGraph.h"
#include <unordered_map>
#include <unordered_set>

template<typename TV, typename TE>
string Distancia_minima(Graph<TV,TE>* &grafo, unordered_map<string,int>& dist, unordered_map<string,bool>& mapita){
    //La variable mapita es para identificar si el nodo ha sido visitado
    int num = INT32_MAX;
    string indice;

    auto vertexes = *(grafo->get_vertexes());

    for(auto &i:vertexes){
        if(dist[i.second->id] <= num && !mapita[i.second->id]){
            indice = i.second->id;
        }
    }
    return indice;
}

template<typename TV, typename TE>
string Distancia_minima(UnDirectedGraph<TV,TE>* &grafo, unordered_map<string,int>& dist, unordered_map<string,bool>& mapita){
    //La variable mapita es para identificar si el nodo ha sido visitado
    int num = INT32_MAX;
    string indice;

    auto vertexes = *(grafo->get_vertexes());

    for(auto &i:vertexes){
        if(dist[i.second->id] <= num && !mapita[i.second->id]){
            indice = i.second->id;
        }
    }
    return indice;
}

template<typename TV, typename TE>
string Distancia_minima(DirectedGraph<TV,TE>* &grafo, unordered_map<string,int>& dist, unordered_map<string,bool>& mapita){
    //La variable mapita es para identificar si el nodo ha sido visitado
    int num = INT32_MAX;
    string indice;

    auto vertexes = *(grafo->get_vertexes());

    for(auto &i:vertexes){
        if(dist[i.second->id] <= num && !mapita[i.second->id]){
            indice = i.second->id;
        }
    }
    return indice;
}

template<typename TV, typename TE>
class Dijkstra{
private:
    DirectedGraph<TV,TE>* result;
public:
    Dijkstra() = default;
    Dijkstra(Graph<TV,TE>* grafo, const string& id){
        result = new DirectedGraph<TV,TE>;
        unordered_map<string,int> dist; //Guarda la distancia o el coste desde un nodo
        unordered_map<string,bool> mapita; //Almacena nuestro nodos e identifica si estos fueron tomados en cuenta para la construcion del camino
        unordered_map<string,pair<Vertex<TV,TE>*,string>> vertices_distancia; //Mapa del vertice y a donde se dirige

        auto vertexes = *(grafo->get_vertexes());
        for(auto &i:vertexes){ //Recorremos todos los vertices del grafo
            if(i.second->id == id){ //Si el id de nuestro vertice es igual al de nuestra llegada 
                dist[i.second->id] = 0; //Se pone 0
            }
            else{
                dist[i.second->id] = INT32_MAX; //Sino, se le considera como infinito
            }

            mapita[i.second->id] = false; //Se le añade al mapa como primer nodo no incluido en el camino corto
            pair<Vertex<TV,TE>*, string> aux (i.second,i.second->id); //variable auxiliar del nodo de llegada
            vertices_distancia[i.second->id] = aux; //se incluye en el mapa con su id y nodo (servira para constuir el camino)
            result->insertVertex(i.second->id,i.second->data); //Se le inserta al grafo
        }

        for(int i = 0; i < vertexes.size() - 1;i++){ //recorremos n - 1 nodos
            string dist_min = Distancia_minima(grafo,dist,mapita); //tomamos el nodo que nos da la minima distancia
            mapita[dist_min] = true; //Lo incluimos en el mapita como uno de los nodos que nos construye el camino opotimo
            
            for(auto j:vertexes){ //Recorremos los vertices 
                if(dist[dist_min] != INT32_MAX && !mapita[j.second->id]){ //Si el nodo que nos da la minima distancia es diferente de infinito y el vertice a evaluar no ha sido tomado en cuenta para el camino corto
                    auto nodo = vertices_distancia[dist_min].first; //tomamos el nodo perteneciente al camino corto
                    for(auto k : nodo->edges){ //recorremos sus aristas
                        if(k->vertexes->id == j.second->id){ //Si su vertice de llegada es igual al vertice que estamos evaluando
                            if(dist[j.second->id] > dist[dist_min] + k->weight){ //Si la distancia hasta ese punto con el nodo a evaluar es mayor a la suma del nodo con la distancia minima y uno de los pesos de sus aristas a otros nodos
                                dist[j.second->id] = dist[dist_min] + k->weight; //Entonces se le asigna un nuevo coste al camino 
                                pair<Vertex<TV,TE>*, string> aux (vertices_distancia[j.second->id].first,dist_min); 
                                vertices_distancia[j.second->id] = aux; //incluimos el nodo actual con su nuevo coste y nodo de llegada, que en ese caso sera el nodo que da el camino corto
                            }
                        }
                    }
                }
            }
        }

        auto x = *vertices_distancia.begin(); //tomamos el objeto de la primera posicion
        for(auto &i : vertices_distancia){ //recorremos los vertices que arman el camino corto
            if(i.first != x.first){ //si el id es diferente en ambos
                auto k = i.second; //asignamos el par
                auto sz = dist[i.second.first->id]; //su coste actual
                if(k.first->id != k.second){ //si el id del nodo es diferente al de llegada
                    sz -= dist[k.second]; //se restan sus costes
                }
                result->createEdge(k.second,k.first->id,sz); //Creamos la arista con su coste individual (NO COSTE ACUMULADO) y sus nodos conectados
            }
        }
    }

    Dijkstra(DirectedGraph<TV,TE>* grafo, const string& id){
        result = new DirectedGraph<TV,TE>;
        unordered_map<string,int> dist; //Guarda la distancia o el coste desde un nodo
        unordered_map<string,bool> mapita; //Almacena nuestro nodos e identifica si estos fueron tomados en cuenta para la construcion del camino
        unordered_map<string,pair<Vertex<TV,TE>*,string>> vertices_distancia; //Mapa del vertice y a donde se dirige

        auto vertexes = *(grafo->get_vertexes());
        for(auto &i:vertexes){ //Recorremos todos los vertices del grafo
            if(i.second->id == id){ //Si el id de nuestro vertice es igual al de nuestra llegada 
                dist[i.second->id] = 0; //Se pone 0
            }
            else{
                dist[i.second->id] = INT32_MAX; //Sino, se le considera como infinito
            }

            mapita[i.second->id] = false; //Se le añade al mapa como primer nodo no incluido en el camino corto
            pair<Vertex<TV,TE>*, string> aux (i.second,i.second->id); //variable auxiliar del nodo de llegada
            vertices_distancia[i.second->id] = aux; //se incluye en el mapa con su id y nodo (servira para constuir el camino)
            result->insertVertex(i.second->id,i.second->data); //Se le inserta al grafo
        }

        for(int i = 0; i < vertexes.size() - 1;i++){ //recorremos n - 1 nodos
            string dist_min = Distancia_minima(grafo,dist,mapita); //tomamos el nodo que nos da la minima distancia
            mapita[dist_min] = true; //Lo incluimos en el mapita como uno de los nodos que nos construye el camino opotimo
            
            for(auto j:vertexes){ //Recorremos los vertices 
                if(dist[dist_min] != INT32_MAX && !mapita[j.second->id]){ //Si el nodo que nos da la minima distancia es diferente de infinito y el vertice a evaluar no ha sido tomado en cuenta para el camino corto
                    auto nodo = vertices_distancia[dist_min].first; //tomamos el nodo perteneciente al camino corto
                    for(auto k : nodo->edges){ //recorremos sus aristas
                        if(k->vertexes->id == j.second->id){ //Si su vertice de llegada es igual al vertice que estamos evaluando
                            if(dist[j.second->id] > dist[dist_min] + k->weight){ //Si la distancia hasta ese punto con el nodo a evaluar es mayor a la suma del nodo con la distancia minima y uno de los pesos de sus aristas a otros nodos
                                dist[j.second->id] = dist[dist_min] + k->weight; //Entonces se le asigna un nuevo coste al camino 
                                pair<Vertex<TV,TE>*, string> aux (vertices_distancia[j.second->id].first,dist_min); 
                                vertices_distancia[j.second->id] = aux; //incluimos el nodo actual con su nuevo coste y nodo de llegada, que en ese caso sera el nodo que da el camino corto
                            }
                        }
                    }
                }
            }
        }

        auto x = *vertices_distancia.begin(); //tomamos el objeto de la primera posicion
        for(auto &i : vertices_distancia){ //recorremos los vertices que arman el camino corto
            if(i.first != x.first){ //si el id es diferente en ambos
                auto k = i.second; //asignamos el par
                auto sz = dist[i.second.first->id]; //su coste actual
                if(k.first->id != k.second){ //si el id del nodo es diferente al de llegada
                    sz -= dist[k.second]; //se restan sus costes
                }
                result->createEdge(k.second,k.first->id,sz); //Creamos la arista con su coste individual (NO COSTE ACUMULADO) y sus nodos conectados
            }
        }
    }

    Dijkstra(UnDirectedGraph<TV,TE>* grafo, const string& id){
        result = new DirectedGraph<TV,TE>;
        unordered_map<string,int> dist; //Guarda la distancia o el coste desde un nodo
        unordered_map<string,bool> mapita; //Almacena nuestro nodos e identifica si estos fueron tomados en cuenta para la construcion del camino
        unordered_map<string,pair<Vertex<TV,TE>*,string>> vertices_distancia; //Mapa del vertice y a donde se dirige

        auto vertexes = *(grafo->get_vertexes());
        for(auto &i:vertexes){ //Recorremos todos los vertices del grafo
            if(i.second->id == id){ //Si el id de nuestro vertice es igual al de nuestra llegada 
                dist[i.second->id] = 0; //Se pone 0
            }
            else{
                dist[i.second->id] = INT32_MAX; //Sino, se le considera como infinito
            }

            mapita[i.second->id] = false; //Se le añade al mapa como primer nodo no incluido en el camino corto
            pair<Vertex<TV,TE>*, string> aux (i.second,i.second->id); //variable auxiliar del nodo de llegada
            vertices_distancia[i.second->id] = aux; //se incluye en el mapa con su id y nodo (servira para constuir el camino)
            result->insertVertex(i.second->id,i.second->data); //Se le inserta al grafo
        }

        for(int i = 0; i < vertexes.size() - 1;i++){ //recorremos n - 1 nodos
            string dist_min = Distancia_minima(grafo,dist,mapita); //tomamos el nodo que nos da la minima distancia
            mapita[dist_min] = true; //Lo incluimos en el mapita como uno de los nodos que nos construye el camino opotimo
            
            for(auto j:vertexes){ //Recorremos los vertices 
                if(dist[dist_min] != INT32_MAX && !mapita[j.second->id]){ //Si el nodo que nos da la minima distancia es diferente de infinito y el vertice a evaluar no ha sido tomado en cuenta para el camino corto
                    auto nodo = vertices_distancia[dist_min].first; //tomamos el nodo perteneciente al camino corto
                    for(auto k : nodo->edges){ //recorremos sus aristas
                        if(k->vertexes->id == j.second->id){ //Si su vertice de llegada es igual al vertice que estamos evaluando
                            if(dist[j.second->id] > dist[dist_min] + k->weight){ //Si la distancia hasta ese punto con el nodo a evaluar es mayor a la suma del nodo con la distancia minima y uno de los pesos de sus aristas a otros nodos
                                dist[j.second->id] = dist[dist_min] + k->weight; //Entonces se le asigna un nuevo coste al camino 
                                pair<Vertex<TV,TE>*, string> aux (vertices_distancia[j.second->id].first,dist_min); 
                                vertices_distancia[j.second->id] = aux; //incluimos el nodo actual con su nuevo coste y nodo de llegada, que en ese caso sera el nodo que da el camino corto
                            }
                        }
                    }
                }
            }
        }

        auto x = *vertices_distancia.begin(); //tomamos el objeto de la primera posicion
        for(auto &i : vertices_distancia){ //recorremos los vertices que arman el camino corto
            if(i.first != x.first){ //si el id es diferente en ambos
                auto k = i.second; //asignamos el par
                auto sz = dist[i.second.first->id]; //su coste actual
                if(k.first->id != k.second){ //si el id del nodo es diferente al de llegada
                    sz -= dist[k.second]; //se restan sus costes
                }
                result->createEdge(k.second,k.first->id,sz); //Creamos la arista con su coste individual (NO COSTE ACUMULADO) y sus nodos conectados
            }
        }
    }

    DirectedGraph<TV,TE>* get_grafo(){
        return result;
    }


};
