#ifndef TREE_H_
#define TREE_H_
#include "Graph.h"
#include <vector>

class Session;

class Tree{
public:
    Tree(int rootLabel);
    Tree(const Tree& other);
    virtual Tree* clone() const = 0;
    void addChild(const Tree& child);
    void addChild(Tree* child);
    static Tree* createTree(const Session& session, int rootLabel);
    virtual int traceTree()=0;
    void BFS(Session& session);
    int getInd();
    bool hasChildren();
    Tree* getNextLeft();
    int numOfChildren();
    void fillingNodes(vector<Tree*> nodes);

private:
    int node;
    void BFSRun(Tree* parent,vector<int> added, const Session& session);


protected:
    std::vector<Tree*> children;
    int depth;
};

class CycleTree: public Tree{
public:
    CycleTree(int rootLabel, int currCycle);
    virtual Tree* clone() const;
    virtual int traceTree();
    int tracing(Tree* tree, int cycle);
private:
    int currCycle;
};

class MaxRankTree: public Tree{
public:
    MaxRankTree(int rootLabel);
    virtual Tree* clone() const;
    virtual int traceTree();

};

class RootTree: public Tree{
public:
    RootTree(int rootLabel);
    virtual Tree* clone() const;
    virtual int traceTree();
};

#endif