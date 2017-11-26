#include <string>
#include <vector>
#include <list>
#include <SFML/Graphics.hpp>
#include "../navipudge666/Entity.h"
#include "../navipudge666/Player.h"
#include "../navipudge666/SimpleBullet.h"

using namespace sf;

RenderWindow window(VideoMode(800,600), "Potom Pridumaem");
double start_time=0;
int k=0;

bool is_non_visible (SimpleBullet value) {return (value.y<0);}

void StartPicture()
{

	if ((start_time >= 1.5) && (k < 3))
	{
		k++;
		start_time=0;
	}
	std::vector<std::string> sTextures={"blank.png","potom.png","pridumaem.png","game.png"};
	Texture sTexture;
	sTexture.loadFromFile("C:/Games/ppg/potom_pridumaem_game/images/"+sTextures[k]);
	Sprite sSprite;
	sSprite.setTexture(sTexture);
	sSprite.setScale(1.067, 1.117);
	sSprite.setPosition(0,0);
	window.clear();
	window.draw(sSprite);
	window.display();
};

int main(){
	Event event;
	Clock clock;
    double reload_time;
    bool StartPic=true;

	Player player("player.png",0,0,5,5,1.5/100);

	Player entity("Enemy.png",400,400,50,50,0);

    SimpleBullet Bullet("bullet.png", player.x, player.y, 5, 5, 0.1);

    std::list<SimpleBullet> bullets{};

	while (window.isOpen())
	{


        Bullet.x=player.x+player.texture.getSize().x/2-4;
        Bullet.y=player.y+player.texture.getSize().y/2-4;
        double time=clock.getElapsedTime().asMicroseconds();
        if (StartPic && k!=3)
		    start_time+=clock.getElapsedTime().asSeconds();
        reload_time += clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time=time/200;


		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
            if (event.type == Event::KeyPressed)
                StartPic=false;
		}

        if (StartPic)
        {
            StartPicture();
            continue;
        }

		if (player.getRect().intersects(entity.getRect()))
            player.sprite.setColor(Color::Red); else player.sprite.setColor(Color::White);

        if (Keyboard::isKeyPressed(Keyboard::Z) && (reload_time>=50000)){
            bullets.push_back(Bullet);
            reload_time = 0;
        }
        //cmonBruh.cok();
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