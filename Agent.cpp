using namespace std;
#include "Agent.h"
#include "Session.h"


    Agent(Session& session): session(session){

    }

void ContactTracer::act() {

}

Virus::Virus(int nodeInd, Session &session) : Agent(session), nodeInd(nodeInd) {
}

void Virus::act() {

}

Agent::Agent(Session &session): session(session){}
