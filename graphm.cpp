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

#include "graphm.h"

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
    while (input >> size) {
        for (int i = 0; i <= size; i++) {
            data[i].setData(input);
            // cout << data[i] <<endl;
        }

        int from, to, weight;
        input >> from >> to >> weight;
        while (from != 0) {
            C[from][to] = weight;
            // cout << from << " from, ";
            // cout << to << " to, ";
            // cout << weight << " weight" <<endl;

            input >> from >> to >> weight;
        }
    }
}

//---------------------------- insertEdge() -------------------------------------
// Insert an edge into graph between two given nodes
// Preconditions: None
// Postconditions: None
bool GraphM::insertEdge(int from, int to, int weight) {
    // Cases where the insert would be invalid
    if (from == to || weight < 0) { 
        // If destination is the same or negative weight
        return false;
    }

    if ((from > size || from < 1) || (to > size || to < 1)) {
        // If attempting to use out of bound nodes
        return false;
    }

    C[from][to] = weight;
    return true;
}

//---------------------------- removeEdge() -------------------------------------
// Remove an edge between two given nodes
// Preconditions: None
// Postconditions: None
bool GraphM::removeEdge(int from, int to) {
    if ((from > size || from < 1) || (to > size || to < 1)) {
        // If attempting to use out of bound nodes
        return false;
    }

    C[from][to] = INT_MAX;
    return true;
}

int main() {
    ifstream infile1("data31.txt");
    GraphM G;
    G.buildGraph(infile1);
    return 0;
}