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

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    Bird* b = new Bird(1, 3);
    testBird();
    return 0;
}
