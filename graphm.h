// ------------------------------------------------ GraphM.h --------------------------------------------------------
// Bryan Adam Tjendra, CSS 343B
// Created: 9/5/2021
// Date of Last Modification:
// --------------------------------------------------------------------------------------------------------------------
// Purpose - This project is to implement Dijkstra's shortest path algorithm.
// --------------------------------------------------------------------------------------------------------------------
// Assumption: the input data file has correctly formatted, valid data.
//             max nodes = 100 / graph
// --------------------------------------------------------------------------------------------------------------------

#ifndef GRAPHM_H
#define GRAPHM_H

#include <iostream>
#include <fstream>
#include "nodedata.h"

using namespace std;

int const MAXNODES = 100;

class GraphM {
public:
    // default constructor
    GraphM(); 

    // builds up graph node information and adjacency matrix of edges between each node reading from a data file.
    void buildGraph(ifstream&); 

    // insert an edge into graph between 2 given nodes
    bool insertEdge(int, int, int);

    // remove edge between 2 given nodes
    bool removeEdge(int, int); 

    // find the shortest path between every node to every other node
    void findShortestPath();

    // displays the distance and paths between nodes
    void displayAll() const; 
    void display(int, int) const;

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

    // Helper for display
    void displayHelper(int, int) const;
};

#endif