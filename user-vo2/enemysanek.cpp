#include <SFML/Graphics.hpp>	
#include <iostream>
#include <cmath>
#include "entity.h"
#include "enemy.h"
#include "enemystraight.h"

using namespace sf;

#define PI 3.14159265

int main()
{

	Clock clock;
	float heroteleporttimer = 0; 
	double i=0,x;
//	std::cout << time << "\n";
	RenderWindow window(sf::VideoMode(800, 600), "GETRECT");
 
	EnemySTRAIGHT SANEK1("images/hero2.png",-150,300);
    EnemySTRAIGHT SANEK2("images/hero2.png",400,300);
	while (window.isOpen())
	{
	float time = clock.getElapsedTime().asMicroseconds();
	clock.restart();
	time = time/800;

	
		
 
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)			
			window.close();
			
		}
		
		x=SANEK1.x;	
		window.clear();
		SANEK1.gogo(time);
		SANEK2.gogo(time);
		window.draw(SANEK1.sprite);
		window.draw(SANEK2.sprite);
		window.display();
	}
 
	return 0;
}
