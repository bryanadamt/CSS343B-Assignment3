// ------------------------------------------------ GraphM.cpp --------------------------------------------------------
// Bryan Adam Tjendra, CSS 343B
// Created: 9/5/2021
// Date of Last Modification:
// --------------------------------------------------------------------------------------------------------------------
// Purpose - This project is to implement Dijkstra's shortest path algorithm.
// --------------------------------------------------------------------------------------------------------------------
// Assumption: the input data file has correctly formatted, valid data.
//             max nodes = 100 / graph
// --------------------------------------------------------------------------------------------------------------------

#include "GraphM.h"

#include <iostream>
#include <climits>
#include <iomanip>
#include <fstream>

using namespace std;

//---------------------------- GraphM() -------------------------------------
// Default Constructor
// Preconditions: None
// Postconditions: None
GraphM::GraphM() : size(0){
    for (int i = 0; i < MAXNODES; i++) {
        for (int j = 0; j < MAXNODES; j++) {
            C[i][j] = INT_MAX;
            T[i][j].visited = false;
            T[i][j].dist = INT_MAX;
            T[i][j].path = 0;
        }
    }
}

//---------------------------- buildGraph() -------------------------------------
// Builds up graph node information and adjacency matrix of edges 
// between each node reading from a data file.
// Preconditions: None
// Postconditions: None
void GraphM::buildGraph(ifstream& input) {
    input >> size;
    for (int i = 0; i < size; i++) {
        string name;
        input >> name;
        NodeData tempND = new NodeData(name);
        data[i] = tempND;
    }

    string line;
}

int main() {
    return 0;
}