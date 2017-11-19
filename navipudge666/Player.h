#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <string>
#include "Entity.h"
#include <iostream>

using namespace sf;

class Player: public Entity
{
	public:
		Player(std::string file,double X,double Y): Entity(file, X, Y) {}
		
		
		void cok()
		{
			std::cout<<x<<' '<<y<<' '<<speed<<std::endl;
		}
		
		void control(float time)
		{
			if (Keyboard::isKeyPressed(Keyboard::Up) && (y-speed*time > h))
				y -= speed*time; 
			if (Keyboard::isKeyPressed(Keyboard::Down) && (y+speed*time < 600-h))
				y += speed*time;
			if (Keyboard::isKeyPressed(Keyboard::Left) && (x-speed*time > w))
				x -= speed*time;
			if (Keyboard::isKeyPressed(Keyboard::Right) && (x+speed*time <= 800-w))
				x += speed*time;
			if (Keyboard::isKeyPressed(Keyboard::LShift))
				speed=2.5/100; else speed=3.75/100;
			sprite.setPosition(x,y);
		}
};

#endif
