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

#endif /* perceptron_hpp */

class Perceptron{
public:
    Perceptron(int depth, int* profils);
    ~Perceptron();
    
    void print() const;
    int* feedForward(int* X) const;
private:
    int m_depth; // Nombre de couches
    int* m_profile; // Nombre de neurones par couche
    float*** m_weights; // Poids
    float** m_biaises; // Biais
};
