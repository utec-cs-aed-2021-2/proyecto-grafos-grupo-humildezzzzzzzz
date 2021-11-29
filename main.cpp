#include <iostream>

#include "Graph/UndirectedGraph.h"
#include "Graph/DirectedGraph.h"
#include "Graph/Algorithms/dfs.h"
#include "Graph/Algorithms/bfs.h"
#include "Graph/Algorithms/kruskal.h"

using namespace std;

void Mostrar() {
        std::cout << "1. Insertar Vertice" << endl;

        std::cout << "2. Insertar Arista" << endl;

        std::cout << "3. Ejecutar BFS" << endl;

        std::cout << "4. Ejecutar DFS" << endl;

        std::cout << "5. Ejecutar Kruskal" << endl;

        std::cout << "6. Ejecutar Prim" << endl;

        std::cout << "7. Ejecutar Dijkstra" << endl;

        std::cout << "7. Ejecutar A*" << endl;

        std::cout << "8. Salir" << endl;

        int opcion;
        std::cout
            << endl << "Ingrese el número correspondiente:  ";
        std::cin >> opcion;
        switch (opcion) {
            case 1:
                break;
            case 2:
                
                break;
            case 3:
                
                break;
            case 4:
                
                break;
            case 6:
                
                break;
            default:
               
                break;
        };
    };


int main(int argc, char *argv[]) {
    std::cout << "================================================" << std::endl;
    std::cout << "MENU GRAPH TESTER" << std::endl;
    std::cout << "================================================" << std::endl;
/*  
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
    */

    Mostrar();
    return EXIT_SUCCESS;
}