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
	float speed_x=0.05, speed_y=0.03;

	void move(float time){
		if(sprite.getPosition().x+h/2 >800 || sprite.getPosition().x-h/2<0) speed_x = -speed_x;
		if(sprite.getPosition().y+w/2 >600 || sprite.getPosition().y-h/2<0) {
			speed_y = -speed_y;
		}
		sprite.move(speed_x*time, speed_y*time);
	}
};


#endif //POTOM_PRIDUMAEM_GAME_ENEMY_H
