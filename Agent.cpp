using namespace std;
#include "Agent.h"
#include "Session.h"


Agent::Agent() {}

void Agent::act(Session &session) {

}

ContactTracer::ContactTracer()  {}
Virus::Virus(int nodeInd) : nodeInd(nodeInd), active(true) {}
//Agent::Agent(Agent agent)

void ContactTracer::act(Session& session)
{
    return;
}





void Virus::act(Session &session)
{
    if (!this->active)
        return;
    Graph& graph = session.getGraph();
    if (!graph.isInfected(nodeInd))
        {graph.infectNode(nodeInd);}
    int nextNode = nextNodeToInfect(nodeInd,graph);
    if (nextNode != -1)                     //-1 means no next node
    {
        Virus *newVirus = new Virus(nextNode);         //do we need to delete???
        session.addAgent(*newVirus);        //why we need * and not &?
    }
    else
        this->active= false;
}


int Virus::nextNodeToInfect(int ind, Graph &graph)
{
    vector<vector<int>>& edges = graph.getEdges();
    for (int i=0; i<edges.size(); i++)
    {
        int edge = edges[ind][i];
        if (edge == 1)              //means there's an edge between ind and i
            if (!graph.isInfected(edge))
                return edge;
    }
    return -1;
}


