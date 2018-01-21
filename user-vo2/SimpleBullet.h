#ifndef SIMPLE_BULLET
#define SIMPLE_BULLET

#include <SFML/Graphics.hpp>
#include <string>
#include "Entity.h"
#include <iostream>


class SimpleBullet: public Entity {
public:

    SimpleBullet(const std::string &file, float X, float Y, float W, float H, double SPEED) : Entity(file, X, Y, W, H, SPEED) {}

    void move(double time){
        //sprite.setOrigin(])
        y -= speed*time;
        sprite.setPosition(x, y);
    }
};


#endif
