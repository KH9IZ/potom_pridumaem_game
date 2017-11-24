#ifndef ENEMYROUND_H
#define ENEMYROUND_H

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <cmath>

#define PI 3.14159265

using namespace sf;

class EnemyROUND
{			
	public:
		Texture texture;
		Sprite sprite;
		double w,h,x,y,speed,i=0;
		int hp;
		bool life;
	
		EnemyROUND (std::string file,double X,double Y)
		{
			x=X+200; y=Y-100;
			texture.loadFromFile(file);
			sprite.setTexture(texture);
			sprite.setPosition(x,y);
			sprite.setOrigin(x/2,y/2);
		}
		
		void gogo (double time){
			sprite.move(std:: cos(i*PI/180)*(-0.2) * time, std:: sin(i*PI/180) * 0.2 * time);
			//std::cout<<cos(i*PI/180)*(-0.2) * time<<' '<<sin(i*PI/180) * 0.2 * time<<std::endl;
			//sprite.setTextureRect(IntRect(0, 96, 96, 96)); 
			i+=1;
		}
		
		FloatRect getRect()
		{
			return FloatRect(sprite.getPosition().x-x/2, sprite.getPosition().y-y/2, w, h);
		}
		
};

#endif
