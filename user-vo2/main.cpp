#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <list>
#include "Entity.h"
#include "Player.h"
#include "SimpleBullet.h"
#include "Enemy.h"


std::list<Enemy> enemies{};// list of all enemies on screen
std::list<Enemy>::iterator en ;

using namespace sf;


std::string img_path = "C:/potom_pridumaem_game/images/";  // Image path;

Player player(img_path+"dt2.png",0,0,5,5,100); // Spawn player

SimpleBullet bullet(img_path+"bullet.png", player.x, player.y, 5, 5, 0.25); // Create bullet

//Enemy enemy(img_path+"Enemy.png", 50, 50,50, 50, 0.05); // Spawn enemy
Enemy left (img_path+"MPW.png", 100, 100,50, 50, 0.05);
Enemy right (img_path+"MPW.png", 700, 100 ,50, 50, -0.05);

RenderWindow window{};

bool destroyed(Enemy value){
    if (value.hp<=0){

        return true;
    }
    return false;
}

bool is_non_visible (SimpleBullet value) {
    for ( std::list<Enemy>::iterator en = enemies.begin() ; en != enemies.end(); en++ ) {
        //std::advance(en,enemy);
        if (value.y < 0 || value.x < 0 || value.x > window.getSize().x || value.y > window.getSize().y) return true;
        else if (value.sprite.getGlobalBounds().intersects(en->sprite.getGlobalBounds())) {
            //enemy.sprite.setScale(0, 0);
            en->hp-=25;
            return true;
        } else return false;
    }
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
	float reload_time = 0,reload_time_enemies=0 ;
	//float corner = 45;


    int count=0;
	std::list<SimpleBullet> bullets{}; // list of all bullets on the screen

   // for (int i=0;i<21;i++){
   //     enemies.push_back(enemy);
   // }


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

    left.sprite.rotate(135);
    right.sprite.rotate(135);
	while (window.isOpen())
	{
		// Задаём начальную координату пули
		bullet.x=player.x+player.texture.getSize().x/2-4;
		bullet.y=player.y+player.texture.getSize().y/2-4;

		// Работа с временем
		float time=clock.getElapsedTime().asMicroseconds();
		reload_time += clock.getElapsedTime().asMicroseconds();
        reload_time_enemies += clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time=time/200;

		// Обработка событий
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

        if  ((count<=10) && (reload_time_enemies>=5000000)){

            enemies.push_back(left);
            enemies.push_back(right);
            reload_time_enemies = 0;count+=2;
        //    std::cout<<enemies.size()<<std::endl;
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

        for (en=enemies.begin(); en != enemies.end(); en++){
            en->move(time);
        }

        enemies.remove_if(destroyed);

		backgroundS.move(0, 0.05*time);
		backgroundSR.move(0, 0.05*time);
		if(backgroundS.getPosition().y>800)
			backgroundS.setPosition(0,-3200);
		if(backgroundSR.getPosition().y>800)
			backgroundSR.setPosition(0,-3200);




		window.clear();
		window.draw(backgroundS);
		window.draw(backgroundSR);
		for(it=bullets.begin(); it != bullets.end(); it++) window.draw(it->sprite);
        for(en=enemies.begin(); en != enemies.end(); en++) window.draw(en->sprite);
		//enemy.move(time);

		window.draw(player.sprite);
		window.display();
	}
	
	return 0;
}
