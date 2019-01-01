//
//  main.cpp
//  FlappyBird Genetique C++
//
//  Created by Paul on 24/12/2018.
//  Copyright © 2018 Paul. All rights reserved.
//

#include <iostream>
#include "Objects.h"
#include "Tests.h"
#include "Matrix.hpp"

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    testBird();
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
    return 0;
}
