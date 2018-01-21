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
		Player(std::string file,float X,float Y, float W, float H, float SPEED): Entity(file, X, Y, W, H, SPEED) {}


		void cok()
		{
			std::cout<<x<<' '<<y<<' '<<x-w<<' '<<x+w<<' '<<y-h<<' '<<y+h<<std::endl;
		}

		void control(float time)
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
				speed=1.5/100; else speed=3.75/100;
			sprite.setPosition(x,y);
		}

    void control_inverted(float time)
    {
        if (Keyboard::isKeyPressed(Keyboard::Down) && (y-speed*time > -(texture.getSize().y/2-2*h)))
            y -= speed*time;
        if (Keyboard::isKeyPressed(Keyboard::Up) && (y+speed*time < 600-(texture.getSize().y/2+2*h)))
            y += speed*time;
        if (Keyboard::isKeyPressed(Keyboard::Right) && (x-speed*time > -(texture.getSize().x/2-2*w)))
            x -= speed*time;
        if (Keyboard::isKeyPressed(Keyboard::Left) && (x+speed*time <= 800-(texture.getSize().x/2+2*w)))
            x += speed*time;
        if (Keyboard::isKeyPressed(Keyboard::LShift))
            speed=1.5/100; else speed=3.75/100;
        sprite.setPosition(x,y);
    }

    void control_menu(double time)
    {
        if (Keyboard::isKeyPressed(Keyboard::Up) && (y-speed*time > 230))
            y -= speed*time;
        if (Keyboard::isKeyPressed(Keyboard::Down) && (y+speed*time < 600-(texture.getSize().y/2+2*h)))
            y += speed*time;
        if (Keyboard::isKeyPressed(Keyboard::Left) && (x-speed*time > -(texture.getSize().x/2-2*w)))
            x -= speed*time;
        if (Keyboard::isKeyPressed(Keyboard::Right) && (x+speed*time <= 800-(texture.getSize().x/2+2*w)))
            x += speed*time;
        if (Keyboard::isKeyPressed(Keyboard::LShift))
            speed=1.5/100; else speed=3.75/100;
        sprite.setPosition(x,y);
    }



};

#endif
/*
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
        Player(std::string file,double X,double Y, double W, double H): Entity(file, X, Y, W, H) {}


        void cok()
        {
            std::cout<<x<<' '<<y<<' '<<x-w<<' '<<x+w<<' '<<y-h<<' '<<y+h<<std::endl;
        }

        void control(double time)
        {
            if (Keyboard::isKeyPressed(Keyboard::Up) && (y-speedtime > -(texture.getSize().y/2-h)))
                y -= speedtime;
            if (Keyboard::isKeyPressed(Keyboard::Down) && (y+speedtime < 600-(texture.getSize().y/2-h)))
                y += speedtime;
            if (Keyboard::isKeyPressed(Keyboard::Left) && (x-speedtime > -(texture.getSize().x/2-w)))
                x -= speedtime;
            if (Keyboard::isKeyPressed(Keyboard::Right) && (x+speedtime <= 800-(texture.getSize().x/2-w)))
                x += speedtime;
            if (Keyboard::isKeyPressed(Keyboard::LShift))
                speed=1.5/100; else speed=3.75/100;
            sprite.setPosition(x,y);
        }
};

#endif
 */