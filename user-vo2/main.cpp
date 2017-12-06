#include "Entity.h"
//#include "Player.h"
#include "enemy1.h"
#include "SimpleBullet.h"
#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
	//double x1=1,y1=1;

	// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// //////////////////////////// ВСЕМ ПОМЕНЯТЬ !!! ///////////////////////////////////////////////////////////////////
	std::string img_path = "C:/potom_pridumaem_game/images/"; // путь до папки с файламиfawf
	// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	RenderWindow window(VideoMode(800, 600), "Potom Pridumaem Game");
	Event event{};
	Clock clock;
	float reload_time = 0;

//	Player player(img_path+"player.png", 0, 0, 5, 5);
	
//	Player entity(img_path+"Enemy.png", 400, 400, 25, 25);
	
	Enemy enemy(img_path+"Enemy.png",100,300,25,25);
	
//	SimpleBullet Bullet(img_path+"bullet.png", player.x, player.y, 5, 5);

//    std::vector<SimpleBullet> bullets/*{}*/;
	//double speed=0.2;
	//y1= std::cos(45*PI/180)*0.1*1;
	//x1= std::sin(45*PI/180)*0.1*1;
    double corner=45;
    while (window.isOpen())
	{
		// Задаём начальную координату пули
//		Bullet.x=player.x;
//	Bullet.y=player.y;

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
//		if (Keyboard::isKeyPressed(Keyboard::Space) && (reload_time>=50000)){
 //           bullets.push_back(Bullet);
//			reload_time = 0;
//        }
//		if (player.getRect().intersects(entity.getRect()))
//			player.sprite.setColor(Color::Red);
//		else player.sprite.setColor(Color::White);
//		player.control(time);
//		for(int i=0; i<bullets.size(); i++) bullets[i].move(time);
		window.clear();
		
		enemy.gogo(time,corner,300,400);
		window.draw(enemy.sprite);
//        for(int i=0; i<bullets.size(); i++) window.draw(bullets[i].sprite);
//		window.draw(entity.sprite);
//		window.draw(player.sprite);
		window.display();
	}
	
	return 0;
}
