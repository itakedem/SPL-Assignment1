#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>

class Graph{
public:
    Graph(std::vector<std::vector<int>> matrix);

    Graph(Graph *pGraph);       //created by CLion
    std::vector<std::vector<int>>& getEdges();

    void infectNode(int nodeInd);
    bool isInfected(int nodeInd);
private:
    std::vector<std::vector<int>> edges;
    int nodesStat[];
};

#endif