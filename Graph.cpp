#include "Graph.h"
#include <utility>
using namespace std;




Graph::Graph(vector<vector<int>> matrix): edges(move(matrix))
{
    for (int i = 0; i<edges.size(); i++)
        nodesStat.push_back(0); //all nodes are healthy at initiate
}


Graph::Graph() = default;

Graph::Graph(Graph *pGraph): edges(pGraph->edges), nodesStat(pGraph->nodesStat), illNodes(pGraph->illNodes), numActives(pGraph->numActives){}




const vector<vector<int>> &Graph::getEdges() const
{
    return edges;
}

int Graph::amountNeighbors(int nodeInd) const
{
    int amount = 0;
    for(int i = 0; i<edges.size(); i++)
    {
        if(edges[nodeInd][i]==0)
            amount +=1;
    }

    return amount;
}


void Graph::infectNode(int nodeInd)
{
    nodesStat[nodeInd] = 1;
    illNodes.push_back(nodeInd);
}

void Graph::CoVIDNode(int nodeInd)
{
    nodesStat[nodeInd] = 2;
}

bool Graph::isInfected(int nodeInd){return nodesStat[nodeInd] == 1;}

bool Graph::isCoVIDed(int nodeInd) {return nodesStat[nodeInd] == 2;}

void Graph::detach(int nodeInd) {
    for(int i = 0; i<edges.size(); i++)
    {
        edges[i][nodeInd] = 0;
        edges[nodeInd][i] = 0;
    }
}

bool Graph::isSatisfied() {return numActives == 0;}

const vector<int> &Graph::getNodeStat() {return nodesStat;}

const vector<int> &Graph::getIllNodes() {return illNodes;}

void Graph::setNumActives(bool raise)
{
    if (raise)
        numActives++;
    else
        numActives--;
}










