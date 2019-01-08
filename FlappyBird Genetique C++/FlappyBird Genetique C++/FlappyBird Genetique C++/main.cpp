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
#include <stdlib.h>     /* srand, rand */
#include <time.h>


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    testBird();
    testMatrix();
    testPerceptron(); //Fait planter le programme ccar soucis avec la classe
    return 0;
}
