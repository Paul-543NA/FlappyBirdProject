#include "bird.h"
#include <iostream>

int* Bird::getCoords() const {
    static int coords [2];
    coords[0] = this->getX();
    coords[1] = this->getY();
    return coords;
};
void Bird::print() const{
    std::cout << "-- Printing Bird object --" << std::endl;
    std::cout << "Coords:   (" << this->getX() << " ,"<< this->getY() << ")" << std::endl;
    std::cout << "Velocity: " << this->getVelovity() << std::endl;
    std::cout << "Fitness:  " << this->getFirness() << std::endl;
    std::cout << "Alive:    " << this->getIsAlive() << std::endl;
}
