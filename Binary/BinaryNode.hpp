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
    unsigned int getDecisionDim() const;
    void setDecisionCriterion(double);
    double getDecisionCriterion() const;
    void setLabel(int);
    int getLabel() const;
    void setImpurity(double);
    double getImpurity() const;

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