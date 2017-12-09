#include <string>
#include <vector>
#include <list>
#include <SFML/Graphics.hpp>
#include "../navipudge666/Entity.h"
#include "../navipudge666/Player.h"
#include "../navipudge666/SimpleBullet.h"

using namespace sf;

std::string img_path;

RenderWindow window(VideoMode(800,600), "Potom Pridumaem");

Player player("player.png",0,0,5,5,1.5/100);

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
};

void BackGroundMove(double time)
{
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

    backgroundS.move(0, 0.017 * time);
    backgroundSR.move(0, 0.017 * time);
    if (backgroundS.getPosition().y > 800)
        backgroundS.setPosition(0, -3200);
    if (backgroundSR.getPosition().y > 800)
        backgroundSR.setPosition(0, -3200);
};

void Menu()
{
    Clock clock;
    Event event{};
    std::string file;
    double reload_time;
    player.x=375; player.y=400;

    SimpleBullet Bullet("bullet.png", player.x, player.y, 5, 5, 0.1);
    std::list<SimpleBullet> bullets{};

    Texture MenuBG; Sprite MenuBGsprite;
    MenuBG.loadFromFile("C:/Games/ppg/potom_pridumaem_game/images/menu.png");
    MenuBGsprite.setTexture(MenuBG);

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
    img_path="C:/Games/ppg/potom_pridumaem_game/images/";
	Event event;
	Clock clock;
    double reload_time;

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


    SimpleBullet Bullet("bullet.png", player.x, player.y, 5, 5, 0.1);
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

        window.clear();
        window.draw(backgroundS);
        window.draw(backgroundSR);
        for(it=bullets.begin(); it != bullets.end(); it++) window.draw(it->sprite);
        window.draw(player.sprite);
        window.display();
    }
	return 0;
}

//