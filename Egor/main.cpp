#include <SFML/Graphics.hpp>
#include <list>
#include "Entity.h"
#include "Player.h"
#include "SimpleBullet.h"


using namespace sf;

bool is_non_visible (SimpleBullet value) {return (value.y<0);}

int main()
{
	// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// //////////////////////////// ВСЕМ ПОМЕНЯТЬ !!! ///////////////////////////////////////////////////////////////////
	std::string img_path = "C:/Users/knyaz/Documents/My progs/c++/potom_pridumaem_game/images/"; // путь до папки с файлами
	// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	RenderWindow window(VideoMode(800, 600), "Potom Pridumaem Game");
	Event event{};
	Clock clock;
	float reload_time = 0;

	Player player(img_path+"player.png", 0, 0, 5, 5);
	
	Player entity(img_path+"Enemy.png", 400, 400, 25, 25);

	SimpleBullet Bullet(img_path+"bullet.png", player.x, player.y, 5, 5);

    std::list<SimpleBullet> bullets{};


    while (window.isOpen())
	{
		// Задаём начальную координату пули
		Bullet.x=player.x+player.texture.getSize().x/2-4;
		Bullet.y=player.y+player.texture.getSize().y/2-4;

		// Работа с временем
		float time=clock.getElapsedTime().asMicroseconds();
		reload_time += clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time=time/200;

		// Обработка событий
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

		}
		if (Keyboard::isKeyPressed(Keyboard::Z) && (reload_time>=50000)){
            bullets.push_back(Bullet);
			reload_time = 0;
        }
		if (player.getRect().intersects(entity.getRect()))
			player.sprite.setColor(Color::Red);
		else player.sprite.setColor(Color::White);
		player.control(time);
		std::list<SimpleBullet>::iterator it;
		for(it=bullets.begin(); it != bullets.end(); it++) {
			it->move(time);
		}
		bullets.remove_if(is_non_visible);
		window.clear();
		for(it=bullets.begin(); it != bullets.end(); it++) window.draw(it->sprite);
		window.draw(entity.sprite);
		window.draw(player.sprite);
		window.display();
	}
	
	return 0;
}
