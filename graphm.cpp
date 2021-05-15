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
#include <algorithm>

using namespace std;

//---------------------------- GraphM() -------------------------------------
// Default Constructor
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
void GraphM::buildGraph(ifstream& input) {
    while (input >> size) {
        for (int i = 0; i <= size; i++) {
            data[i].setData(input);
        }

        int from, to, weight;
        input >> from >> to >> weight;
        while (from != 0) {
            C[from][to] = weight;
            input >> from >> to >> weight;
        }
    }
}

//---------------------------- insertEdge() -------------------------------------
// Insert an edge into graph between two given nodes
bool GraphM::insertEdge(int from, int to, int weight) {
    // If attempt to insert an edge to self or negative weight
    if (from == to || weight < 0) {
        return false;
    }

    // If attempting to use out of bound nodes
    if (from < 1 || to < 1 || from > size || to > size) {
        return false;
    }

    C[from][to] = weight;
    findShortestPath();
    return true;
}

//---------------------------- removeEdge() -------------------------------------
// Remove an edge between two given nodes
bool GraphM::removeEdge(int from, int to) {
    // If there is no edge to remove
    if (C[from][to] == INT_MAX) {
        return false;
    }

    // If attempting to use out of bound nodes
    if (from < 1 || to < 1 || from > size || to > size) {
        return false;
    }

    C[from][to] = INT_MAX;
    findShortestPath();
    return true;
}

//---------------------------- findShortestPath() -------------------------------------
// The shortest path between every node to every other node
// Following the pseudocode given in the assignment file
void GraphM::findShortestPath() {
    for (int source = 1; source <= size; source++) {
        T[source][source].dist = 0;
        T[source][source].visited = true;
        int v = 0;

        for (int i = 1; i <= size; i++) {
            if (C[source][i] != INT_MAX) {
                T[source][i].dist = C[source][i];
                T[source][i].path = source;
            }
        }

        do {
            v = 0; // reset

            for (int i = 1; i <= size; i++) {
                if (!T[source][i].visited && (C[source][i] < C[source][v])) {
                    v = i;
                }
            }

            if (v != 0) {
                T[source][v].visited = true;

                for (int w = 1; w <= size; w++) {
                    if (!T[source][w].visited && C[v][w] != INT_MAX && v != w) {
                        if (T[source][w].dist > T[source][v].dist + C[v][w]) {
                            T[source][w].dist = T[source][v].dist + C[v][w];
                            T[source][w].path = v;
                        }
                    }
                }
            }
        } while (v != 0);
    }

    for (int i = 0; i <= size; i++) {
        for( int j = 0; j <= size; j++) {
            if (T[i][j].visited) {
                cout<< setw(2) << T[i][j].dist << setw(2) << T[i][j].path << " |";
            } else if (i == 0 || j == 0) {
                cout << setw(5) << max(i,j) << " |";
            } else {
                if (T[i][j].dist != INT_MAX) {
                    cout << setw(2) << T[i][j].dist << setw(3) << T[i][j].path << "nv|";
                }
                else { cout << setw(7) <<  "--- |"; }
            }
        }
        cout << endl;
    }
}

//---------------------------- displayAll() -------------------------------------
// displays the distance and paths between All nodes
void GraphM::displayAll() const { 
    cout << "Description         From node   To node   Dijkstra's     Path" << endl;
    for (int i = 1; i <= size; i++) {
        cout << data[i] << endl;
        for (int j = 1; j <= size; j++) {
            if (i == j) { // Don't print out path to self
                continue;
            }
            cout << "                        ";
            cout << i << "           " << j << "         ";

            if (T[i][j].dist != INT_MAX) {
                cout << T[i][j].dist << "           ";
                displayPathHelper(i, j);
            } else {
                cout << "----";
            }

            cout << endl;
        }
    }
}

//---------------------------- display() -------------------------------------
// displays the distance and paths between a node to another node
void GraphM::display(int from, int to) const {
    cout << "  " << from << "         " << to;
    cout << "        " << T[from][to].dist;
    cout << "            ";
    displayPathHelper(from, to);
    cout << endl;
    displayAddressHelper(from, to);
} 

//---------------------------- displayPathHelper() -------------------------------------
// Recursively prints the path from one node to another
void GraphM::displayPathHelper(int from, int to) const {
    if (T[from][to].dist != INT_MAX) {
        displayPathHelper(from, T[from][to].path);
        cout << to << " ";
    }
}

//---------------------------- displayAddressHelper() -------------------------------------
// Recursively prints the address from one node to another
void GraphM::displayAddressHelper(int from, int to) const {
    if (T[from][to].dist != INT_MAX) {
        displayAddressHelper(from, T[from][to].path);
        cout << data[to] << endl;
    }
}

int main() {
    ifstream infile1("testdata.txt");
    GraphM G;
    G.buildGraph(infile1);
    G.findShortestPath();
    G.displayAll();
    G.display(1,4);
    return 0;
}