// ------------------------------------------------ graphl.cpp --------------------------------------------------------
// Bryan Adam Tjendra, CSS 343B
// Created: 9/5/2021
// Date of Last Modification:
// --------------------------------------------------------------------------------------------------------------------
// Purpose - This project is to display the graph information and implement depth-first (search always
//           starts at node #1).
// --------------------------------------------------------------------------------------------------------------------
// Assumption: input data is correctly formatted, valid data
// --------------------------------------------------------------------------------------------------------------------

#include "graphl.h"

#include <iomanip>

//---------------------------- GraphL() -------------------------------------
// Default Constructor
GraphL::GraphL() : size(0) {
    for (int i = 1; i < MAXNODES; i++) {
        gNArray[i].edgeHead = NULL;
        gNArray[i].data = NULL;
        gNArray[i].visited = false;
    }
}

//---------------------------- ~GraphL() -------------------------------------
// Destructor
GraphL::~GraphL() {
    //ok
}

//---------------------------- buildGraph() -------------------------------------
// Builds up graph node information and adjacency list of edges between each
// node reading from a data file.
void GraphL::buildGraph(ifstream& input) {
    string address;
    input >> size;
    getline(input, address); // Throwaway line

    for (int i = 1; i <= size; i++) {
        getline(input, address);

        NodeData* newND = new NodeData(address);
        gNArray[i].data = newND;

        EdgeNode* newEN = new EdgeNode();
        gNArray[i].edgeHead = newEN;
        gNArray[i].edgeHead->adjGraphNode = 0;
        gNArray[i].edgeHead->nextEdge = NULL;
    }

    int from, to;
    while (input >> from >> to) {
        if (from != 0) {
            EdgeNode* newEdge = new EdgeNode();
            newEdge->adjGraphNode = 0;
            newEdge->nextEdge = NULL;

            // O(1) insertion
            if (gNArray[from].edgeHead->nextEdge != NULL) {
                newEdge->adjGraphNode = gNArray[from].edgeHead->adjGraphNode;
                newEdge->nextEdge = gNArray[from].edgeHead->nextEdge;
            }
            gNArray[from].edgeHead->adjGraphNode = to;
            gNArray[from].edgeHead->nextEdge = newEdge;
        } else {
            break;
        }
    }
}

//---------------------------- displayGraph() -------------------------------------
// Displays each node information and edge in the graph
void GraphL::displayGraph() const {
    cout << "Graph:" << endl;
    for (int i = 1; i <= size; i++) {
        cout << "Node" << i << "         " << *gNArray[i].data << endl;
        cout << endl;

        EdgeNode* traverse = gNArray[i].edgeHead;
        while (traverse != NULL) {
            if (traverse->adjGraphNode != 0 ) {
                cout << "  edge  " << i << "  " << traverse->adjGraphNode << endl;
            }
            traverse = traverse->nextEdge;
        }
        cout << endl;
    }
} 

//---------------------------- depthFirstSearch() -------------------------------------
// Makes a depth-first search and displays each node in depth-first order
void GraphL::depthFirstSearch() {
    cout << "Depth-first ordering:  ";
    for (int i = 1; i <= size; i++) {
        if (!gNArray[i].visited) {
            dfsHelper(i);
            cout << endl;
            cout << "                       ";
        }
    }
    cout << endl;
}

//---------------------------- dfsHelper() -------------------------------------
// Recursively do dfs
void GraphL::dfsHelper(int source) {
    if (source == 0) {
        return;
    }
    gNArray[source].visited = true;
    cout << source << " ";

    EdgeNode* traverse = gNArray[source].edgeHead;
    while (traverse != NULL) {
        if (!gNArray[traverse->adjGraphNode].visited) {
            dfsHelper(traverse->adjGraphNode);
        }
        traverse = traverse->nextEdge;
    }
}