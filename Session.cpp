#include "Session.h"
#include <iostream>
#include <fstream>
#include "json.hpp"
#include "Agent.h"

using namespace std;
using json = nlohmann::json;


Session::Session(const string& path):g()
{
    ifstream i(path);          //maybe need * maybe not
    json j;
    j << i;
    g = Graph(j["graph"]);
    cycle = 0;
    treeType = j["tree"];
    for (auto agent: j["agents"]) //creates the vector of agents in the session, based on the json config file
    {
        if (agent[0] == "V")
            agents.push_back(new Virus(agent[1]));
        else
            agents.push_back(new ContactTracer());
    }
}

Session::Session(const Session &other): g(other.g), treeType(other.getTreeType()), cycle(other.cycle)
{
    for(int i=0;i<other.agents.size();i++)
    {
        Agent* newAgent = other.agents[i]->clone();
        agents.push_back(newAgent);
    }
    infectedQueue = other.infectedQueue;
}

const Session &Session::operator=(const Session &other){
    if(this!=&other){
        g = other.g;
        treeType = other.treeType;
        clearAgents();
        for(Agent* agent: other.agents)
            agents.push_back(agent->clone());
        cycle = other.cycle;
        infectedQueue.clear();
        infectedQueue = other.infectedQueue;
    }
    return *this;
}
void Session::clearAgents()
{
    for(Agent* agent: agents)
    {
        if(agent)
        delete agent;
    }
}



void Session::simulate()
{

    //don't forget to update cycle field after each cycle

}

void Session::addAgent(const Agent &agent)
{
    Agent* clone = agent.clone();
    agents.push_back(clone);
}

void Session::setGraph(const Graph &graph) {

}

void Session::enqueueInfected(int) {

}

int Session::dequeueInfected() {
    return 0;
}

TreeType Session::getTreeType() const {
    return treeType;
}

Graph& Session::getGraph()
{
    return g;           //needs to send reference!!!!!
}

int Session::getCycle() const {
    return cycle;
}










