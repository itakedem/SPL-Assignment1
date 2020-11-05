#ifndef AGENT_H_
#define AGENT_H_

#include <vector>
#include "Session.h"

class Agent{
public:
    Agent(Session& session);
    Agent(Agent *newAgent);

    virtual void act(Session& session)=0;

protected:
    Session& session;
};

class ContactTracer: public Agent{
public:
    ContactTracer(Session& session);

    virtual void act();
};


class Virus: public Agent{
public:
    Virus(int nodeInd, Session& session);
    int nextNodeToInfect(int ind, Graph graph);

    virtual void act();
private:
    const int nodeInd;
    bool active;                    //if false, there's no uninfected neighbors
};

#endif