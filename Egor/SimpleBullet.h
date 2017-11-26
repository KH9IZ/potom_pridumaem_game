#ifndef SIMPLE_BULLET
#define SIMPLE_BULLET

#include <SFML/Graphics.hpp>
#include <string>
#include "Entity.h"
#include <iostream>


class SimpleBullet:  public Entity {
public:
    SimpleBullet(const std::string &file, float X, float Y, float W, float H) : Entity(file, X, Y, W, H) {speed = 0.1;}

    void move(double time){
        y -= speed*time;
        sprite.setPosition(x, y);
    }
};


#endif
