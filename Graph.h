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
    bool isInfected(int nodeInd);
    void detach(int nodeInd);
    bool isSatisfied();
    const vector<int>& getNodeStat();

    void setNumActives(bool raise);

private:
    vector<vector<int>> edges;
    vector<int> nodesStat;          // if
    int numActives;                 //how many active viruses we have
};

#endif