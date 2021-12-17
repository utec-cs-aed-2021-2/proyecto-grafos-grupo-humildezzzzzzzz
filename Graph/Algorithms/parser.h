#include <queue>
#include <set>
#include<fstream>
#include "json.hpp"
#include "../DirectedGraph.h"
#include "../UndirectedGraph.h"
using json = nlohmann::json;

template<typename TV,typename TE>
class parser{
private:
    json j;
public:
    parser() = default;

    void clear(){

    }; // Clears parser saved atributes

    void readJSON(string direccion){

    }; // Parses JSON file and saves data into class
// NOTE: each derived class has its own readJSON method

    void uGraphMake(UnDirectedGraph<string, double> &tempGraph){

    }; // Adds the parsed data into the specified undirected graph

    void dGraphMake(DirectedGraph<string, double> &tempGraph){

    }; // Adds the parsed data into the specified directed graph

};
