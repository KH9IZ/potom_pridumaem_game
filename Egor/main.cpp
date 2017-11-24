#include "../Egor/Entity.h"
#include "Player.h"
#include <queue>
#include "SimpleBullet.h"
#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
	RenderWindow window(VideoMode(800, 600), "Potom Pridumaem");
	Event event{};
	Clock clock;
	float reload_time;
    std::string img_path = "C:/Users/knyaz/Documents/My progs/c++/potom_pridumaem_game/Egor/img/"; // путь до папки с файлами
	
	Player cmonBruh(img_path+"cmonBruh.png", 0, 0, 14 ,14);
	
	Player entity(img_path+"chai_pyu.png", 400, 400, 15, 15);

	SimpleBullet sas(img_path+"Bullet.png", cmonBruh.x, cmonBruh.y, 14, 14);

    std::vector<SimpleBullet> bullets{};


    while (window.isOpen())
	{
		float time=clock.getElapsedTime().asMicroseconds();
		reload_time += clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time=time/200;

		//float reload_time = reload_clock.getElapsedTime().asMilliseconds();



		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

		}
        if (Keyboard::isKeyPressed(Keyboard::Space) && (reload_time>=100000)){
            bullets.push_back(SimpleBullet(img_path+"Bullet.png", cmonBruh.x, cmonBruh.y, 14, 14));
			reload_time = 0;
        }
		if (cmonBruh.getRect().intersects(entity.getRect()))
			cmonBruh.sprite.setColor(Color::Red); else cmonBruh.sprite.setColor(Color::White);
		cmonBruh.control(time);
		for(int i=0; i<bullets.size(); i++) bullets[i].move(time);
		window.clear();
        for(int i=0; i<bullets.size(); i++) window.draw(bullets[i].sprite);
		window.draw(entity.sprite);
		window.draw(cmonBruh.sprite);
		window.draw(sas.sprite);
		window.display();
	}
	
	return 0;
}
