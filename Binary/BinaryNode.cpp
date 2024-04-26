#include "BinaryNode.hpp"

BinaryNode::BinaryNode() {
    _nodeY = nullptr;
    _nodeN = nullptr;
    _decisionDim = 0;
    _decisionCriterion = 0.0;
    _label = -1;
    _impurity = 0.0;
}

bool BinaryNode::isLeaf() {
    return (getNodeY() == nullptr && getNodeN() == nullptr);
}


/*-------------------- GETTERS AND SETTERS ------------------- */

BinaryNode *BinaryNode::getNodeY() {
    return _nodeY;
}

BinaryNode *BinaryNode::getNodeN() {
    return _nodeN;
}

void BinaryNode::setNodeY(BinaryNode *node_in) {
    _nodeY = node_in;
}

void BinaryNode::setNodeN(BinaryNode *node_in) {
    _nodeN = node_in;
}

void BinaryNode::setDecisionDim(int dim_in) {
    _decisionDim = dim_in;
}

int BinaryNode::getDecisionDim() const {
    return _decisionDim;
}

void BinaryNode::setDecisionCriterion(double criterion_in) {
    _decisionCriterion = criterion_in;
}

double BinaryNode::getDecisionCriterion() const {
    return _decisionCriterion;
}

void BinaryNode::setLabel(int label_in) {
    _label = label_in;
}

int BinaryNode::getLabel() const {
    return _label;
}

void BinaryNode::setImpurity(double impurity_in) {
    _impurity = impurity_in;
}

double BinaryNode::getImpurity() const {
    return _impurity;
}

BinaryNode::~BinaryNode() {

}