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
		
		Entity(std::string file,double X,double Y, double W, double H)
		{
			x=X; y=Y; w=W; h=H;
			file = "C:/Games/ppg/potom_pridumaem_game/images/"+file;
			texture.loadFromFile(file);
			sprite.setTexture(texture);
			sprite.setPosition(x,y);
		}
		
		FloatRect getRect()
		{
			return FloatRect(x-w, y-h, w, h);
		}
		
};

#endif
