// ------------------------------------------------ GraphM.h --------------------------------------------------------
// Bryan Adam Tjendra, CSS 343B
// Created: 9/5/2021
// Date of Last Modification:
// --------------------------------------------------------------------------------------------------------------------
// Purpose - This project is to implement Dijkstra's shortest path algorithm.
// --------------------------------------------------------------------------------------------------------------------
// Notes on specifications, special algorithms, and assumptions.
// --------------------------------------------------------------------------------------------------------------------

#ifndef GRAPHM_H
#define GRAPHM_H

#include <iostream>
#include "nodedata.h"

using namespace std;

class GraphM {
public:
    GraphM(); // default constructor

    buildGraph(); // builds up graph node information and adjacency matrix of edges between each
                  // node reading from a data file.
    insertEdge(int, int, int); // insert an edge into graph between 2 given nodes
    removeEdge(int, int); // remove edge between 2 given nodes


private:
    struct TableType {
        bool visited; // whether node has been visited
        int dist; // shortest distance from source known so far
        int path; // previous node in path of min dist
    };

    NodeData data[MAXNODES]; // data for graph nodes
    int C[MAXNODES][MAXNODES]; // Cost array, the adjacency matrix
    int size; // number of nodes in the graph
    TableType T[MAXNODES][MAXNODES]; // stores visited, distance, path
};

#endif