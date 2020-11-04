#include "Graph.h"

#include <utility>

void Graph::infectNode(int nodeInd) {

}

bool Graph::isInfected(int nodeInd) {
    return false;
}

Graph::Graph(Graph *pGraph) {

}

Graph::Graph(std::vector<std::vector<int>> matrix): edges(std::move(matrix)){}

