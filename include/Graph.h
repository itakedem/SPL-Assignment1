#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
using namespace std;

class Graph{
public:
    Graph(vector<vector<int>> matrix);
    Graph();
    Graph(Graph *pGraph);                           //copy constructor
    const vector<vector<int>>& getEdges() const;
    void infectNode(int nodeInd);           //makes node infected
    void CoVIDNode(int nodeInd);            //makes node carrier
    bool isInfected(int nodeInd);
    bool isCoVIDed(int nodeInd);
    void detach(int nodeInd);               //removes all edges from specific node
    bool isSatisfied();                     //if no active viruses
    const vector<int>& getIllNodes();       //return all the infected nodes
    void setNumActives(bool raise);         //adjusts number of active viruses

private:
    vector<vector<int>> edges;
    vector<int> nodesStat;          //nodestat[i] == 0 means node i is healthy, == 1 means node i is infected, 2 is covided
    vector<int> illNodes;
    int numActives;                 //how many active viruses we have
};

#endif