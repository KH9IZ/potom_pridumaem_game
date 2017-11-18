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
		Player(std::string file,double X,double Y): Entity(file, X, Y) { }
		
		void cok()
		{
			std::cout<<x<<' '<<y<<std::endl;
		}
		
		void control(float time)
		{
			if (Keyboard::isKeyPressed(Keyboard::Up) && (y > h))
				y -= 0.05*time; 
			if (Keyboard::isKeyPressed(Keyboard::Down) && (y < 600-h))
				y += 0.05*time;
			if (Keyboard::isKeyPressed(Keyboard::Left) && (x > w))
				x -= 0.05*time;
			if (Keyboard::isKeyPressed(Keyboard::Right) && (x <= 800-w))
				x += 0.05*time;
			sprite.setPosition(x,y);
		}
};

#endif
