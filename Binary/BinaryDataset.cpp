#include "BinaryDataset.hpp"

BinaryDataset::BinaryDataset() {
    _numFeatures = 0;
    _numObservations = 0;
}

BinaryDataset::BinaryDataset(const char *filename_in, int num_features) {
    int r = 0;
    _numFeatures = num_features;

    std::ifstream dataset(filename_in);
    if (!dataset.is_open()) {
        std::cout << "Error opening file" << std::endl;
    }

    while (!dataset.eof()) {
        for (int c = 0; c < num_features; c++) {
            // input data into _observation
            dataset >> _observation[r][c];
        }
        // input data into _label
        dataset >> _label[r];
        r++;
    }
    dataset.close();

    _numObservations = r - 1;
}

void BinaryDataset::split(int iidim, int iiobs, BinaryDataset *subset1, BinaryDataset *subset2) {
    double features[_numFeatures];

    subset1->zero();
    subset2->zero();
    subset1->setNumFeatures(_numFeatures);
    subset2->setNumFeatures(_numFeatures);

    for (int i = 0; i < _numObservations; i++) {
        getObservation(i, features);

        // if value is less than given observation value, append to subset1
        if (_observation[i][iidim] < _observation[iiobs][iidim]) {
            subset1->appendObservation(features, getLabel(i));
        }
        // otherwise append to subset2
        else {
            subset2->appendObservation(features, getLabel(i));
        }
    }
}

void BinaryDataset::splitLOO(int ii, BinaryDataset *dataset1, BinaryDataset *dataset2) {
    double features[_numFeatures];

    dataset1->zero();
    dataset2->zero();
    dataset1->setNumFeatures(_numFeatures);
    dataset2->setNumFeatures(_numFeatures);

    for (int i = 0; i < _numObservations; i++) {
        getObservation(i, features);

        // append observation that matches index ii to dataset2
        if (i == ii) {
            dataset2->appendObservation(features, getLabel(i));
        }
        // add all other observations to dataset1
        else {
            dataset1->appendObservation(features, getLabel(i));
        }
    }
}

void BinaryDataset::findOptimalSplit(int *out_dim, int *out_ii) {
    int optimal_dim = 0;
    int optimal_ixobs = 0;
    double max_impurity_drop = 0.0;

    auto *subset1 = new BinaryDataset();
    auto *subset2 = new BinaryDataset();

    for (int i = 0; i < _numFeatures; i++) {
        for (int j = 0; j < _numObservations; j++) {
            // split dataset along these dimensions
            split(i, j, subset1, subset2);

            double IeD = calcImpurityEntropy();
            double IeD1 = subset1->calcImpurityEntropy();
            double IeD2 = subset2->calcImpurityEntropy();
            double n = getNumObservations();
            double n1 = subset1->getNumObservations();

            double impurity_drop = IeD - (n1 / n) * IeD1 - (1.0 - n1 / n) * IeD2;

            if (impurity_drop > max_impurity_drop) {
                max_impurity_drop = impurity_drop;
                optimal_dim = i;
                optimal_ixobs = j;
            }
        }
    }

    *out_dim = optimal_dim;
    *out_ii = optimal_ixobs;

    delete subset1;
    delete subset2;
}

double BinaryDataset::calcImpurityEntropy() {
    int n = _numObservations;
    int n1 = 0, n2 = 0;

    // count number of labels which are in class 1 or 2
    for (int i = 0; i < _numObservations; i++) {
        if (getLabel(i) == -1) {
            n1++;
        }
        else if (getLabel(i) == 1) {
            n2++;
        }
    }

    // if class 1 or class 2 is 0, entropy impurity is 0
    if (!n1 || !n2) {
        return 0.0;
    }

    double ratio1 = double(n1) / double(n);
    double ratio2 = double(n2) / double(n);
    double impurity_entropy = -ratio1 * log2(ratio1) - ratio2 * log2(ratio2);

    return impurity_entropy;
}

int BinaryDataset::getMajorityLabel() {
    int neg = 0;
    int pos = 0;

    for (int i = 0; i < _numObservations; i++) {
        if (getLabel(i) == -1) {
            neg++;
        }
        else if (getLabel(i) == 1) {
            pos++;
        }
    }

    if (pos >= neg) {
        return 1;
    }

    return -1;
}

bool BinaryDataset::isEmpty() const {
    return _numObservations == 0;
}

void BinaryDataset::appendObservation(double *ft_in, int label_in) {
    setObservation(_numObservations, ft_in);
    setLabel(_numObservations, label_in);

    _numObservations++;
}

void BinaryDataset::zero() {
    setNumObservations(0);
}


/*-------------------- GETTERS AND SETTERS ------------------- */
int BinaryDataset::getNumFeatures() const {
    return _numFeatures;
}

void BinaryDataset::setNumFeatures(int num_features_in) {
    _numFeatures = num_features_in;
}

void BinaryDataset::getObservation(int ix, double *features) {
    // error checking
    if (ix > _numObservations) {
        return;
    }

    for (int i = 0; i < _numFeatures; i++) {
        features[i] = _observation[ix][i];
    }
}

void BinaryDataset::setObservation(int ix, const double *features) {
    for (int i = 0; i < _numFeatures; i++) {
        _observation[ix][i] = features[i];
    }
}

int BinaryDataset::getLabel(int ix) {
    return _label[ix];
}

void BinaryDataset::setLabel(int ix, int label_in) {
    _label[ix] = label_in;
}

int BinaryDataset::getNumObservations() const {
    return _numObservations;
}

void BinaryDataset::setNumObservations(int num_observations_in) {
    _numObservations = num_observations_in;
}

BinaryDataset::~BinaryDataset() {

}