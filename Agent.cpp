using namespace std;
#include "Agent.h"
#include "Session.h"

/*********************** Agent **********************/

Agent::Agent() {}

/*********************** ContactTracer **********************/

ContactTracer::ContactTracer()  {}


Agent *ContactTracer::clone() const {
    return new ContactTracer(*this);
}

void ContactTracer::act(Session& session)
{
    int infected = session.dequeueInfected();
    if(infected != -1)
    {
        Tree *infectedT = Tree::createTree(session, infected);
        infectedT->BFS(session);
        int detach = infectedT->traceTree();
        session.changeGraph().detach(detach);
    }
}







/*********************** Virus **********************/


Virus::Virus(int nodeInd) : nodeInd(nodeInd), active(true) {}

Agent *Virus::clone() const {
    return new Virus(*this);
}


void Virus::act(Session &session)
{
    if (!this->active)
        return;
    Graph graph = session.changeGraph();
    if (!graph.isInfected(nodeInd))
        {
            graph.infectNode(nodeInd);
            session.enqueueInfected(nodeInd);
        }
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
    const vector<vector<int>>& edges = graph.getEdges();
    for (int i=0; i<edges.size(); i++)
    {
        int edge = edges[ind][i];
        if (edge == 1)              //means there's an edge between ind and i
            if (!graph.isInfected(edge))
                return edge;
    }
    return -1;
}




