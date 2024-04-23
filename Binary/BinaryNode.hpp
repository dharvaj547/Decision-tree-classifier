#pragma once

class BinaryNode {
public:
    // Constructors and destructors
    BinaryNode();
    virtual ~BinaryNode();

    // Setters and getters
    BinaryNode *getNodeY();
    BinaryNode *getNodeN();
    void setNodeY(BinaryNode *);
    void setNodeN(BinaryNode *);
    void setDecisionDim(unsigned int);
    unsigned int getDecisionDim();
    void setDecisionCriterion(double);
    double getDecisionCriterion();
    void setLabel(int);
    int getLabel();
    void setImpurity(double);
    double getImpurity();

    // Other methods
    bool isLeaf();

private:
    BinaryNode *nodeY;
    BinaryNode *nodeN;
    unsigned int decisionDim;
    double decisionCriterion;
    int label;
    double impurity;
};