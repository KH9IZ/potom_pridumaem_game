#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <string>
#include "Entity.h"
#include <iostream>
#include <cmath>
#include <ctime>

#define PI 3.14159265

using namespace sf;

class Enemy: public Entity {
public:
	Enemy(const std::string &file,float X, float Y, float W, float H, double SPEED): Entity(file, X, Y, W, H, SPEED) {}


    double gogo(double time, double corner)
	{double	y2;
	double	x2;
       bool mov=false;
	y2= std::cos(corner/180*PI)*speed*time;
	x2= std::sin(corner/180*PI)*speed*time;
        if (((y - y2) <= -(texture.getSize().y / 2 - 2*h)) || ((y + y2) >= 600 - (texture.getSize().y / 2 - 2*h))) {
               mov = true;

               y2=-y2;
           }
        if (((x - x2) <= -(texture.getSize().x / 2 - 2*w)) || ((x + x2) >= 800 - (texture.getSize().x / 2 - 2*w))){
               mov=true;
               x2=-x2;
           }
        if (x>= 800 - (texture.getSize().x / 2 - 2*w)){
            x=800 - (texture.getSize().x / 2 - 2*w)*speed;
        }
        if (x <= -(texture.getSize().x / 2 - 2*w)){
            x= - (texture.getSize().x / 2 - 2*w)*speed;
        }
        if (y>= 600 - (texture.getSize().y / 2 - 2*h)){
            y= 600 - (texture.getSize().y / 2 - 2*h)*speed;
        }
        if (y<= -(texture.getSize().y / 2 - 2*h)){
            y= -(texture.getSize().y / 2 - 2*h)*speed;
        }
            x+=x2;
            y+=y2;
        if (mov){
            if (rand() % 2==0){
                corner+=90;
            }
            else{
                corner-=90;
            }
        }
            sprite.setPosition(x,y);
        return corner;
	}
};

#endif

