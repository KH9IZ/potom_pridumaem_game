//
// Created by knyaz on 12/6/2017.
//
#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <string>
#include "Entity.h"
#include <iostream>
#include <cmath>
#include <ctime>

#define PI 3.1415



class Enemy : public Entity{
public:
	Enemy(const std::string &file, float X, float Y, float W, float H, float SPEED): Entity(file, X, Y, W, H, SPEED) {}
	float speed_x=speed, speed_y=speed;
    int hp=50;

    //int corner=45;
    //std::cout<<speed_x<<std::endl;
    //float speed_x;float speed_y;
	void move(float time){

        //float cornerfloat=corner;
       // speed_x = std::sin(cornerfloat/180*PI)*speed;
		//speed_y = std::cos(cornerfloat/180*PI)*speed;
        float exx=speed_x, exy=speed_y;
		if(sprite.getPosition().x+h/2 >800 || sprite.getPosition().x-h/2<0) {
			speed_x = -speed_x;
           // sprite.rotate(90);
		}
		if(sprite.getPosition().y+w/2 >600 || sprite.getPosition().y-h/2<0) {
			speed_y = -speed_y;

		}
        sprite.rotate(((speed_x-exx)+(speed_y-exy))/speed/2*90);
		sprite.move(speed_x*time, speed_y*time);
		//corner = (corner+90)%180;
        //std::cout<<speed_x<<' '<<corner<<std::endl;
	}

};


#endif //POTOM_PRIDUMAEM_GAME_ENEMY_H
