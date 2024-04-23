#include "BinaryNode.hpp"

BinaryNode::BinaryNode() {
    nodeY = nullptr;
    nodeN = nullptr;
    decisionDim = 0;
    decisionCriterion = 0.0;
    label = -1;
    impurity = 0.0;
}

bool BinaryNode::isLeaf() {
    if (getNodeY() == nullptr && getNodeN() == nullptr) {
        return true;
    }

    return false;
}

BinaryNode *BinaryNode::getNodeY() {
    return nodeY;
}

BinaryNode *BinaryNode::getNodeN() {
    return nodeN;
}

void BinaryNode::setNodeY(BinaryNode *node_in) {
    nodeY = node_in;
}

void BinaryNode::setNodeN(BinaryNode *node_in) {
    nodeN = node_in;
}

void BinaryNode::setDecisionDim(unsigned int dim_in) {
    decisionDim = dim_in;
}

unsigned int BinaryNode::getDecisionDim() const {
    return decisionDim;
}

void BinaryNode::setDecisionCriterion(double criterion_in) {
    decisionCriterion = criterion_in;
}

double BinaryNode::getDecisionCriterion() const {
    return decisionCriterion;
}

void BinaryNode::setLabel(int label_in) {
    // check for invalid label values
    if (label_in != -1 || label_in != 1) {
        // negative values are corrected to -1
        if (label_in < 0) {
            label_in = -1;
        }
            // positive values are corrected to 1
        else {
            label_in = 1;
        }
    }

    label = label_in;
}

int BinaryNode::getLabel() const {
    return label;
}

void BinaryNode::setImpurity(double impurity_in) {
    // correct invalid impurity values
    if (impurity_in < 0) {
        impurity_in = 0;
    } else if (impurity_in > 1) {
        impurity_in = 1;
    }

    impurity = impurity_in;
}

double BinaryNode::getImpurity() const {
    return impurity;
}

BinaryNode::~BinaryNode() {

}