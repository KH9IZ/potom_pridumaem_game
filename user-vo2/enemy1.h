#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <string>
#include "Entity.h"
#include <iostream>
#include <cmath>

#define PI 3.14159265

using namespace sf;

class Enemy: public Entity {
public:
	Enemy(const std::string &file,float X, float Y, float W, float H): Entity(file, X, Y, W, H) {}


	void gogo(double time, double corner,double x1,double y1)
	{double	y1;
	double	x1;
	y1= std::cos(corner*PI/180)*speed*time;
	x1= std::sin(corner*PI/180)*speed*time;
		if (y-y1 == -h){
			y1= -y1;
		//	y+=y1;
		}
		if  (y+y1 == 600-h){
		
			y1 = -y1;
		//	y+=y1;
		}
		if  (x-x1 == -w){
		
			x1 = -x1;
		//	x+=x1;
		}
		if  ((x+x1 )== 800-w){
			x1 = -x1;
		//	x+=x1;
		}
		x+=x1;
		y+=y1;	
		sprite.setPosition(x,y);
		return x1;
	}
};

#endif

