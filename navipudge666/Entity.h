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
		double w,h,x,y,speed;
		int hp;
		bool life;
		
		Entity(std::string file,double X,double Y, double W, double H, double SPEED)
		{
			x=X; y=Y; w=W; h=H; speed=SPEED;
			file = "C:/Games/ppg/potom_pridumaem_game/images/"+file;
            texture.loadFromFile(file);
			sprite.setTexture(texture);
			sprite.setPosition(x,y);
		}
		FloatRect getRect()
		{
			return FloatRect(x+texture.getSize().x/2-w, y+texture.getSize().y/2-h, 2*w, 2*h);
		}
		
};

#endif