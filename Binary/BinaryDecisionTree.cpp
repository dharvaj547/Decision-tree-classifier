#include "BinaryDecisionTree.hpp"

BinaryDecisionTree::BinaryDecisionTree() {
    root = nullptr;
}

BinaryDecisionTree::BinaryDecisionTree(BinaryDataset *dataset) {
    growTree(dataset, root);
}

bool BinaryDecisionTree::isEmpty() {
    return root == nullptr;
}

BinaryNode *BinaryDecisionTree::getRoot() {
    return root;
}

int BinaryDecisionTree::classify(const double *ft_in) {
    BinaryNode *node = root;

    while (!node->isLeaf()) {
        // check whether to traverse to "yes" node
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
    unsigned int out_dim, out_ii;
    auto *feature = new double[dataset_in->getNumFeatures()];

    auto *subset1 = new BinaryDataset();
    auto *subset2 = new BinaryDataset();

    node_in->setImpurity(dataset_in->calcImpurityEntropy());
    node_in->setLabel(dataset_in->getMajorityLabel());

    // if dataset is not pure
    if (node_in->getImpurity() > 0.0) {
        dataset_in->findOptimalSplit(&out_dim, &out_ii);

        dataset_in->getObservation(out_ii, feature);
        node_in->setDecisionDim(out_dim);
        node_in->setDecisionCriterion(feature[out_dim]);

        dataset_in->split(out_dim, out_ii, subset1, subset2);

        // create child nodes
        auto *child1 = new BinaryNode();
        auto *child2 = new BinaryNode();
        node_in->setNodeY(child1);
        node_in->setNodeN(child2);

        // recursively call itself twice, once for each dataset resulting from split
        growTree(subset1, node_in->getNodeY());
        growTree(subset2, node_in->getNodeN());
    }

    delete subset1;
    delete subset2;
    delete[] feature;
}

void BinaryDecisionTree::deleteSubtree(BinaryNode *node_in) {
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
    return leafCount(getRoot());
}

unsigned int BinaryDecisionTree::leafCount(BinaryNode *node_in) {
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

void BinaryDecisionTree::setRoot(BinaryNode *node_in) {
    root = node_in;
}

BinaryDecisionTree::~BinaryDecisionTree() {
    deleteSubtree(root);
}