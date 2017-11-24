#include "Entity.h"
#include "Player.h"
#include "SimpleBullet.h"
#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
	RenderWindow window(VideoMode(800,600), "Potom Pridumaem");
	Event event;
	Clock clock;
    double reload_time;

	Player cmonBruh("cmonBruh.png",0,0,14,14);

	Player entity("chai_pyu.png",400,400,15,15);

    SimpleBullet Bullet("Enemy.png", cmonBruh.x, cmonBruh.y, 14, 14);

    std::vector<SimpleBullet> bullets{};

	while (window.isOpen())
	{
        Bullet.x=cmonBruh.x;
        Bullet.y=cmonBruh.y;
        double time=clock.getElapsedTime().asMicroseconds();
        reload_time += clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time=time/200;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		if (cmonBruh.getRect().intersects(entity.getRect()))
			cmonBruh.sprite.setColor(Color::Red); else cmonBruh.sprite.setColor(Color::White);
        if (Keyboard::isKeyPressed(Keyboard::Space) && (reload_time>=100000)){
            bullets.push_back(Bullet);
            reload_time = 0;
        }
		//cmonBruh.cok();
		cmonBruh.control(time);
        for(int i=0; i<bullets.size(); i++) bullets[i].move(time);
		window.clear();
        for(int i=0; i<bullets.size(); i++) window.draw(bullets[i].sprite);
		window.draw(entity.sprite);
		window.draw(cmonBruh.sprite);
		window.display();
	}

	return 0;
}
