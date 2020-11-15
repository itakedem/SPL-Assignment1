#include "../include/Tree.h"
#include "../include/Session.h"
#include "../include/Graph.h"
using namespace std;


/*********************** Tree **********************/

Tree::Tree(int rootLabel): node(rootLabel), children({}){}

//Copy Constructor
Tree::Tree(const Tree& other): node(other.node), children({}){
    for(unsigned int i=0; i<other.children.size();i++){
        Tree* newTree = other.children[i]->clone();
        children.push_back(newTree);
    }

}

//move Constructor
Tree::Tree(Tree&& tree): node(tree.node), children({})
{
    for(Tree* child: tree.children)
    {
        addChild(child);
        child = nullptr;
    }
    tree.children.clear();
}


//destructor
Tree::~Tree() {clear();}

//clear children vector
void Tree::clear()
{
    for (Tree* tree: children)
    {
        if (tree != nullptr)
        {
            delete tree;
            tree = nullptr;
        }
    }
    children.clear();
}


//assignment operator
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
    return *this;
}


//move operator
Tree &Tree::operator=(Tree &&other)
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
        other.children.clear();

    }
    return *this;
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
    vector<int> added;          //marks which node was added to the tree
    for (unsigned int i=0; i<edges.size(); i++)         //sets vector added with 0's
        added.push_back(0);
    added[node] = 1;        //sets the current node as added
    vector<Tree*> trees;            //queue of trees to add
    trees.push_back(this);
    while (!trees.empty())
    {
        Tree* tree = trees[0];
        trees.erase(trees.cbegin());
        int ind = tree->getInd();
        for (unsigned int i=0;  i<edges.size(); i++)
        {
            if ((edges[ind][i] == 1) & (added[i] == 0))     //if there's an edge in the graph and the node wasn't added to the tree then execute
            {
                Tree* newTree = createTree(session, i);
                tree->addChild(newTree);
                added[i] = 1;
                trees.push_back(newTree);       //adding to the tree queue so we would go over his children
            }
        }
    }
}

//adding a clone of the child
void Tree::addChild(const Tree &child)
{
    Tree* copyChild = child.clone();
    addChild(copyChild);
}

//adding the child
void Tree::addChild(Tree *child){children.push_back(child);}

int Tree::getInd(){return node;}
bool Tree::hasChildren() {return !children.empty();}

Tree& Tree::getNextLeft() {return *this->children[0];}      //returns the left most child (children[0])
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
    vector<int> max;        //holds the node's data which we would return (nodeId, amountOfChildren)
    max.push_back(this->getInd());
    max.push_back(this->numOfChildren());
    vector<Tree*> nodes;        //trees we need to go over
    nodes.push_back(this);
    while(!nodes.empty())
    {
        Tree* tree = nodes[0];
        nodes.erase(nodes.cbegin());
        fillingNodes(nodes,tree);       //inserts the children of the current node
        if (tree->numOfChildren() > max[1])
        {
            max[0] = tree->getInd();
            max[1] = tree->numOfChildren();
        }
    }
    return max[0];
}


//inserts all tree children into node vector (used in traceTree() for fill our checking queue)
void MaxRankTree::fillingNodes(vector<Tree*>& nodes, Tree* tree)
{
    for (Tree* child: tree->getChildren())
        nodes.push_back(child);

}

const vector<Tree *> &Tree::getChildren() const {return children;}


Tree *MaxRankTree::clone() const {return new MaxRankTree(*this);}


/*********************** RootTree **********************/

RootTree::RootTree(int rootLabel):Tree(rootLabel) {}

int RootTree::traceTree() {return this->getInd();}

Tree *RootTree::clone() const {return new RootTree(*this);}
