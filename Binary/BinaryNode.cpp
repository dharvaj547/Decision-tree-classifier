#include "BinaryNode.hpp"

BinaryNode::BinaryNode() {
  // TODO IMPLEMENT // 
  this->nodeY = nullptr;
  this->nodeN = nullptr;
  this->decisionDim = 0;
  this->decisionCriterion = 0.0;
  this->label = -1;
  this->impurity = 0.0;
}

BinaryNode::~BinaryNode() {
  // TODO IMPLEMENT // 
}

bool BinaryNode::isLeaf() {
  // TODO IMPLEMENT //
  // if nodeY and nodeN are nullptr, return true
  if (this->getNodeY() == nullptr && this->getNodeN() == nullptr) {
    return true;
  }

  return false;
}

// Getters and setters
BinaryNode * BinaryNode::getNodeY() {
  // TODO IMPLEMENT //
  return this->nodeY; 
}

BinaryNode * BinaryNode::getNodeN() {
  // TODO IMPLEMENT //
  return this->nodeN; 
}

void BinaryNode::setNodeY(BinaryNode *node_in) {
  // TODO IMPLEMENT //
  this->nodeY = node_in;
}

void BinaryNode::setNodeN(BinaryNode *node_in) {
  // TODO IMPLEMENT //
  this->nodeN = node_in;
}

void BinaryNode::setDecisionDim(unsigned int dim_in) {
  // TODO IMPLEMENT //
  this->decisionDim = dim_in;
}

unsigned int BinaryNode::getDecisionDim() {
  // TODO IMPLEMENT // 
  return this->decisionDim;
}

void BinaryNode::setDecisionCriterion(double criterion_in) {
  // TODO IMPLEMENT //
  this->decisionCriterion = criterion_in;
}

double BinaryNode::getDecisionCriterion() {
  // TODO IMPLEMENT //
  return this->decisionCriterion;
}

void BinaryNode::setLabel(int label_in) {
  // TODO IMPLEMENT //
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
  
  this->label = label_in;
}

int BinaryNode::getLabel() {
  // TODO IMPLEMENT //
  return this->label;
}

void BinaryNode::setImpurity(double impurity_in) {
  // TODO IMPLEMENT //
  // correct invalid impurity values
  if (impurity_in < 0) {
    impurity_in = 0;
  } else if (impurity_in > 1) {
    impurity_in = 1;
  }
  
  this->impurity = impurity_in;
}

double BinaryNode::getImpurity() {
  // TODO IMPLEMENT // 
  return this->impurity; 
}

