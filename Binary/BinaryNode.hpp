#pragma once

class BinaryNode {
private:
    BinaryNode *_nodeY;
    BinaryNode *_nodeN;
    int _decisionDim;
    double _decisionCriterion;
    int _label;
    double _impurity;

public:
    BinaryNode();
    virtual ~BinaryNode();

    bool isLeaf();

    // Setters and getters
    BinaryNode *getNodeY();
    void setNodeY(BinaryNode *);
    BinaryNode *getNodeN();
    void setNodeN(BinaryNode *);
    int getDecisionDim() const;
    void setDecisionDim(int);
    double getDecisionCriterion() const;
    void setDecisionCriterion(double);
    int getLabel() const;
    void setLabel(int);
    double getImpurity() const;
    void setImpurity(double);
};