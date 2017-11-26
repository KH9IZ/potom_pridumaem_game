#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "../navipudge666/Entity.h"
#include "../navipudge666/Player.h"
#include "../navipudge666/SimpleBullet.h"

using namespace sf;

RenderWindow window(VideoMode(800,600), "Potom Pridumaem");
double start_time;

void StartPicture()
{
	int k=0;
	if ((start_time >= 1500) && (k < 4))
	{
		k++;
		start_time=0;
	}
	std::vector<std::string> sTextures={"blank.png","potom.png","pridumaem.png","game.png"};
	Texture sTexture;
	sTexture.loadFromFile(sTextures[k]);
	Sprite sSprite;
	sSprite.setTexture(sTexture);
    sSprite.setPosition(0,0);
	window.clear();
	window.draw(sSprite);
	window.display();
};

int main(){
	Event event;
	Clock clock;
    double reload_time;

	Player player("player.png",0,0,5,5,1.5/100);

	Player entity("Enemy.png",400,400,50,50,0);

    SimpleBullet Bullet("bullet.png", player.x, player.y, 5, 5, 0.1);

    std::vector<SimpleBullet> bullets{};

	while (window.isOpen())
	{
		bool StartPic=true;

        Bullet.x=player.x+player.texture.getSize().x/2-4;
        Bullet.y=player.y+player.texture.getSize().y/2-4;
        double time=clock.getElapsedTime().asMicroseconds();
		start_time+=clock.getElapsedTime().asMicroseconds();
        reload_time += clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time=time/200;

		if (!Keyboard::isKeyPressed(Keyboard::Unknown))
		{
			StartPicture();
			continue;
		}

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