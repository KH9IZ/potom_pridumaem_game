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
		double w,h,x,y,speed=0;								// ��� ��������� (���� ��������)
		
		Entity(std::string file,double X,double Y)
		{
			w=14; h=14; // ���� ��������
			x=X; y=Y;
			texture.loadFromFile(file);
			sprite.setTexture(texture);
			sprite.setPosition(x,y);
			sprite.setOrigin(x/2,y/2);
		}
		
		FloatRect getRect()
		{
			return FloatRect(sprite.getPosition().x-x/2, sprite.getPosition().y-y/2, w, h);
		}
		
};

#endif
