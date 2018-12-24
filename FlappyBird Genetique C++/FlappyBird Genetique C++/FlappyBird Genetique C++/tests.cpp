//
//  tests.cpp
//  FlappyBird Genetique C++
//
//  Created by Paul on 24/12/2018.
//  Copyright © 2018 Paul. All rights reserved.
//

#include <stdio.h>

#include "Tests.h"
#include "Objects.h"

void testBird(){
    Bird* bird = new Bird(1, 4);
    bird->print();
}
