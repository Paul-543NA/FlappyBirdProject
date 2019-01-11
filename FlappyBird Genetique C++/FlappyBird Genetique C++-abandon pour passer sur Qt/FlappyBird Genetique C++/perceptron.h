#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#include <stdio.h>
#include <math.h>
#include <iostream>
#include "matrix.h"

class Perceptron{
public:
    Perceptron(int depth, int profile[]);
    ~Perceptron();

    void print() const;
    Matrix feedForward(Matrix X) const;
private:
    int m_depth; // Nombre de couches
    int* m_profile; // Nombre de neurones par couche
    Matrix** m_weights; // Poids
    Matrix** m_biaises; // Biais
};

Matrix sigmoid(Matrix M);

#endif // PERCEPTRON_H
