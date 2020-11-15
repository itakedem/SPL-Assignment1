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
    const Session& operator=(const Session& other); //assignment operator
    virtual ~Session();                      //destructor
    Session(Session&& session);             //move constructor
    Session& operator=(Session&& other);    //move assignment operator
    void simulate();
    void addAgent(const Agent& agent);
    void setGraph(const Graph& graph);
    void enqueueInfected(int);
    int dequeueInfected();
    TreeType getTreeType() const;
    const Graph& getGraph() const;
    Graph& changeGraph();           //returns the graph with the ability to change the graph
    int getCycle() const;
    void output();                  //creates the output file
    void TreeTypeJson(const string& type);      //initiates the treeType from json
    void AgentsJson(const vector<tuple<string,int>>& agent);    //initiates the agents from json

private:
    Graph g;
    TreeType treeType;
    std::vector<Agent*> agents;
    int cycle;
    vector<int> infectedQueue;
    void clearAgents();


};

#endif