#include "Tree.h"
#include "Session.h"
#include "Graph.h"
using namespace std;


/*********************** Tree **********************/

Tree::Tree(int rootLabel): node(rootLabel){}

Tree::Tree(const Tree& other): node(other.node){
    for(int i=0; i<other.children.size();i++){
        Tree* newTree = other.children[i]->clone();
        children.push_back(newTree);
    }

}

Tree *Tree::createTree(const Session &session, int rootLabel) {
    TreeType treeType = session.getTreeType();
    if(treeType == Cycle)
        return new CycleTree(rootLabel, session.getCycle());
    else if(treeType == MaxRank)
        return new MaxRankTree(rootLabel);
    else
        return new RootTree(rootLabel);
}

void Tree::BFS(Session &session)
{
    vector<int> added;
    for (int i=0; i<session.getGraph().getEdges().size();i++)
    {
        if (i == this->getInd())
            added.push_back(-2);
        else
            added.push_back(-1);
    }
    BFSRun(*this,added,session);
}

void Tree::BFSRun(Tree& parent, vector<int> added, const Session &session)
{
    const vector<vector<int>> &edges = session.getGraph().getEdges();
    for (int neigh=0; neigh<edges.size(); neigh++)
    {
        if (edges[parent.getInd()][neigh] == 1 & added[neigh] == -1)
            added[neigh] = parent.getInd();
    }
    for (int neigh=0; neigh<edges.size(); neigh++)
    {
        if (added[neigh] == parent.getInd())
        {
            Tree* tempTree = createTree(session,neigh);
            parent.addChild(*tempTree);
            BFSRun(*tempTree,added,session);
        }
    }
}

void Tree::addChild(const Tree &child)
{
    Tree* copyChild = child.clone();
    addChild(copyChild);
}

void Tree::addChild(Tree *child)
{
    children.push_back(child);
}

int Tree::getInd()
{
    return node;
}
bool Tree::hasChildren() {return !children.empty();}

Tree& Tree::getNextLeft() {return *this->children[0];}
int Tree::numOfChildren() {return this->children.size();}



/********   a*************** CycleTree **********************/

CycleTree::CycleTree(int rootLabel, int currCycle): Tree(rootLabel), currCycle(currCycle){}

int CycleTree::traceTree()
{
    return tracing(*this, currCycle);
}

int CycleTree::tracing(Tree& tree, int cycle)
{
    if (cycle == 0 || !tree.hasChildren())
        return tree.getInd();
    return tracing(tree.getNextLeft(), cycle-1);
}


Tree *CycleTree::clone() const {
    return new CycleTree(*this);
}


/*********************** MaxRankTree **********************/

MaxRankTree::MaxRankTree(int rootLabel):Tree(rootLabel) {}
int MaxRankTree::traceTree()
{
    vector<int> max;
    max.push_back(this->getInd());
    max.push_back(this->numOfChildren());
    vector<Tree*> nodes;
    nodes.push_back(this);
    for (Tree* tree: nodes)
        tree->fillingNodes(nodes);

    for (Tree* tree: nodes)
    {
        if (tree->numOfChildren() > max[1])
        {
            max[1] = tree->numOfChildren();
            max[0] = tree->getInd();
        }
    }
    return max[0];
}

void Tree::fillingNodes(vector<Tree*> nodes)
{
    for (Tree* tree: this->children)
        nodes.push_back(tree);

}


Tree *MaxRankTree::clone() const {
    return new MaxRankTree(*this);
}


/*********************** RootTree **********************/

RootTree::RootTree(int rootLabel):Tree(rootLabel) {}

int RootTree::traceTree() {
    return this->getInd();
}

Tree *RootTree::clone() const {
    return new RootTree(*this);
}
