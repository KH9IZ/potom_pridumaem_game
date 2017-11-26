#include "../navipudge666/Entity.h"
#include "../navipudge666/Player.h"
#include "SimpleBullet.h"
#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
	RenderWindow window(VideoMode(800,600), "Potom Pridumaem");
	Event event;
	Clock clock;
    double reload_time;

	Player player("player.png",0,0,5,5);

	Player entity("Enemy.png",400,400,50,50);

    SimpleBullet Bullet("bullet.png", player.x, player.y, 5, 5);

    std::vector<SimpleBullet> bullets{};

	while (window.isOpen())
	{
        Bullet.x=player.x+player.texture.getSize().x/2-4;
        Bullet.y=player.y+player.texture.getSize().y/2-4;
        double time=clock.getElapsedTime().asMicroseconds();
        reload_time += clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time=time/200;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		if (player.getRect().intersects(entity.getRect()))
            player.sprite.setColor(Color::Red); else player.sprite.setColor(Color::White);
        if (Keyboard::isKeyPressed(Keyboard::Z) && (reload_time>=50000)){
            bullets.push_back(Bullet);
            reload_time = 0;
        }
		//cmonBruh.cok();
        player.control(time);
        for(int i=0; i<bullets.size(); i++) bullets[i].move(time);
		window.clear();
        for(int i=0; i<bullets.size(); i++) window.draw(bullets[i].sprite);
		window.draw(entity.sprite);
		window.draw(player.sprite);
		window.display();
	}

	return 0;
}
