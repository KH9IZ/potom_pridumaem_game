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
    SimpleBullet(std::basic_string<char, std::char_traits<char>, std::allocator<char>> file, float X, float Y, float W, float H) : Entity(file, X, Y, W, H) { speed = 0.05;}

    void move(double time){

        y -= speed*time;
        sprite.setPosition(x, y);
		//sprite.move(0, speed);
    }
};


#endif
