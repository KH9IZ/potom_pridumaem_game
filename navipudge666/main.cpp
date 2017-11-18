#include "Entity.h"
#include "Player.h"
#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
	RenderWindow window(VideoMode(800,600), "Potom Pridumaem");
	Player cmonBruh("cmonBruh.png",200,200);
	Event event;
	Clock clock;
	
	while (window.isOpen())
	{
		float time=clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time=time/200;
		
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		cmonBruh.cok();
		cmonBruh.control(time);
		window.clear();
		window.draw(cmonBruh.sprite);
		window.display();
	}
	
	return 0;
}
