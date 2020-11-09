#ifndef SESSION_H_
#define SESSION_H_
#include <fstream>
#include "json.hpp"
#include <vector>
#include <string>
#include "Graph.h"

using json = nlohmann::json;
using namespace std;

class Agent;

enum TreeType{
    Cycle,
    MaxRank,
    Root
};

class Session{
public:
    Session(const string& path);
    Session(const Session& other);
    void simulate();
    void addAgent(const Agent& agent);
    void setGraph(const Graph& graph);
    void enqueueInfected(int);
    int dequeueInfected();
    TreeType getTreeType() const;
    Graph& getGraph() const;
    int getCycle() const;

private:
    Graph g;
    TreeType treeType;
    std::vector<Agent*> agents;
    int cycle;
    vector<int> infectedQueue;

};

#endif