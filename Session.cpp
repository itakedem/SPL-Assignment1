#include "Session.h"
#include <iostream>
#include <fstream>
#include "json.hpp"
#include "Agent.h"

using namespace std;
using json = nlohmann::json;


Session::Session(const string& path):
        {
            ifstream i(*path);          //maybe need * maybe not
            g = new Graph(i["graph"]);
            cycle = 0;
            treetype = i["tree"];
            agents = new vector<Agent*>;
            future_agents = i["agents"];
        }

public:
    void addVectorAgents():     //creates the vector of agents in the session, based on the json config file
    {
        for (auto agent: this.future_agents):
        {
            if (agent[0] == "V")
                agents.pushback(new Virus(agent[1], this));
            else
                agents.pushback(new ContactTracer(this));
        }
    }
    void simulate():
    {

    }



