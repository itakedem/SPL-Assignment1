using namespace std;
#include "Agent.h"
#include "Session.h"


    Agent(Session& session): session(session){

    }

void ContactTracer::act() {

}

Virus::Virus(int nodeInd, Session &session) {
    nodeInd=nodeInd;
    session = session;
}

void Virus::act() {

}
