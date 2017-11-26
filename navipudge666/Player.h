#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <string>
#include "../Egor/Entity.h"
#include <iostream>

using namespace sf;

class Player: public Entity {
public:
	Player(const std::string &file,float X, float Y, float W, float H): Entity(file, X, Y, W, H) {}


	void control(double time)
	{
		if (Keyboard::isKeyPressed(Keyboard::Up) && (y-speed*time > -h))
			y -= speed*time;
		if (Keyboard::isKeyPressed(Keyboard::Down) && (y+speed*time < 600-h))
			y += speed*time;
		if (Keyboard::isKeyPressed(Keyboard::Left) && (x-speed*time > -w))
			x -= speed*time;
		if (Keyboard::isKeyPressed(Keyboard::Right) && (x+speed*time <= 800-w))
			x += speed*time;
		if (Keyboard::isKeyPressed(Keyboard::LShift))
			speed=0.025;
		else speed=0.0375;
		sprite.setPosition(x,y);
	}
};

#endif
