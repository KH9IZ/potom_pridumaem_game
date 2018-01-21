#ifndef SIMPLE_BULLET
#define SIMPLE_BULLET

#include <SFML/Graphics.hpp>
#include <string>
#include "Entity.h"
#include <iostream>
#include <cmath>


class SimpleBullet: public Entity {
public:
    Vector2f direction;
    SimpleBullet(const std::string &file, float X, float Y, float W, float H, double SPEED) : Entity(file, X, Y, W, H, SPEED) {
        direction.x = 0;
        direction.y = -1;
        sprite.setRotation(0);
    }
    SimpleBullet(const std::string &file, float X, float Y, float W, float H, double SPEED, float directionAngle) : Entity(file, X, Y, W, H, SPEED) {
        direction.x = sin(directionAngle);
        direction.y = cos(directionAngle);
        sprite.setRotation(90-directionAngle);
    }

    void move(double time){
        y += speed*time*direction.y;
        x += speed*time*direction.x;
        sprite.setPosition(x, y);
    }
};


#endif
