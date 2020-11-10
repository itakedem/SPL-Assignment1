#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
using namespace std;

class Graph{
public:
    Graph(vector<vector<int>> matrix);
    Graph();
    Graph(Graph *pGraph);       //created by CLion
    const vector<vector<int>>& getEdges() const;
    int amountNeighbors(int nodeInd) const;
    void infectNode(int nodeInd);
    void CoVIDNode(int nodeInd);
    bool isInfected(int nodeInd);
    bool isCoVIDed(int nodeInd);
    void detach(int nodeInd);
    bool isSatisfied();                     //if no active viruses
    const vector<int>& getNodeStat();
    const vector<int>& getIllNodes();

    void setNumActives(bool raise);

private:
    vector<vector<int>> edges;
    vector<int> nodesStat;          //nodestat[i] == 0 means node i is healthy, == 1 means node i is infected, 2 is covided
    vector<int> illNodes;
    int numActives;                 //how many active viruses we have
};

#endif