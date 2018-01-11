#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <list>
#include "Entity.h"
#include "Player.h"
#include "SimpleBullet.h"
#include "Enemy.h"
//#include "bits/stdc++.h"


std::list<Enemy> enemies{};// list of all enemies on screen
std::list<Enemy>::iterator en ;

using namespace sf;


std::string img_path = "C:/potom_pridumaem_game/images/";  // Image path;

Player player(img_path+"player.png",0,0,5,5,100); // Spawn player

SimpleBullet bullet(img_path+"bullet.png", player.x, player.y, 5, 5, 0.25); // Create bullet


//Enemy enemy(img_path+"Enemy.png", 50, 50,50, 50, 0.05); // Spawn enemy
Enemy left (img_path+"dt2.png", 100, 100,50, 50, 0.05);

Enemy right (img_path+"dt2.png", 700, 100 ,50, 50, -0.05);

float timer=0;
int score=0;
RenderWindow window{};

Texture texture_Explode;

float currentFrame = 1.0;

void explode(float x,float y){
    currentFrame += 0.5 * timer;
    if (currentFrame>6)
        {
            score+=1000000;// тут что делать после взрыва
        }
    texture_Explode.loadFromFile(img_path + std::to_string(int(currentFrame)) + "stage.png") ;
}

bool destroyed (Enemy value)
{
    if (value.hp<=0){
        explode(value.x,value.y);
        return true;
    }return false;

}


bool is_non_visible (SimpleBullet value) {
    for ( std::list<Enemy>::iterator en = enemies.begin() ; en != enemies.end(); en++ ) {
        //std::advance(en,enemy);
        if (value.y < 0 || value.x < 0 || value.x > window.getSize().x || value.y > window.getSize().y) return true;
        else if (value.sprite.getGlobalBounds().intersects(en->sprite.getGlobalBounds())) {
            // en->sprite.setScale(0, 0);
            en->hp-=25;
            return true;
        } else return false;
    }
}



//void level(float ,float );



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
	float reload_time = 0,reload_time_enemies=0 ,reload_time_portal=0;

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

    //работа с порталами
    Texture portal_texture;
    Sprite portal_sprite;
    std::string Portal_file=img_path+"Portal.png";
    portal_texture.loadFromFile(Portal_file);
    portal_sprite.setTexture(portal_texture);
    float portal_r=0;
    portal_sprite.setOrigin(93, 82);
    portal_sprite.setScale(portal_r,portal_r);
    int count=0;
    bool portal_close=false,portal_open=false;

    left.sprite.rotate(135);
    right.sprite.rotate(135);
	while (window.isOpen())
	{
		// Задаём начальную координату пули
		bullet.x=player.x+player.texture.getSize().x/2-4;
		bullet.y=player.y+player.texture.getSize().y/2-4;
       // float timer;
		// Работа с временем
        timer=clock.getElapsedTime().asMicroseconds();
		reload_time += clock.getElapsedTime().asMicroseconds();
        reload_time_enemies += clock.getElapsedTime().asMicroseconds();
        reload_time_portal+=clock.getElapsedTime().asMicroseconds();
		clock.restart();
		timer=timer/200;

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

		player.control(timer);

		std::list<SimpleBullet>::iterator it;

		for(it=bullets.begin(); it != bullets.end(); it++) {
			it->move(timer);
		}
		bullets.remove_if(is_non_visible);

        //level 1 start

      /*

      */
        if((!portal_open) && (portal_r<=1) && (reload_time_portal>=2)){
            portal_sprite.setScale(portal_r,portal_r);
            portal_r+=0.002;
            reload_time_portal=0;
        }
        else{
            portal_open=true;
        }

         if (portal_open) {
            if ((count <10) && (reload_time_enemies >= 5000000)) {
                enemies.push_back(left);
                enemies.push_back(right);
                count += 2;
                reload_time_enemies = 0;
            }
         }

        if (count==10){
            portal_close=true;
        }

        for (en=enemies.begin(); en != enemies.end(); en++){
            en->move(timer);
        }

        enemies.remove_if(destroyed);


        //std::cout<<count<<std::endl;

       // level 1 finish



		backgroundS.move(0, 0.05*timer);
		backgroundSR.move(0, 0.05*timer);
		if(backgroundS.getPosition().y>800)
			backgroundS.setPosition(0,-3200);
		if(backgroundSR.getPosition().y>800)
			backgroundSR.setPosition(0,-3200);




		window.clear();

        window.draw(backgroundS);
        window.draw(backgroundSR);

        if (count<=10)  {

              if((portal_close) && (portal_r>=0) && (reload_time_portal>=2)){
                  portal_sprite.setScale(portal_r,portal_r);
                  portal_r-=0.002;
                  reload_time_portal=0;
              }
        portal_sprite.rotate(1);
        portal_sprite.setPosition(100, 100);
        window.draw(portal_sprite);
        portal_sprite.setPosition(700, 100);
        window.draw(portal_sprite);
    }





		for(it=bullets.begin(); it != bullets.end(); it++) window.draw(it->sprite);
        for(en=enemies.begin(); en != enemies.end(); en++) window.draw(en->sprite);
		//enemy.move(time);

		window.draw(player.sprite);
		window.display();
	}
	
	return 0;
}

