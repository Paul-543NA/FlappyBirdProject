//
//  perceptron.hpp
//  FlappyBird Genetique C++
//
//  Created by Paul on 25/12/2018.
//  Copyright © 2018 Paul. All rights reserved.
//

#ifndef perceptron_hpp
#define perceptron_hpp

#include <stdio.h>
#include <math.h>
#include <iostream>
#include "Matrix.hpp"

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


#endif /* perceptron_hpp */
