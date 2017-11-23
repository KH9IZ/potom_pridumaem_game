//
// Created by knyaz on 23.11.2017.
//

#ifndef SIMPLE_BULLET
#define SIMPLE_BULLET

#include <SFML/Graphics.hpp>
#include <string>
#include "../Egor/Entity.h"
#include <iostream>


class SimleBullet: public Entity {
public:
    SimleBullet(const std::string &file, double X, double Y, double W, double H) : Entity(file, X, Y, W, H) {}

    void move(double time){
        if (Keyboard::isKeyPressed(Keyboard::Space) && (y-speed*time > -h))
            y -= speed*time;
        sprite.setPosition(x, y);
    }
};


#endif //POTOM_PRIDUMAEM_GAME_SIMLEBULLET_H
