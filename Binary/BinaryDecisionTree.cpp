#include "BinaryDecisionTree.hpp"

BinaryDecisionTree::BinaryDecisionTree() { 
  // TODO IMPLEMENT //
  this->root = nullptr;
}

BinaryDecisionTree::BinaryDecisionTree(BinaryDataset *dataset) { 
 // TODO IMPLEMENT //
  this->growTree(dataset, this->root);
}

BinaryDecisionTree::~BinaryDecisionTree() { 
  // TODO IMPLEMENT //
  this->deleteSubtree(this->root);
}

bool BinaryDecisionTree::isEmpty() {
  // TODO IMPLEMENT //
  return this->root == nullptr;
}

void BinaryDecisionTree::print() {
  // TODO IMPLEMENT // 
}

void BinaryDecisionTree::print(BinaryNode *node_in) { 
  // TODO IMPLEMENT //
}

BinaryNode * BinaryDecisionTree::getRoot() {
  // TODO IMPLEMENT //
  return this->root;
}

int BinaryDecisionTree::classify(double *ft_in) {
  // TODO IMPLEMENT //
  BinaryNode *node = this->root;

  // loop until leaf node is reached
  while (!node->isLeaf()) {
    // check wether to traverse to "yes" node
    if (ft_in[node->getDecisionDim()] < node->getDecisionCriterion()) {
      node = node->getNodeY();
    }
    // traverse to the "no" node
    else {
      node = node->getNodeN();
    }
  }

  return node->getLabel();
}

void BinaryDecisionTree::growTree(BinaryDataset *dataset_in, BinaryNode *node_in) {
  // TODO IMPLEMENT //
  unsigned int out_dim, out_ii;
  double *feature =  new double [dataset_in->getNumFeatures()];
  BinaryDataset *subset1 = new BinaryDataset();
  BinaryDataset *subset2 = new BinaryDataset();
  
  // set impurity and label
  node_in->setImpurity(dataset_in->calcImpurityEntropy());
  node_in->setLabel(dataset_in->getMajorityLabel());   

  // if dataset is not pure
  if (node_in->getImpurity() > 0.0) { 
    // find optimal split
    dataset_in->findOptimalSplit(&out_dim, &out_ii);

    // set decision dimension and decision criterion 
    dataset_in->getObservation(out_ii, feature);
    node_in->setDecisionDim(out_dim);
    node_in->setDecisionCriterion(feature[out_dim]);

    dataset_in->split(out_dim, out_ii, subset1, subset2);

    // create child nodes
    BinaryNode *child1 = new BinaryNode(); 
    BinaryNode *child2 = new BinaryNode();
    node_in->setNodeY(child1);
    node_in->setNodeN(child2);
  
    // recursively call itself twice, once for each dataset resulting from split
    growTree(subset1, node_in->getNodeY()); 
    growTree(subset2, node_in->getNodeN());
  }

  delete subset1;
  delete subset2;
  delete [] feature;
}

void BinaryDecisionTree::deleteSubtree(BinaryNode *node_in) {
  // TODO IMPLEMENT //
  // check for end nodes
  if (node_in == nullptr) {
    return;
  }

  // delete child nodes
  deleteSubtree(node_in->getNodeY());
  deleteSubtree(node_in->getNodeN());

  delete node_in;
}

unsigned int BinaryDecisionTree::size() { 
  // TODO IMPLEMENT //
  return this->leafCount(this->getRoot());
}

unsigned int BinaryDecisionTree::leafCount(BinaryNode *node_in) {
  // TODO IMPLEMENT //
  // initial check
  if (node_in == nullptr) {
    return 0;
  }

  // base case, check for leaf node
  if (node_in->isLeaf()) {
    return 1;
  } 
  // recursive case, count for child nodes
  else {
    return leafCount(node_in->getNodeY()) + leafCount(node_in->getNodeN());
  }
}

void BinaryDecisionTree::setRoot(BinaryNode *node_in){
  // TODO IMPLEMENT //
  this->root = node_in;
}


