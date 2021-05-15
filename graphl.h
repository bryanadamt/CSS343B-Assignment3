// ------------------------------------------------ graphl.h --------------------------------------------------------
// Bryan Adam Tjendra, CSS 343B
// Created: 9/5/2021
// Date of Last Modification:
// --------------------------------------------------------------------------------------------------------------------
// Purpose - This project is to display the graph information and implement depth-first (search always
//           starts at node #1).
// --------------------------------------------------------------------------------------------------------------------
// Assumption: input data is correctly formatted, valid data
// --------------------------------------------------------------------------------------------------------------------
#ifndef GRAPHL_H
#define GRAPHL_H

#include <iostream>
#include <fstream>
#include "nodedata.h"

using namespace std;

int const MAXNODES = 100;

class GraphL {
    public:
    // Constructor and Destructor
    GraphL();
    ~GraphL();

    // Builds up graph node information and adjacency list of edges between each
    // node reading from a data file.
    void buildGraph(ifstream&);

    // Displays each node information and edge in the graph
    void displayGraph() const;

    // Makes a depth-first search and displays each node in depth-first order
    void depthFirstSearch();

    private:
        int size;
        struct EdgeNode; // forward reference for the compiler

        struct GraphNode { // structs used for simplicity, use classes if desired
            EdgeNode* edgeHead; // head of the list of edges
            NodeData* data; // data information about each node
            bool visited;
        };

        GraphNode gNArray[MAXNODES];

        struct EdgeNode {
            int adjGraphNode; // subscript of the adjacent graph node
            EdgeNode* nextEdge;
        };

        // Helper functions
        void dfsHelper(int);
};

#endif