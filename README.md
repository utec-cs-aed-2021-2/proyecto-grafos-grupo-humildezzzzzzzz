[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-f059dc9a6f8d3a56e377f745f24479a46679e63a5d9fe6f495e02850cd0d8118.svg)](https://classroom.github.com/online_ide?assignment_repo_id=6129282&assignment_repo_type=AssignmentRepo)
# Algoritmos y Estructura de Datos
## Proyecto sobre Grafos
--------

## Integrantes
- Juan Sebastian Sara Junco
- Denis Irala Morales
- Plinio Matias Avendaño Vargas

----

El proyecto del curso consiste en implementar una estructura genérica de grafo y un file parser. La cual debe soportar los métodos y algoritmos descritos a continuacion:  


## Graph data structure

* El grafo debe ser dinámico (inserciones. eliminaciones, búsquedas, ...)
* Se debe implementar los dos tipos de grafos: dirigidos y no-dirigidos.
* No considerar loops ni multi-arista. 


### Methods:
```cpp
bool insertVertex(string id, V data); // Creates a new vertex in the graph with some data and an ID

bool createEdge(string start, string end, E data); // Creates a new edge in the graph with some data

bool deleteVertex(string id); // Deletes a vertex in the graph

bool deleteEdge(string start, string end); // Deletes an edge in the graph, it is not possible to search by the edge value, since it can be repeated

E &operator()(string start, string end); // Gets the value of the edge from the start and end vertexes

float density() const; // Calculates the density of the graph

bool isDense(float threshold = 0.5) const; // Calculates the density of the graph, and determine if it is dense dependening on a threshold value

bool isConnected(); // Detect if the graph is connected

bool isStronglyConnected() throw(); // Detect if the graph is strongly connected (only for directed graphs)

bool empty(); // If the graph is empty

void clear(); // Clears the graph
```

### Algorithms:
```cpp
//Given the graph
UndirectedGraph<string, int> graph;

//1- Generates a MST graph using the Kruskal approach (only for undirected graphs)
Kruskal<string, int> kruskal(&graph);
UndirectedGraph<string, int> result = kruskal.get_grafo();//return a tree

//2- Generates a MST graph using the Prim approach (only for undirected graphs)
Prim<string, int> prim(&graph, "A");
UndirectedGraph<string, int> result = prim.get_grafo();//return a tree

//3- BFS 
BFS<string, int> BFS(&graph, vertex_id);
DirectedGraph<string, int> result = BFS.get_grafo();

//4- DFS 
DFS<string, int> DFS(&graph, vertex_id);
DirectedGraph<string, int> result = DFS.get_grafo();

//5- Dijkstra
Dijkstra<string, int> dijkstra(&graph, id);
DirectedGraph<string, int> result = dijkstra.get_grafo();

//6- Warshall
warshall<string, int> warshall(&graph);
DirectedGraph<string, int> result = warshall.get_grafo();

//7- Bellman
bellman<string, int> bellman(&graph, from);
DirectedGraph<string, int> result = bellman.get_grafo();

//8- Best First Search
BestBFS<string, int> bestbfs(&graph, "A", "Z", heuristics);
UndirectedGraph<string, int> result = bestbfs.get_grafo();

//9- A*
AStar<string, int> astar(&graph, inicio, fin, heuristics);
UndirectedGraph<string, int> result = astar.get_grafo();

```

Procederemos a explicar los algoritmos más complejos.

## Kruskal
El algoritmo de Kruskal, permite hallar el minimum spanning tree dado un grafo no dirigido, esto es hallar un arbol que mantenga la conectividad del grafo original con el menor costo de aristas, para esta implementación, se empleó disjoints sets, y se aplico las optimizaciones de Union by Rank y Path Compression, para alcanzar una complejidad final de O(eloge).Funciona de la siguiente manera, sorteamos las aristas por peso e iteramos desde la menor, realizando dos operaciones, si los dos nodos no estan conectados, se precede a agregar esa arista al grafo, caso contrario se continua.
```cpp
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
```

## Prim
De igual manera que el algoritmo anterior, se buscar encontrar el mst de un grafo no dirigido, este algoritmo empleando estructuras basadas en arboles binarios de busqueda (bst) logra una complejidad O(elogv).Funciona de la siguiente manera, se empieza de un nodo arbitrario, buscamos la menor arista, unimos esa arista al grafo y se procede a buscar la menor arista en el nuevo conjunto de nodos, asi hasta cubrir todo el grafo original.
```cpp
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
                //cout << v << " " << min_e[v].to << ' '<<vert[v]->data<<endl;
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
```

## BellmanFord

El presente algoritmo permite dado un nodo v encontrar la longitud de los caminos más cortos a todos los vértices del grafo, a diferencia de Djikstra este se puede aplicar a grafos con aristas negativas, funciona de la siguiente manera, se emplea un vector de distancias inicializado en infinito para todos los demás nodos a excepción del mismo, en cada iteracion se va actualizando este valor si se logra bajar el peso, la complejidad es O(ve).

```cpp
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

```
## Warshall

El algoritmo de Warshall, permite encontrar los caminos mínimos de todos los nodos hacia todos los nodos, en complejidad O(v^3), esto es posible mediante una matriz de distancias, la cual se va actualizando conforme cada iteracion basada en la siguiente operacion d[i][j]=min(d[i][j],d[i][k]+d[k][j]), eso es para un nodo arbitrario k, que sea un intermediario entre i-j.

```cpp
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

```

## Best BFS
Es el mismo procedimiento que la BFS regular, sin embargo, al momento de agregar un nodo a la cola, se ordena en base a una heurística, puede ser el peso de cada arista, o la distancia euclidiana entre muchas otras. La versión del algoritmo implementado es heurístico-dependiente, es decir que en caso la heurística no sea perfecta, no se podrá encontrar un camino, la complejidad es O(n+e).

```cpp
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
```


## JSON file parser
* Construye un grafo a partir de una archivo JSON de aereopuertos del mundo. 


### Methods:
```cpp
void clear(); // Clears parser saved atributes

void readJSON(); // Parses JSON file and saves data into class
// NOTE: each derived class has its own readJSON method

void uGraphMake(UndirectedGraph<string, double> &tempGraph); // Adds the parsed data into the specified undirected graph

void dGraphMake(DirectedGraph<string, double> &tempGraph); // Adds the parsed data into the specified directed graph
```

## [Git Karma Guidelines](http://karma-runner.github.io/5.2/dev/git-commit-msg.html)

```
<type>(<scope>): <subject>

<body>
```

### Allowed ```<type>``` values

* feat (new feature for the user, not a new feature for build script)
* fix (bug fix for the user, not a fix to a build script)
* docs (changes to the documentation)
* style (formatting, missing semi colons, etc)
* refactor (refactoring production code, eg. renaming a variable)
* test (adding missing tests, refactoring tests)
* chore (updating grunt tasks etc)

### Allowed ```<scope>``` values

* graph
* directedGraph
* undirectedGraph
* parser
* main
* tester


> **PD:** Puntos extras sobre Evaluación Continua si se implementa una GUI.
