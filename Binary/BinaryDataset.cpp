#include "BinaryDataset.hpp"

BinaryDataset::BinaryDataset() { 
  // TODO IMPLEMENT //
  this->numFeatures = 0;
  this->numObservations = 0;
}

BinaryDataset::BinaryDataset(const char *filename_in, unsigned int num_features) {
  // TODO IMPLEMENT //
  unsigned int r = 0;
  this->numFeatures = num_features;

  // open file
  ifstream dataset(filename_in);

  // check for errors opening file
  if (!dataset.is_open()) 
    cout << "Error opening file" << endl;

  // read file line by line
  while(!dataset.eof()) {
    for (unsigned int c = 0; c < num_features; c++) { 
      // input data into observation
      dataset >> observation[r][c];  
    }
    // input data into label
    dataset >> label[r];
    r++;
  }

  this->numObservations = r - 1;

  // close file
  dataset.close();
}

BinaryDataset::~BinaryDataset() { 
  // TODO IMPLEMENT //
}

bool BinaryDataset::isEmpty() {
  // TODO IMPLEMENT //
  return this->numObservations == 0;
}

int BinaryDataset::getMajorityLabel() { 
  // TODO IMPLEMENT //
  int neg = 0;
  int pos = 0;

  for (unsigned int i = 0; i < this->numObservations; i++) {
    // count number of labels which are negative
    if (this->getLabel(i) == -1) { 
      neg++; 
    } 
    // count number of labels which are positive 
    else if (this->getLabel(i) == 1) { 
      pos++; 
    }
  }

  // return majority label type
  if (pos >= neg) {
    return 1;
  }

  return -1;
}

double BinaryDataset::calcImpurityEntropy() {
  // TODO IMPLEMENT //
  unsigned int n = this->numObservations;
  unsigned int n1 = 0, n2 = 0;

  // count number of labels which are in class 1 or 2
  for (unsigned int i = 0; i < this->numObservations; i++) {
    // negative labels are class 1
    if (this->getLabel(i) == -1) { 
      n1++; 
    } 
    // positive labels are class 2
    else if (this->getLabel(i) == 1) { 
      n2++; 
    }
  }

  // if class 1 or class 2 is 0, entropy impurity is 0
  if (!n1 || !n2) {
    return 0.0;
  }

  double ratio1 = double(n1) / double(n);
  double ratio2 = double(n2) / double(n);

  // calculate entropy impurity
  double result = -ratio1 * log2(ratio1) - ratio2  * log2(ratio2);

  return result; 
}

void BinaryDataset::print() {
  // TODO IMPLEMENT IF YOU WANT //
}

void BinaryDataset::split(unsigned int iidim, unsigned int iiobs, BinaryDataset *subset1, BinaryDataset *subset2) {
  // TODO IMPLEMENT //
  double features [numFeatures];

  // reset number of observations for both subsets
  subset1->zero();
  subset2->zero();
  
  // set number of features for both subsets
  subset1->setNumFeatures(this->numFeatures);
  subset2->setNumFeatures(this->numFeatures);

  // loop over number of observations
  for (unsigned int i = 0; i < this->numObservations; i++) {
    this->getObservation(i, features);
    
    // if value is less than given observation value, append to subset1
    if (this->observation[i][iidim] < this->observation[iiobs][iidim]) {
      subset1->appendObservation(features, this->getLabel(i));
    } 
    // otherwise append to subset2
    else {
      subset2->appendObservation(features, this->getLabel(i));
    }
  }
}

void BinaryDataset::appendObservation(double *ft_in, int label_in) {
  // TODO IMPLEMENT //
  // append observation at next available position
  this->setObservation(numObservations, ft_in);
  this->setLabel(numObservations, label_in);

  // update number of observations
  this->numObservations++;
}

void BinaryDataset::splitLOO(unsigned int ii, BinaryDataset *dataset1, BinaryDataset *dataset2) {
  // TODO IMPLEMENT //
  double features [this->numFeatures];

  // reset number of observations for both datasets
  dataset1->zero();
  dataset2->zero();

  // set number of features for both subsets
  dataset1->setNumFeatures(this->numFeatures);
  dataset2->setNumFeatures(this->numFeatures);

  for (unsigned int i = 0; i < this->numObservations; i++) {
    this->getObservation(i, features);

    // append observation that matches index ii to dataset2
    if (i == ii) {
      dataset2->appendObservation(features, this->getLabel(i));
    } 
    // add all other observations to dataset1
    else {
      dataset1->appendObservation(features, this->getLabel(i));
    }
  }
}

void BinaryDataset::findOptimalSplit(unsigned int *out_dim, unsigned int *out_ii) {
  // TODO IMPLEMENT //
  unsigned int optimal_dim = 0, optimal_ixobs = 0;
  double current_drop = 0.0, max_drop = 0.0;
  BinaryDataset *subset1 = new BinaryDataset();
  BinaryDataset *subset2 = new BinaryDataset();

  // loop over feature dimensions
  for (unsigned int i = 0; i < this->numFeatures; i++) {
    // loop over all observations
    for (unsigned int j = 0; j < this->numObservations; j++) {
      // split dataset along these dimensions
      this->split(i, j, subset1, subset2);

      double IeD = this->calcImpurityEntropy();
      double IeD1 = subset1->calcImpurityEntropy(); 
      double IeD2 = subset2->calcImpurityEntropy();
      double n = this->getNumObservations();
      double n1 = subset1->getNumObservations();

      // calculate impurity drop for this split
      current_drop = IeD - (n1/n) * IeD1 - (1.0 - n1/n) * IeD2;

      // get max impurity drop 
      if (current_drop > max_drop) {
        max_drop = current_drop;
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

void BinaryDataset::getObservation(unsigned int ix, double *features) {
  // TODO IMPLEMENT //
  // error checking
  if (ix > this->numObservations) {
    return;
  }
  
  // add observation at given row index
  for (unsigned int i = 0; i < this->numFeatures; i++) {
    features[i] = this->observation[ix][i];
  }
}

void BinaryDataset::setObservation(unsigned int ix, double *features) {
  // TODO IMPLEMENT //
  // set observation at given row (ix)
  for (unsigned int i =0; i < this->numFeatures; i++) {
    this->observation[ix][i] = features[i];
  }
}

void BinaryDataset::setLabel(unsigned int ix, int label_in) {
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

  this->label[ix] = label_in;
}

int BinaryDataset::getLabel(unsigned int ix) {
  // TODO IMPLEMENT //
  return this->label[ix];
}

void BinaryDataset::setNumFeatures(unsigned int num_features_in){
  // TODO IMPLEMENT //
  this->numFeatures = num_features_in;
}

unsigned int BinaryDataset::getNumFeatures(){
  // TODO IMPLEMENT //
  return this->numFeatures;
}

unsigned int BinaryDataset::getNumObservations(){
  // TODO IMPLEMENT //
  return this->numObservations;
}

void BinaryDataset::setNumObservations(unsigned int num_observations_in){
  // TODO IMPLEMENT //
  this->numObservations = num_observations_in;
}

void BinaryDataset::zero() {
  this->setNumObservations(0);
}