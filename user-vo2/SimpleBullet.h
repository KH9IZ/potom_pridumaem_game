#ifndef SIMPLE_BULLET
#define SIMPLE_BULLET

#include <SFML/Graphics.hpp>
#include <string>
#include "Entity.h"
#include <iostream>


class SimpleBullet: public Entity {
public:

    SimpleBullet(const std::string &file, float X, float Y, float W, float H, double SPEED) : Entity(file, X, Y, W, H, SPEED) {}
    double speed_x,speed_y;
    void move(double time/*, float speed_x,float speed_y*/){
        //sprite.setOrigin
        x +=speed_x*time;
        y +=speed_y*time;
        sprite.setPosition(x, y);
    }
};


#endif
