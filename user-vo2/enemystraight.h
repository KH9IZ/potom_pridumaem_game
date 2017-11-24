#ifndef ENEMYSTRAIGHT_H
#define ENEMYSTRAIGHT_H

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <cmath>

#define PI 3.14159265

using namespace sf;

class EnemySTRAIGHT
{			
	public:
		Texture texture;
		Sprite sprite;
		double w,h,x,y,speed,i=0;
		int hp;
		bool life,direct;
	
		EnemySTRAIGHT (std::string file,double X,double Y)
		{
			x=X; y=Y;
			texture.loadFromFile(file);
			sprite.setTexture(texture);
			sprite.setPosition(x,y);
			sprite.setOrigin(x/2,y/2);
		}
		
		void gogo (double time){
			if (x==800){
				direct=false;
			//	i=-800;
				}
			if (x==0){
				direct=true;
				}
			if (direct)
				sprite.move(0.2 *time,0);
			else 
				sprite.move(-0.2 *time,0);
			//	i++;
			//std::cout<<cos(i*PI/180)*(-0.2) * time<<' '<<sin(i*PI/180) * 0.2 * time<<std::endl;
			//sprite.setTextureRect(IntRect(0, 96, 96, 96)); 
		}
		
		FloatRect getRect()
		{
			return FloatRect(sprite.getPosition().x-x/2, sprite.getPosition().y-y/2, w, h);
		}
		
};

#endif
