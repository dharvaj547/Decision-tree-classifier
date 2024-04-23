#pragma once

#include <iostream>
#include <fstream>
#include <cmath>

#define MAX_OBSERVATIONS 500
#define MAX_NUM_FEATURES 10

class BinaryDataset {
public:
    // Constructors and deconstructors
    BinaryDataset();
    BinaryDataset(const char *, unsigned int);
    virtual ~BinaryDataset();

    // Getters and setters
    void setNumFeatures(unsigned int);
    unsigned int getNumFeatures() const;
    void getObservation(unsigned int, double *);
    void setObservation(unsigned int, const double *);
    void setLabel(unsigned int, int);
    int getLabel(unsigned int);
    unsigned int getNumObservations() const;
    void setNumObservations(unsigned int);

    // Other methods
    void split(unsigned int, unsigned int, BinaryDataset *, BinaryDataset *);
    void splitLOO(unsigned int, BinaryDataset *, BinaryDataset *);
    void findOptimalSplit(unsigned int *, unsigned int *);
    double calcImpurityEntropy();
    int getMajorityLabel();
    bool isEmpty() const;
    void appendObservation(double *, int);
    void zero();

private:
    unsigned int numFeatures;
    double observation[MAX_OBSERVATIONS][MAX_NUM_FEATURES];
    int label[MAX_OBSERVATIONS];
    unsigned int numObservations;
};