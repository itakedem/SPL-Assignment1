using namespace std;
#include "Agent.h"
#include "Session.h"


Agent::Agent(Session &session): session(session){}
ContactTracer::ContactTracer(Session &session) : Agent(session) {}
Virus::Virus(int nodeInd, Session *session) : nodeInd(nodeInd), Agent(session), active(true) {}


void ContactTracer::act()
{

}





void Virus::act()
{
    if (!this->active)
        return;
    Graph& graph = session.getGraph();
    if (!graph.isInfected(nodeInd))
        {graph.infectNode(nodeInd);}
    int nextNode = nextNodeToInfect(nodeInd,graph);
    if (nextNode != -1)                     //-1 means no next node
    {
        Virus *newVirus = new Virus(nextNode, session);         //do we need to delete???
        session.addAgent(*newVirus);        //why we need * and not &?
    }
    else
        this->active= false;
}

int nextNodeToInfect(int ind,  Graph &graph)
{
    std::vector<std::vector<int>>& edges = graph.getEdges();
    for (int i=0; i<edges.size(); i++)
    {
        int edge = edges[ind][i];
        if (edge == 1)              //means there's an edge between ind and i
            if (!graph.isInfected(edge))
                return edge;
    }
    return -1;
}


