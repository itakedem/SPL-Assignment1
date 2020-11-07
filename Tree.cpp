//
// Created by Itamar Kedem on 02/11/2020.
//

#include "Tree.h"
#include "Session.h"
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

void Tree::addChild(const Tree &child) {

}



/*********************** CycleTree **********************/

CycleTree::CycleTree(int rootLabel, int currCycle): Tree(rootLabel), currCycle(currCycle){}

int CycleTree::traceTree() {
    return 0;
}

Tree *CycleTree::clone() const {
    return new CycleTree(*this);
}


/*********************** MaxRenkTree **********************/

MaxRankTree::MaxRankTree(int rootLabel):Tree(rootLabel) {}
int MaxRankTree::traceTree() {
    return 0;
}

Tree *MaxRankTree::clone() const {
    return new MaxRankTree(*this);
}


/*********************** RootTree **********************/

RootTree::RootTree(int rootLabel):Tree(rootLabel) {}

int RootTree::traceTree() {
    return 0;
}

Tree *RootTree::clone() const {
    return new RootTree(*this);
}
