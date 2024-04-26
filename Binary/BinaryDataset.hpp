#pragma once

#include <iostream>
#include <fstream>
#include <cmath>

#define MAX_OBSERVATIONS 500
#define MAX_NUM_FEATURES 10

class BinaryDataset {
private:
    int _numFeatures;
    double _observation[MAX_OBSERVATIONS][MAX_NUM_FEATURES];
    int _label[MAX_OBSERVATIONS];
    int _numObservations;

public:
    BinaryDataset();
    BinaryDataset(const char *, int);
    virtual ~BinaryDataset();

    void split(int, int, BinaryDataset *, BinaryDataset *);
    void splitLOO(int, BinaryDataset *, BinaryDataset *);
    void findOptimalSplit(int *, int *);
    double calcImpurityEntropy();
    int getMajorityLabel();
    bool isEmpty() const;
    void appendObservation(double *, int);
    void zero();

    // Getters and setters
    int getNumFeatures() const;
    void setNumFeatures(int);
    void getObservation(int, double *);
    void setObservation(int, const double *);
    int getLabel(int);
    void setLabel(int, int);
    int getNumObservations() const;
    void setNumObservations(int);
};