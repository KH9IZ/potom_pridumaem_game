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
		Player(std::string file, float X, float Y, float W, float H, float SPEED): Entity(file, X, Y, W, H, SPEED) {}


		void control(double time)
		{
			if (Keyboard::isKeyPressed(Keyboard::Up) && (y-speed*time > -(texture.getSize().y/2-2*h)))
				y -= speed*time;
			if (Keyboard::isKeyPressed(Keyboard::Down) && (y+speed*time < 600-(texture.getSize().y/2+2*h)))
				y += speed*time;
			if (Keyboard::isKeyPressed(Keyboard::Left) && (x-speed*time > -(texture.getSize().x/2-2*w)))
				x -= speed*time;
			if (Keyboard::isKeyPressed(Keyboard::Right) && (x+speed*time <= 800-(texture.getSize().x/2+2*w)))
				x += speed*time;
			if (Keyboard::isKeyPressed(Keyboard::LShift))
				speed=1.5/100;
			else speed=3.75/100;
			sprite.setPosition(x,y);
		}
};

#endif