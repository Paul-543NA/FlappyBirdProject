#ifndef BIRD_H
#define BIRD_H


class Bird{

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
#endif // BIRD_H
