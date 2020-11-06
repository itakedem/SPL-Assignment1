#include "Session.h"
#include <iostream>
#include <fstream>
#include "json.hpp"
#include "Agent.h"

using namespace std;
using json = nlohmann::json;


Session::Session(const string& path): g(nullptr)                    //why must add null g???
        {
            ifstream i(path);          //maybe need * maybe not
            json j;
            j << i;
            g = new Graph(j["graph"]);
            cycle = 0;
            treeType = j["tree"];
            j_agents = j["agents"];
        }

void Session::simulate()
{
    sourceAgents();

}

void Session::addAgent(const Agent &agent)
{
    Agent* newA = new Agent(agent);
    agents.push_back(newA);
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


    void Session::sourceAgents()     //creates the vector of agents in the session, based on the json config file
    {
        for (auto agent: j_agents)
        {
            if (agent[0] == "V")
                agents.push_back(new Virus(agent[1]));
            else
                agents.push_back(new ContactTracer());
        }
    }



