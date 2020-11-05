//
// Created by Itamar Kedem on 02/11/2020.
//

#include "Tree.h"
using namespace std;

Tree::Tree(int rootLabel): node(rootLabel){children = new vector<Tree*> ;}

void Tree::addChild(const Tree &child) {

}

Tree *Tree::createTree(const Session &session, int rootLabel) {
    return nullptr;
}

CycleTree::CycleTree(int rootLabel, int currCycle): Tree(rootLabel), currCycle(currCycle){}

int CycleTree::traceTree() {
    return 0;
}


MaxRankTree::MaxRankTree(int rootLabel):Tree(rootLabel) {}
int MaxRankTree::traceTree() {
    return 0;
}

RootTree::RootTree(int rootLabel):Tree(rootLabel) {}

int RootTree::traceTree() {
    return 0;
}
