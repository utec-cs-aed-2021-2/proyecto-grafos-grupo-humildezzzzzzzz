[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-f059dc9a6f8d3a56e377f745f24479a46679e63a5d9fe6f495e02850cd0d8118.svg)](https://classroom.github.com/online_ide?assignment_repo_id=6129282&assignment_repo_type=AssignmentRepo)
# Algoritmos y Estructura de Datos
## Proyecto sobre Grafos
--------

## Integrantes
- Juan Sebastian Sara Junco
- Denis Irala Morales
- Plinio Matias Avendaño Vargas

----

El proyecto del curso consiste en implementar una estructura de datos de grafo y un file parser. La estructura debe soportar los métodos y algoritmos descritos a continuacion:  


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
