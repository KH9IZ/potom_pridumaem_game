#include "../Egor/Entity.h"
#include "Player.h"
#include "SimleBullet.h"
#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
	RenderWindow window(VideoMode(800, 600), "Potom Pridumaem");
	Event event{};
	Clock clock;
    std::string img_path = "C:/Users/knyaz/Documents/My progs/c++/potom_pridumaem_game/Egor/img/"; // путь до папки с файлами
	
	Player cmonBruh(img_path+"cmonBruh.png", 0, 0, 14 ,14);
	
	Player entity(img_path+"chai_pyu.png", 400, 400, 15, 15);


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
		if (cmonBruh.getRect().intersects(entity.getRect()))
			cmonBruh.sprite.setColor(Color::Red); else cmonBruh.sprite.setColor(Color::White);
		cmonBruh.control(time);
		window.clear();
		window.draw(entity.sprite);
		window.draw(cmonBruh.sprite);
		window.display();
	}
	
	return 0;
}
