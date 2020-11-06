#ifndef AGENT_H_
#define AGENT_H_

#include <vector>
#include "Session.h"

class Agent{
public:
    Agent();
    //Agent(Agent *newAgent);

    virtual void act(Session& session);

};

class ContactTracer: public Agent{
public:
    ContactTracer();

    virtual void act(Session& session);
};


class Virus: public Agent{
public:
    Virus(int nodeInd);
    int nextNodeToInfect(int ind, Graph &graph);

    virtual void act(Session &session);
private:
    const int nodeInd;
    bool active;                    //if false, there's no uninfected neighbors
};

#endif