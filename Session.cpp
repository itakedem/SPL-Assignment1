#include "Session.h"
#include <iostream>
#include <fstream>
#include "json.hpp"
#include "Agent.h"

using namespace std;
using json = nlohmann::json;


Session::Session(const string& path):
        {
            ifstream i(path);          //maybe need * maybe not
            json j;
            j << i;
            g = new Graph(j["graph"]);
            cycle = 0;
            treetype = j["tree"];
            agents = new vector<Agent*>;
        }

void Session::simulate() {

}

void Session::addAgent(const Agent &agent) {

}

void Session::setGraph(const Graph &graph) {

}

void Session::enqueueInfected(int) {

}

int Session::dequeueInfected() {
    return 0;
}

TreeType Session::getTreeType() const {
    return Root;
}

public:
    void addVectorAgents():     //creates the vector of agents in the session, based on the json config file
    {
        for (auto agent: this.future_agents):
        {
            if (agent[0] == "V")
                agents.push_back(new Virus(agent[1], this));
            else
                agents.push_back(new ContactTracer(this));
        }
    }
    void simulate():
    {

    }



