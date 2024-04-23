#pragma once

#include "BinaryNode.hpp"
#include "BinaryDataset.hpp"

class BinaryDecisionTree {
public:
    // Constructors and destructors
    BinaryDecisionTree();
    explicit BinaryDecisionTree(BinaryDataset *);
    virtual ~BinaryDecisionTree();

    // Getters and setters
    BinaryNode *getRoot();
    void setRoot(BinaryNode *);

    // Other methods
    bool isEmpty();
    int classify(const double *);
    unsigned int size();

private:
    void growTree(BinaryDataset *, BinaryNode *);
    void deleteSubtree(BinaryNode *);
    unsigned int leafCount(BinaryNode *);
    BinaryNode *root = new BinaryNode();
};