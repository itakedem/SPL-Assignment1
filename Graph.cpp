#include "Graph.h"
#include <utility>
using namespace std;



Graph::Graph(std::vector<std::vector<int>> matrix): edges(move(matrix))
{
  /*  nodesStat[matrix.size()];
    for (int i = 0; i<matrix.size(); i++)
        nodesStat[i] = 0;*/
} //need to delete edges???
Graph::Graph(Graph *pGraph) { edges = (*pGraph).edges;
}

Graph::Graph() = default;

void Graph::infectNode(int nodeInd)
{
   // nodesStat[nodeInd] = 1;
                                    //need to add to infectedQueue
}

bool Graph::isInfected(int nodeInd)
{
    true;
    //return nodesStat[nodeInd] == 1;
}

vector<vector<int>>& Graph::getEdges()
{
    return edges;
}







