using namespace std;
#include "../include/Agent.h"
#include "../include/Session.h"

/*********************** Agent **********************/

Agent::Agent() {}
Agent::~Agent() {}

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
        delete infectedT;
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
    Graph& graph = session.changeGraph();
    if (!graph.isInfected(nodeInd))         //if node is not yet infected --> infect node
        {
            graph.infectNode(nodeInd);
            session.enqueueInfected(nodeInd);
        }
    int nextNode = nextNodeToInfect(nodeInd,graph);
    if (nextNode != -1)                     //-1 means no next node
    {
        Virus *newVirus = new Virus(nextNode);
        session.addAgent(newVirus);
        graph.CoVIDNode(nextNode);          //mark node as carrier
        session.changeGraph().setNumActives(true);
    }
    else
    {
        this->active= false;
        session.changeGraph().setNumActives(false);
    }
}

//finds the smallest index which is not infected
int Virus::nextNodeToInfect(int ind, Graph &graph)
{
    const vector<vector<int>>& edges = graph.getEdges();
    for (unsigned int i=0; i<edges.size(); i++)
    {
        int hasEdge = edges[ind][i];
        if (hasEdge == 1)              //means there's an edge between ind and i
            if (!graph.isInfected(i) & !graph.isCoVIDed(i))     //checks if there's no virus on the node
                return i;
    }
    return -1;
}




