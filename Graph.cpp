#include "Graph.h"
#include <utility>
using namespace std;



Graph::Graph(std::vector<std::vector<int>> matrix): edges(std::move(matrix)){} //need to delete edges???
Graph::Graph(Graph *pGraph) { edges = (*pGraph).edges;
}


void Graph::infectNode(int nodeInd) {

}

bool Graph::isInfected(int nodeInd) {
    return false;
}

vector<vector<int>>& Graph::getEdges() {
    return edges;
}





