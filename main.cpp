#include <iostream>

#include "Graph/UndirectedGraph.h"
#include "Graph/DirectedGraph.h"
#include "Graph/Algorithms/dfs.h"
#include "Graph/Algorithms/bfs.h"
#include "Graph/Algorithms/kruskal.h"
#include "Graph/Algorithms/astar.h"
#include "Graph/Algorithms/dijkstra.h"
#include "Graph/Algorithms/bellman.h"
#include "Graph/Algorithms/warshall.h"
#include "Graph/Algorithms/bestbfs.h"

using namespace std;

auto GND = new UnDirectedGraph<string, int>;
auto GD = new DirectedGraph<string, int>;
bool tipo=0;

void Mostrar() {

        std::cout << "0. Elegir entre Grafo Dirigido y Grafo No Dirigido. (Obligatorio)" << endl;

        std::cout << "1. Insertar Vertice" << endl;

        std::cout << "2. Insertar Arista" << endl;

        std::cout << "3. Ejecutar BFS" << endl;

        std::cout << "4. Ejecutar DFS" << endl;

        std::cout << "5. Ejecutar Kruskal" << endl;

        std::cout << "6. Ejecutar Prim" << endl;

        std::cout << "7. Ejecutar Dijkstra" << endl;

        std::cout << "8. Ejecutar A*" << endl;

        std::cout << "9. Ejecutar Warshall" << endl;

        std::cout << "10. Ejecutar Bellman" << endl;

        std::cout << "11. Ejecutar Best BFS" << endl;

        std::cout << "12. Eliminar Arista" << endl;

        std::cout << "13. Eliminar Vértice" << endl;

        std::cout << "14. Salir" << endl;

        string c, c1;
        DirectedGraph<string, int>* Nuevo_GD;
        UnDirectedGraph<string, int>* Nuevo_GND;
        bfs<string,int> X;
        int opcion, i=0;
        std::cout
            << endl << "Ingrese el número correspondiente:  ";
        std::cin >> opcion;
        switch (opcion) {
            case 0:
                cout<<"Escribe 0 para utilizar un Grafo No Dirigido y 1 para un Grafo Dirigido"<<endl;
                int x;
                cin>>x;
                tipo=x;
                Mostrar();
                break;
            case 1:
                
                while(c1!="-1"){
                    cout<<"Escribe el string del vértice y el string de su contenido. Escribe un string cualquiera y -1 para salir."<<endl;
                    cin>>c>>c1;
                    if(c1!="-1"){
                if(tipo){
                    GD->insertVertex(c, c1);
                }
                else{
                    GND->insertVertex(c, c1);
                }
                }
                }
                Mostrar();
                break;
            case 2:
                while(i!=-1){
                    cout<<"Escribe el string del nodo de entrada, el string del nodo de salida y el int de la nueva arista. Escribe un string cualquiera, otro string cualquiera y -1 para salir."<<endl;
                    cin>>c>>c1>>i;
                    if(c1!="-1"){
                if(tipo){
                    GD->createEdge(c, c1, i);
                }
                else{
                    GND->createEdge(c, c1, i);
                }
                }
                }
                Mostrar();
                break;
            
            default:

                break;
        };
    
    if(opcion==3){
        cout<<"Escribe el string del nodo donde empezar el recorrido.";
                cin>>c;
                bfs<string,int> X(GND,c);
                if(tipo){
                    bfs<string,int> X(GD,c);
                }
                else{
                    bfs<string,int> X(GND,c);
                }
                Nuevo_GD=X.get_grafo();
                Nuevo_GD->display();
        Mostrar();
    }
    else if(opcion==4){
        cout<<"Escribe el string del nodo donde empezar el recorrido.";
                cin>>c;
                dfs<string,int> X(GND,c);
                if(tipo){
                    dfs<string,int> X(GD,c);

                }
                else{
                    dfs<string,int> X(GND,c);
                }
                Nuevo_GD=X.get_grafo();
                Nuevo_GD->display();
                Mostrar();
    }
    else if (opcion==5){
        if(tipo){
            cout<<"Los MST solo se pueden ejecutar para grafos no dirigidos.";
        }
        else{
            kruskal<string,int> X(GND);
            Nuevo_GD=X.get_grafo();
            Nuevo_GD->display();
        }
        Mostrar();
    }
     else if (opcion==6){
        if(tipo){
            cout<<"Los MST solo se pueden ejecutar para grafos no dirigidos.";
        }
        else{
            kruskal<string,int> X(GND);
            Nuevo_GD=X.get_grafo();
            Nuevo_GD->display();
        }
        Mostrar();
    }
     else if (opcion==7){
          cout<<"Escribe el string del nodo donde empezar el recorrido.";
                cin>>c;
        if(tipo){
            Dijkstra<string,int> X(GD,c);
            Nuevo_GD=X.get_grafo();
            Nuevo_GD->display();
        }
        else{
            Dijkstra<string,int> X(GND,c);
            Nuevo_GD=X.get_grafo();
            Nuevo_GD->display();
        }
        Mostrar();
    }
     else if (opcion==12){
        while(c!="-1"){
                    cout<<"Escribe el string de entrada y el string de salida del vértice a borrar. Escribe un string cualquiera y -1 para salir."<<endl;
                    cin>>c>>c1;
                    if(c1!="-1"){
                if(tipo){
                    GD->deleteEdge(c,c1);
                }
                else{
                    GND->deleteEdge(c,c1);
                }
                }

                }
        Mostrar();
    }
     else if (opcion==13){
        while(c!="-1"){
                    cout<<"Escribe el string del vértice a borrar. Escribe -1 para salir."<<endl;
                    cin>>c;
                    if(c1!="-1"){
                if(tipo){
                    GD->deleteVertex(c);
                }
                else{
                    GND->deleteVertex(c);
                }
                }
        }
                Mostrar();
    
    } //
     else if (opcion==8){
         // A*
         unordered_map<string,int> heuristica;

        if(tipo){
            while(heuristica.size()!=GD->get_vertexes()->size()){
                cout<<"Ingrese los IDs de los vértices junto con su valor en la heurística."<<endl;
                cin>>c>>i;
                heuristica[c]=i;
            }
            cout<<"Ingrese el ID del vértice de entrada y el ID del vértice de salida."<<endl;
            cin>>c>>c1;
            Astar<string,int> Y(GD, c, c1, heuristica);
            Y.display();
        }
        else{
            while(heuristica.size()!=GND->get_vertexes()->size()){
                cout<<"Ingrese los IDs de los vértices junto con su valor en la heurística."<<endl;
                cin>>c>>c1;
                cin>>c>>i;
                heuristica[c]=i;
            }
            cout<<"Ingrese el ID del vértice de entrada y el ID del vértice de salida."<<endl;
            cin>>c>>c1;
            Astar<string,int> Y(GND, c, c1, heuristica);
            Y.display();
        }
        Mostrar();
    }
    else if (opcion==9){
        if(tipo){
            warshall<string,int> X(GD);
            Nuevo_GD=X.get_grafo();
            Nuevo_GD->display();
        }
        else{
            warshall<string,int> X(GND);
            Nuevo_GD=X.get_grafo();
            Nuevo_GD->display();
        }
        Mostrar();
    }
    else if (opcion==10){
         cout<<"Escribe el string del nodo donde empezar el recorrido.";
                cin>>c;
        if(tipo){
            bellman<string,int> X(GD,c);
            Nuevo_GD=X.get_grafo();
            Nuevo_GD->display();
        }
        else{
            bellman<string,int> X(GND,c);
            Nuevo_GD=X.get_grafo();
            Nuevo_GD->display();
        }
        Mostrar();
    }
    else if (opcion==11){
        //Best BFS
         unordered_map<string,int> heuristica;

        if(tipo){
            while(heuristica.size()!=GD->get_vertexes()->size()){
                cout<<"Ingrese los IDs de los vértices junto con su valor en la heurística."<<endl;
                cin>>c>>i;
                heuristica[c]=i;
            }
            cout<<"Ingrese el ID del vértice de entrada y el ID del vértice de salida."<<endl;
            cin>>c>>c1;
            BestBFS<string,int> Y(GD, c, c1, heuristica);
            Nuevo_GND=Y.get_grafo();
            Nuevo_GND->display();
        }
        else{
            while(heuristica.size()!=GND->get_vertexes()->size()){
                cout<<"Ingrese los IDs de los vértices junto con su valor en la heurística."<<endl;
                cin>>c>>c1;
                cin>>c>>i;
                heuristica[c]=i;
            }
            cout<<"Ingrese el ID del vértice de entrada y el ID del vértice de salida."<<endl;
            cin>>c>>c1;
            BestBFS<string,int> Y(GND, c, c1, heuristica);
            Nuevo_GND=Y.get_grafo();
            Nuevo_GND->display();
        }
        Mostrar();
    }
    };


int main(int argc, char *argv[]) {
    std::cout << "================================================" << std::endl;
    std::cout << "MENU GRAPH TESTER" << std::endl;
    std::cout << "================================================" << std::endl;
  
    UnDirectedGraph<string, int> GND;
    GND.insertVertex("A", "5");
    GND.insertVertex("B", "50");
    GND.insertVertex("C", "1");
    GND.insertVertex("D", "0");
    GND.insertVertex("X", "0");
    GND.createEdge("A","B",6);
    GND.createEdge("B","C",6);
    GND.createEdge("C","A",2);
    GND.createEdge("D","B",20);
    GND.createEdge("C","D",3);
    GND.createEdge("B","D",11);
    GND.createEdge("A","X",11);

    //PRUEBA DE DIJKSTRA
    UnDirectedGraph<string,int> g2;
    g2.insertVertex("A","2");
    g2.insertVertex("B","2");
    g2.insertVertex("C","2");

    g2.createEdge("A","B",2);
    g2.createEdge("A","B",23);
    g2.createEdge("A","B",3);
    g2.createEdge("A","B",13);
    g2.createEdge("A","B",7);
    g2.createEdge("A","C",19);
    g2.createEdge("B","C",4);

/*
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

    cout<<"A*: "<<endl;
    unordered_map<string,int> heuristica;

    heuristica["A"] = 15;
    heuristica["B"] = 18;
    heuristica["C"] = 7;
    heuristica["D"] = 23;

    Astar<char,int> Y(&GND, "A", "D", heuristica);
    Y.display();
   

    cout<<"Dijkstra: "<<endl;
    Dijkstra<char,int> Z(&GND,"A");
    auto grafito = Z.get_grafo();
    grafito->display();
    

    unordered_map<string,int> heuristica;
    heuristica["A"] = 15;
    heuristica["B"] = 18;
    heuristica["C"] = 7;
    heuristica["D"] = 0;

    BestBFS<string,int> Y(&GND, "A", "D", heuristica);
            auto Nuevo_GND=Y.get_grafo();
            Nuevo_GND->display();
             */
    Mostrar();
    return EXIT_SUCCESS;
}