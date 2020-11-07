#ifndef TREE_H_
#define TREE_H_

#include <vector>

class Session;

class Tree{
public:
    Tree(int rootLabel);
    Tree(const Tree& other);
    virtual Tree* clone() const = 0;
    void addChild(const Tree& child);
    static Tree* createTree(const Session& session, int rootLabel);
    virtual int traceTree()=0;
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