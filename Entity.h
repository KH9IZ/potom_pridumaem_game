#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

using namespace sf;

class Entity
{
public:
	Texture texture;
	Sprite sprite;
	float w, h, x, y, speed;
	Entity(const std::string &file, float X, float Y, float W, float H)
	{
		x=X; y=Y; w=W; h=H; speed=0.0375;
		texture.loadFromFile(file);
		sprite.setTexture(texture);
		sprite.setOrigin(w/2, h/2);
		sprite.setPosition(x,y);
	}

	FloatRect getRect()
	{
		return FloatRect(x-w, y-h, w, h);
	}

};

#endif
