#include "../include/Tree.h"
#include "../include/Session.h"
#include "../include/Graph.h"
using namespace std;


/*********************** Tree **********************/

Tree::Tree(int rootLabel): node(rootLabel){}

Tree::Tree(const Tree& other): node(other.node){
    for(int i=0; i<other.children.size();i++){
        Tree* newTree = other.children[i]->clone();
        children.push_back(newTree);
    }

}
Tree::~Tree() {clear();}

void Tree::clear()
{
    for (Tree* tree: children)
    {
        if (tree != nullptr)
            delete tree;
    }
}

Tree &Tree::operator=(const Tree& other)
{
    if (this != &other)
    {
        clear();
        for (Tree* tree: other.children)
        {
            children.push_back(tree->clone());
        }
        node = other.node;
    }
}       //assignment operator

Tree &Tree::operator=(Tree &other)                  //move operator
{
    if (this != &other)
    {
        clear();
        node = other.node;
        for (Tree* tree: other.children)
        {
            children.push_back(tree);
            tree = nullptr;
        }

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

void Tree::BFS(Session& session)
{
    const vector<vector<int>>& edges = session.getGraph().getEdges();
    vector<int> added;
    for (int i=0; i<edges.size(); i++)
        added.push_back(0);
    added[node] = 1;
    vector<Tree*> trees;
    trees.push_back(this);
    while (!trees.empty())
    {
        Tree* tree = trees[0];
        trees.erase(trees.cbegin());
        int ind = tree->getInd();
        for (int i=0;  i<edges.size(); i++)
        {
            if (edges[ind][i] == 1 & added[i] == 0)
            {
                Tree* newTree = createTree(session, i);
                tree->addChild(newTree);
                added[i] = 1;
                trees.push_back(newTree);
            }
        }
    }
}

void Tree::addChild(const Tree &child)
{
    Tree* copyChild = child.clone();
    addChild(copyChild);
}

void Tree::addChild(Tree *child){children.push_back(child);}

int Tree::getInd(){return node;}
bool Tree::hasChildren() {return !children.empty();}

Tree& Tree::getNextLeft() {return *this->children[0];}
int Tree::numOfChildren() {return this->children.size();}



/********   a*************** CycleTree **********************/

CycleTree::CycleTree(int rootLabel, int currCycle): Tree(rootLabel), currCycle(currCycle){}

int CycleTree::traceTree(){return tracing(*this, currCycle);}

int CycleTree::tracing(Tree& tree, int cycle)
{
    if (cycle == 0 || !tree.hasChildren())
        return tree.getInd();
    return tracing(tree.getNextLeft(), cycle-1);
}


Tree *CycleTree::clone() const {return new CycleTree(*this);}


/*********************** MaxRankTree **********************/

MaxRankTree::MaxRankTree(int rootLabel):Tree(rootLabel) {}

int MaxRankTree::traceTree()
{
    vector<int> max;
    max.push_back(this->getInd());
    max.push_back(this->numOfChildren());
    vector<Tree*> nodes;
    nodes.push_back(this);
    while(!nodes.empty())
    {
        Tree* tree = nodes[0];
        nodes.erase(nodes.cbegin());
        fillingNodes(nodes,tree);
        if (tree->numOfChildren() > max[1])
        {
            max[1] = tree->numOfChildren();
            max[0] = tree->getInd();
        }
    }
    return max[0];
}


void Tree::fillingNodes(vector<Tree*>& nodes, Tree* tree)
{
    for (Tree* child: tree->children)
        nodes.push_back(child);

}


Tree *MaxRankTree::clone() const {return new MaxRankTree(*this);}


/*********************** RootTree **********************/

RootTree::RootTree(int rootLabel):Tree(rootLabel) {}

int RootTree::traceTree() {return this->getInd();}

Tree *RootTree::clone() const {return new RootTree(*this);}
