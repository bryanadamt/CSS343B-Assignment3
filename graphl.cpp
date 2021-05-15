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
    string address; // = ""?
    input >> size; // if size = 0?
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
void GraphL::displayGraph() {
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


int main() {
    ifstream infile2("data32.txt");
    //for each graph, find the depth-first search ordering
	for (;;) {
		GraphL G;
		G.buildGraph(infile2);
	    if (infile2.eof())
		break;
		G.displayGraph();
		// G.depthFirstSearch();    // find and display depth-first ordering to cout
	}
    return 0;
}