//
// Created by knyaz on 12/6/2017.
//

#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <string>
#include "Entity.h"
#include <iostream>



class Enemy : public Entity{
public:
	Enemy(const std::string &file, float X, float Y, float W, float H, float SPEED): Entity(file, X, Y, W, H, SPEED) {}
};


#endif //POTOM_PRIDUMAEM_GAME_ENEMY_H
