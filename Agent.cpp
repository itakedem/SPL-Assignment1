using namespace std;
#include "Agent.h"
#include "Session.h"


Agent::Agent(Session &session): session(session){}
ContactTracer::ContactTracer(Session &session) : Agent(session) {}
Virus::Virus(int nodeInd, Session &session) : nodeInd(nodeInd),Agent(session) {}


void ContactTracer::act()
{

}





void Virus::act()
{
    if (session.getGraph().isInfected(nodeInd))
    {

    }
}


