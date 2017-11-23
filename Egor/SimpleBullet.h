//
// Created by knyaz on 23.11.2017.
//

#ifndef SIMPLE_BULLET
#define SIMPLE_BULLET

#include <SFML/Graphics.hpp>
#include <string>
#include "../Egor/Entity.h"
#include <iostream>


class SimpleBullet: public Entity {
public:
    SimpleBullet(const std::string &file, float X, float Y, float W, float H) : Entity(file, X, Y, W, H) {}

    void move(double time){
        y -= speed*time;
        sprite.setPosition(x, y);
    }
};


#endif
