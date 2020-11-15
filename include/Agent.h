#ifndef AGENT_H_
#define AGENT_H_

#include <vector>
#include "../include/Session.h"
#include "../include/Tree.h"

class Agent{
public:
    Agent();
    virtual ~Agent();       //destructor
    virtual Agent* clone() const =0;
    virtual void act(Session& session)=0;

};

class ContactTracer: public Agent{
public:
    ContactTracer();
    virtual Agent* clone() const;
    virtual void act(Session& session);
};


class Virus: public Agent{
public:
    Virus(int nodeInd);
    virtual Agent* clone() const;
    int nextNodeToInfect(int ind, Graph &graph);        //finds the smallest index which is not infected
    virtual void act(Session &session);
private:
    const int nodeInd;              //Index node of the virus
    bool active;                    //if false, there's no uninfected neighbors
};

#endif