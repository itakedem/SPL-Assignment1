#ifndef SESSION_H_
#define SESSION_H_
#include <fstream>
#include "../include/json.hpp"
#include <vector>
#include <string>
#include "../include/Graph.h"


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
    const Session& operator=(const Session& other);
    virtual ~Session();
    Session(Session&& session);
    Session& operator=(Session&& other);
    void simulate();
    void addAgent(const Agent& agent);
    void setGraph(const Graph& graph);
    void enqueueInfected(int);
    int dequeueInfected();
    TreeType getTreeType() const;
    const Graph& getGraph() const;
    Graph& changeGraph();
    int getCycle() const;
    void output();
    void TreeTypeJson(const string& type);
    void AgentsJson(const vector<tuple<string,int>>& agent);

private:
    Graph g;
    TreeType treeType;
    std::vector<Agent*> agents;
    int cycle;
    vector<int> infectedQueue;
    void clearAgents();


};

#endif