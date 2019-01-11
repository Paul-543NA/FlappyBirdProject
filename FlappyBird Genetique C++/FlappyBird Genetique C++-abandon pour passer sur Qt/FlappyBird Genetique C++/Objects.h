//
//  Objects.h
//  FlappyBird Genetique C++
//
//  Created by Paul on 24/12/2018.
//  Copyright © 2018 Paul. All rights reserved.
//

#ifndef Objects_h
#define Objects_h

class Object{
//public:
    //virtual void show() const; // Displays the object on the graphic interface
};

// ---------------------------------------------------------------------------------------------------

class Bird: public Object{
    
public:
    
    Bird(int x, int y){
        m_x = x;
        m_y = y;
    }
    
    int getFlapPower() const {return m_flapPower;}
    int getX() const {return m_x;}
    int getY() const {return m_y;}
    int getVelovity() const {return m_velocity;}
    bool getIsAlive() const {return m_isAlive;}
    bool getFirness() const {return m_fitness;}

    void print() const;
    int* getCoords() const;
    
private:
    // Still to add:
    // image, gravuty, brain, canheight
    int m_x;
    int m_y;
    int m_velocity = 0;
    bool m_isAlive = true;
    unsigned int m_fitness = 0;
    const int m_radius = 5;
    int const m_flapPower = 10;
};

// ---------------------------------------------------------------------------------------------------

class Pipe: public Object{
private:
    Pipe(int x, int center){
        m_x = x;
        m_center = center;
    }
private:
    int m_x;                     // x-position of the pipe
    int m_center;                // y-position of the center of the hole, initialized randomly
    const int m_holeheignt = 75; // Size of the hole
    const int m_width = 30;      // width of the pipe
    const int m_speed = 1;       // speed of the pipe
};

#endif /* Objects_h */
