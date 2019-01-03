//
//  tests.cpp
//  FlappyBird Genetique C++
//
//  Created by Paul on 24/12/2018.
//  Copyright © 2018 Paul. All rights reserved.
//

#include <iostream>

#include "Tests.h"


void testBird(){
    Bird* bird = new Bird(1, 4);
    bird->print();
}

void testMatrix(){
    Matrix A = Matrix(2, 3);
    std::cout << A.shape()[0] << A.shape()[1] << std::endl;
    A.set_val(0, 0, 1.0f);
    A.set_val(0, 1, 1.0f);
    A.set_val(1, 0, 1.0f);
    A.set_val(1, 1, 1.0f);
    A.set_val(0, 2, 0.0f);
    A.set_val(1, 2, 0.0f);
    A.print();
    Matrix B = A.T();
    B.print();
    Matrix C = A + A;
    C.print();
    Matrix D = C * C;
    D.print();
    Matrix E = C.dot(C.T());
    E.print();
    Matrix R = Matrix(4, 4);
    R.print();
}

void testPerceptron(){
    int* profile = new int[3];
    profile[0] = 2;
    profile[1] = 6;
    profile[2] = 3;
    Perceptron P = Perceptron(3, profile);
    P.print();
}
