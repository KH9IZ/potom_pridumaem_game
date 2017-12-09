#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <list>
#include "Entity.h"
#include "Player.h"
#include "SimpleBullet.h"
#include "Enemy-my.h"


using namespace sf;


std::string img_path = "C:/Users/knyaz/Documents/My progs/c++/potom_pridumaem_game/images/";  // Image path;

Player player(img_path+"player.png",0,0,5,5,0.0015); // Spawn player

SimpleBullet bullet(img_path+"bullet.png", player.x, player.y, 5, 5, 0.1); // Create bullet

Enemy enemy(img_path+"Enemy.png", 400, 300, 100, 100, 0.1); // Spawn enemy

RenderWindow window{};

bool is_non_visible (SimpleBullet value) {
	if (value.y<0 || value.x<0 || value.x>window.getSize().x || value.y>window.getSize().y) return true;
	else if (value.sprite.getGlobalBounds().intersects(enemy.sprite.getGlobalBounds())) {
		enemy.sprite.setScale(0, 0);
		return true;
	}
	else return false;
}

void new_start_window(){
	Clock clock;
	Event event{};
	std::string file;
	while (window.isOpen()){
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed) return;
		}
		int time = int(clock.getElapsedTime().asSeconds());
		std::cout << time << std::endl;
		if(time<1) file = "blank.png";
		else if(time<2) file = "potom.png";
		else if(time<3) file = "pridumaem.png";
		else file = "game.png";
		Texture sTexture;
		sTexture.loadFromFile(img_path+file);
		Sprite sSprite;
		sSprite.setTexture(sTexture);
		sSprite.setScale(1.067, 1.117);
		sSprite.setPosition(0,0);
		window.clear();
		window.draw(sSprite);
		window.display();
	}
}

int main(){
	window.create(VideoMode(800, 600), "Potom Pridumaem Game"); // Creating window
	new_start_window();

	Event event{};
	Clock clock;
	float reload_time = 0;
	float corner = 45;



	std::list<SimpleBullet> bullets{}; // list of all bullets on the screen



	Texture background, backgroundR;
	Sprite backgroundS, backgroundSR;
	background.loadFromFile(img_path+"background.jpg");
	backgroundS.setTexture(background);
	backgroundS.setScale(0.64,1);
	backgroundS.setPosition(0,-1200);
	backgroundR.loadFromFile(img_path+"background_reversed.png");
	backgroundSR.setTexture(backgroundR);
	backgroundSR.setScale(0.64,1);
	backgroundSR.setPosition(0,-3200);


	while (window.isOpen())
	{
		// Задаём начальную координату пули
		bullet.x=player.x+player.texture.getSize().x/2-4;
		bullet.y=player.y+player.texture.getSize().y/2-4;

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
            bullets.push_back(bullet);
            reload_time = 0;
        }
		player.control(time);
		std::list<SimpleBullet>::iterator it;
		for(it=bullets.begin(); it != bullets.end(); it++) {
			it->move(time);
		}
		bullets.remove_if(is_non_visible);


		backgroundS.move(0, 0.1*time);
		backgroundSR.move(0, 0.1*time);
		if(backgroundS.getPosition().y>800)
			backgroundS.setPosition(0,-3200);
		if(backgroundSR.getPosition().y>800)
			backgroundSR.setPosition(0,-3200);




		window.clear();
		window.draw(backgroundS);
		window.draw(backgroundSR);
		for(it=bullets.begin(); it != bullets.end(); it++) window.draw(it->sprite);
		enemy.move(time);
		window.draw(enemy.sprite);
		window.draw(player.sprite);
		window.display();
	}
	
	return 0;
}
