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
	float speed_x=speed, speed_y=speed,reload_shoot=0;
	//float exangle=sprite.getRotation();
	float angle=0;
	int hp=50;
	//bool lol=true;
	//int corner=45;
	//std::cout<<speed_x<<std::endl;
	//float speed_x;float speed_y;
	void move_enemy(float time,float player_x, float player_y){
		//float corner=atan(fabs(speed_x/speed_y)+atan(fabs(player_x-x)/(player_y-y)));
		//if (lol){
		x=sprite.getPosition().x;
		y=sprite.getPosition().y;
		//angle=(atan(((player_x-x)/(player_y-y))))/PI*180;

		//if ((angle<=90) || (angle>=270)){
		//    angle=-angle;
		//}
		//if (angle<0){
		//    angle+=360;
		//}
		//if (angle>180){
		//angle=-angle;
		//}
		//angle=1;

		//}


		//float cornerfloat=corner;
		// speed_x = std::sin(cornerfloat/180*PI)*speed;
		//speed_y = std::cos(cornerfloat/180*PI)*speed;
		//float exx=speed_x, exy=speed_y;
		if(sprite.getPosition().x+h/2 >800 || sprite.getPosition().x-h/2<0) {
			speed_x = -speed_x;
			// sprite.rotate(90);
		}
		if(sprite.getPosition().y+w/2 >600 || sprite.getPosition().y-h/2<0) {
			speed_y = -speed_y;

		}
		angle=atan(speed_x/speed_y)/PI*180;
		//sprite.rotate(((speed_x/exx)*(speed_y/exy))/*speed/2*/*90);
		sprite.move(speed_x*time, speed_y*time);
		//corner = (corner+90)%180;
		std::cout<<angle<<std::endl;
		sprite.setRotation(angle+90);
		//if (lol) {
		//sprite.rotate(exangle);
		//sprite.rotate(angle);
		//lol=false;
		// }
		//exangle=-angle;
	}

};


#endif //POTOM_PRIDUMAEM_GAME_ENEMY_H
