#include <iostream>

#include "Graph/UndirectedGraph.h"
#include "Graph/DirectedGraph.h"
#include "Graph/Algorithms/dfs.h"
#include "Graph/Algorithms/bfs.h"
#include "Graph/Algorithms/kruskal.h"

using namespace std;

int main(int argc, char *argv[]) {
    std::cout << "================================================" << std::endl;
    std::cout << "MENU GRAPH TESTER" << std::endl;
    std::cout << "================================================" << std::endl;

    UnDirectedGraph<char, int> GND;
    GND.insertVertex("A", 5);
    GND.insertVertex("B", 50);
    GND.insertVertex("C", 1);
    GND.insertVertex("D", 0);
    GND.createEdge("A","B",6);
    GND.createEdge("B","C",6);
    GND.createEdge("C","A",2);
    GND.createEdge("D","B",20);

    cout<<"Kruskal:"<<endl;
    kruskal<char,int> Z(&GND);
    auto nuevo_grafo2=Z.get_grafo();
    nuevo_grafo2->display();

    cout<<"DFS:"<<endl;
    dfs<char,int> X(&GND,"A");
    auto nuevo_grafo=X.get_grafo();
    nuevo_grafo->display();

    cout<<"BFS:"<<endl;
    bfs<char,int> Y(&GND, "A");
    auto new_graph = Y.get_grafo();
    new_graph->display();
    return EXIT_SUCCESS;
}