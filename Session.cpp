#include "Session.h"
#include <iostream>
#include <fstream>
#include "json.hpp"
#include "Agent.h"

using namespace std;
using json = nlohmann::json;


Session::Session(const string& path): g()
{
    ifstream i(path);          //maybe need * maybe not
    json j;
    j << i;
    g = Graph(j["graph"]);
    cycle = 0;
    TreeTypeJson(j["tree"]);
    AgentsJson(j["agents"]);
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


Session::~Session(){clearAgents();}

Session::Session(Session &&session): g(session.g), treeType(session.treeType), agents(session.agents), cycle(session.cycle), infectedQueue(session.infectedQueue)
{
    for(Agent* agent:session.agents)
        agent = nullptr;
}

Session &Session::operator=(Session &&other){
    if(this!= &other)
    {
        g = other.g;
        treeType = other.treeType;
        clearAgents();
        for(Agent* agent: other.agents)
            agents.push_back(agent);
        cycle = other.cycle;
        infectedQueue.clear();
        infectedQueue = other.infectedQueue;
        for(Agent* agent:other.agents)
            agent = nullptr;
    }
    return *this;
}





void Session::clearAgents()
{
    for(Agent* agent: agents)
    {
        if(agent!= nullptr)
        {
            delete agent;
            agent = nullptr;
        }
    }
}



void Session::simulate()
{
    while(!g.isSatisfied())
    {
        int agentSize = agents.size();
        for(int i = 0; i< agentSize; i++)
            agents[i]->act(*this);
        cycle++;
    }
    output();
}

void Session::addAgent(const Agent &agent)
{
    Agent* clone = agent.clone();
    agents.push_back(clone);
}

void Session::setGraph(const Graph &graph)
{
    g = graph;
}

void Session::enqueueInfected(int nodeInd) {
    infectedQueue.push_back(nodeInd);
}

int Session::dequeueInfected()
{
    if(!infectedQueue.empty())
    {
        int infect = infectedQueue[0];
        infectedQueue.erase(infectedQueue.begin());
        return infect;
    }
    return -1;
}

TreeType Session::getTreeType() const {
    return treeType;
}

const Graph& Session::getGraph() const
{
    return g;
}
Graph& Session::changeGraph() {return g;}

int Session::getCycle() const {
    return cycle;
}

void Session::output()
{
    json j;
    j["infected"] = g.getIllNodes();
    j["graph"] = g.getEdges();
    ofstream i("output.json");
    j >> i;
}


void Session::TreeTypeJson(const string& type){

    if(type == "M")
        treeType = MaxRank;
    else if(type == "R")
        treeType = Root;
    else
        treeType = Cycle;
}

void Session::AgentsJson(const vector<tuple<string, int>>& agent) {
    for (auto a: agent) //creates the vector of agents in the session, based on the json config file
    {
        if (get<0>(a) == "V")
        {
            agents.push_back(new Virus(get<1>(a)));
            g.setNumActives(true);
        }
        else
            agents.push_back(new ContactTracer());
    }
}















