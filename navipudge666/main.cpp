#include <string>
#include <vector>
#include <list>
#include <SFML/Graphics.hpp>
#include "../navipudge666/Entity.h"
#include "../navipudge666/Player.h"
#include "../navipudge666/SimpleBullet.h"
#include "../navipudge666/enemy1.h"

using namespace sf;

std::string img_path="C:/Games/ppg/potom_pridumaem_game/images/";

RenderWindow window(VideoMode(800,600), "Potom Pridumaem");

Player player(img_path+"player.png",0,0,5,5,1.5/100);

bool is_non_visible (SimpleBullet value) {return (value.y<0);}

void StartPicture()
{
    Clock clock;
    Event event{};
    std::string file;
    while (window.isOpen()){
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::KeyPressed)
                return;
        }
        int time = int(clock.getElapsedTime().asSeconds());
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
};

void Menu()
{
    Clock clock;
    Event event{};
    std::string file;
    float reload_time;
    player.x=375; player.y=400;

    SimpleBullet Bullet(img_path+"bullet.png", player.x, player.y, 5, 5, 0.1);
    std::list<SimpleBullet> bullets{};

    Texture MenuBG; Sprite MenuBGsprite;
    MenuBG.loadFromFile(img_path+"menu.png");
    MenuBGsprite.setTexture(MenuBG);

    while (window.isOpen())
    {
        Bullet.x=player.x+player.texture.getSize().x/2-4;
        Bullet.y=player.y+player.texture.getSize().y/2-4;
        float time=clock.getElapsedTime().asMicroseconds();
        reload_time += clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time=time/200;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Z) && (reload_time>=50000))
        {
            bullets.push_back(Bullet);
            reload_time = 0;
        }

        if (Keyboard::isKeyPressed((Keyboard::Q)))
            return;

        std::list<SimpleBullet>::iterator it;
        for(it=bullets.begin(); it != bullets.end(); it++)
        {
            it->move(time);
        }
        bullets.remove_if(is_non_visible);
        player.control(time);
        window.clear();
        window.draw(MenuBGsprite);
        window.draw(player.sprite);
        for(it=bullets.begin(); it != bullets.end(); it++) window.draw(it->sprite);
        window.display();
    }
}

int main(){

	Event event;
	Clock clock;
    float reload_time,corner=45;

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

    Enemy enemy(img_path+"Enemy.png",100,100,14,14,0.1);

    SimpleBullet Bullet(img_path+"bullet.png", player.x, player.y, 5, 5, 0.1);
    std::list<SimpleBullet> bullets{};

    StartPicture();
    Menu();
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
        player.control(time);
        std::list<SimpleBullet>::iterator it;
        for(it=bullets.begin(); it != bullets.end(); it++) it->move(time);
        bullets.remove_if(is_non_visible);

        backgroundS.move(0,0.1*time);
        backgroundSR.move(0,0.1*time);
        if(backgroundS.getPosition().y>800)
            backgroundS.setPosition(0,-3200);
        if(backgroundSR.getPosition().y>800)
            backgroundSR.setPosition(0,-3200);

        corner=enemy.gogo(time,corner);
        window.clear();
        window.draw(backgroundS);
        window.draw(backgroundSR);
        window.draw(enemy.sprite);
        for(it=bullets.begin(); it != bullets.end(); it++) window.draw(it->sprite);
        window.draw(player.sprite);
        window.display();
    }
	return 0;
}

//