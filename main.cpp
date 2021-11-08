#include <iostream>

#include "Graph/UndirectedGraph.h"

using namespace std;

int main(int argc, char *argv[]) {
    std::cout << "================================================" << std::endl;
    std::cout << "MENU GRAPH TESTER" << std::endl;
    std::cout << "================================================" << std::endl;
    UnDirectedGraph<int, int> GND;
    GND.insertVertex("A", 5);
    GND.insertVertex("B", 50);
    GND.insertVertex("C", 1);
    GND.insertVertex("D", 0);
    GND.createEdge("A","B",6);
    GND.createEdge("B","C",6);
    GND.createEdge("C","A",2);
    return EXIT_SUCCESS;
}