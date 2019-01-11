#include "tests.h"

#include <iostream>

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
    Matrix U(1, 3);
    Matrix V(3, 1);
    U.dot(V).print();
    Matrix testCopy = A;
    testCopy.print();
    std::cout << "Test Matrices ok" << std::endl;
}

void testPerceptron(){
    int* profile = new int[3];
    profile[0] = 2;
    profile[1] = 6;
    profile[2] = 3;
    Perceptron P = Perceptron(3, profile);
    P.print();
    Matrix A = Matrix(1, 2);
    A.print();
    P.feedForward(A).print();
}

