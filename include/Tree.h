#ifndef TREE_H_
#define TREE_H_
#include "../include/Graph.h"
#include <vector>

class Session;

class Tree{
public:
    Tree(int rootLabel);
    Tree(const Tree& other);        //copy constructor
    virtual ~Tree();                //destructor
    Tree(Tree&& tree);
    Tree& operator=(const Tree& other);     //assignment operator
    Tree& operator=(Tree&& other);          //move assignment operator
    virtual Tree* clone() const = 0;
    void addChild(const Tree& child);
    void addChild(Tree* child);
    static Tree* createTree(const Session& session, int rootLabel);
    virtual int traceTree()=0;
    void BFS(Session& session);
    int getInd();
    bool hasChildren();
    Tree& getNextLeft();        //returns the left most child (children[0])
    int numOfChildren();
    void clear();               //clear children vector
    const vector<Tree*>& getChildren() const;

private:
    int node;


protected:
    std::vector<Tree*> children;
};

class CycleTree: public Tree{
public:
    CycleTree(int rootLabel, int currCycle);
    virtual Tree* clone() const;
    virtual int traceTree();
    int tracing(Tree& tree, int cycle);     //implementing traceTree()
private:
    int currCycle;
};

class MaxRankTree: public Tree{
public:
    MaxRankTree(int rootLabel);
    virtual Tree* clone() const;
    virtual int traceTree();
    void fillingNodes(vector<Tree*>& nodes,Tree* tree);         //inserts all tree children into node vector (used in traceTree() for fill our checking queue)

};

class RootTree: public Tree{
public:
    RootTree(int rootLabel);
    virtual Tree* clone() const;
    virtual int traceTree();
};

#endif