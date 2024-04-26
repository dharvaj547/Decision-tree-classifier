#pragma once

#include "BinaryNode.hpp"
#include "BinaryDataset.hpp"

class BinaryDecisionTree {
private:
    BinaryNode *_root = new BinaryNode();

    void growTree(BinaryDataset *, BinaryNode *);
    void deleteSubtree(BinaryNode *);
    int leafCount(BinaryNode *);

public:
    BinaryDecisionTree();
    explicit BinaryDecisionTree(BinaryDataset *);
    virtual ~BinaryDecisionTree();

    bool isEmpty();
    int classify(const double *);
    int size();

    // Getters and setters
    BinaryNode *getRoot();
    void setRoot(BinaryNode *);
};