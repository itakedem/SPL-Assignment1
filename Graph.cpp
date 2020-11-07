#include "Graph.h"
#include <utility>
using namespace std;



Graph::Graph(vector<vector<int>> matrix): edges(move(matrix))
{
    for (int i = 0; i<matrix.size(); i++)
        nodesStat.push_back(0); //all nodes are healthy at initiate
} //need to delete edges???


Graph::Graph(Graph *pGraph)
{
    edges = (*pGraph).edges, nodesStat = (*pGraph).nodesStat;
}

Graph::Graph() = default;






void Graph::infectNode(int nodeInd)
{
    nodesStat[nodeInd] = 1;
                                    //need to add to infectedQueue
}

bool Graph::isInfected(int nodeInd)
{
    return nodesStat[nodeInd] == 1;
}

const vector<vector<int>>& Graph::getEdges()
{
    return edges;
}







