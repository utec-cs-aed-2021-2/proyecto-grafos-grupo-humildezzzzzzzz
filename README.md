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
El algoritmo de Kruskal, permite hallar el minimum spanning tree dado un grafo no dirigido, esto es hallar un arbol que mantenga la conectividad del grafo original con el menor costo de aristas, para esta implementación, se empleó disjoints sets, y se aplico las optimizaciones de Union by Rank y Path Compression, para alcanzar una complejidad final de O(eloge).
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
##Prim


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
