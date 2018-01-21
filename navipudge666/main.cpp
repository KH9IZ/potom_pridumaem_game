#include <string>
#include <vector>
#include <list>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../navipudge666/Entity.h"
#include "../navipudge666/Player.h"
#include "../navipudge666/SimpleBullet.h"
#include "../navipudge666/Enemy.h"


using namespace sf;

std::string img_path="../images/";

RenderWindow window(VideoMode(800,600), "Potom Pridumaem");

Player player(img_path+"player.png",0,0,5,5,1.5/100);

Enemy left (img_path+"MPW.png", 100, 100,50, 50, 0.05);

Enemy right (img_path+"MPW.png", 700, 100 ,50, 50, -0.05);

float timer=0;
int score=0;

std::list<Enemy> enemies{};// list of all enemies on screen
std::list<Enemy>::iterator en ;

Texture texture_Explode;

float currentFrame = 1.0;

void explode(float x,float y){
    currentFrame += 0.5 * timer;
    if (currentFrame>6)
    {
        score+=1000000;// тут что делать после взрыва
    }
   // texture_Explode.loadFromFile(img_path + std::to_string(int(currentFrame)) + "stage.png") ;
}

bool destroyed (Enemy value)
{
    if (value.hp<=0){
        explode(value.x,value.y);
        return true;
    }return false;

}


bool is_non_visible (SimpleBullet value) {
    if (enemies.size()!=0)
    for ( std::list<Enemy>::iterator en = enemies.begin() ; en != enemies.end(); en++ ) {
        //std::advance(en,enemy);
        if (value.y < 0 || value.x < 0 || value.x > window.getSize().x || value.y > window.getSize().y) return true;
        else if (value.sprite.getGlobalBounds().intersects(en->sprite.getGlobalBounds())) {
            // en->sprite.setScale(0, 0);
            en->hp-=25;
            return true;
        } else return false;
    }
    else return value.y < 0 || value.x < 0 || value.x > window.getSize().x || value.y > window.getSize().y;
}

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
    player.hp=3;
    bool options=false;
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

    Texture empty_hp,hp;
    hp.loadFromFile(img_path+"hp.png");
    empty_hp.loadFromFile(img_path+"empty_hp.png");
    Sprite HP[5];
    for (int i=0; i<5; i++)
    {
        if (i<player.hp)
            HP[i].setTexture(hp);
        else
            HP[i].setTexture(empty_hp);
        HP[i].setPosition(322+33*i,116);
    }
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

        if (Keyboard::isKeyPressed(Keyboard::Z) && (bullets.size()<1))
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
            if (!options && it->sprite.getPosition().y<=136)
            {
                if (it->sprite.getPosition().x>50 && it->sprite.getPosition().x<247)
                    return;
                if (it->sprite.getPosition().x>551 && it->sprite.getPosition().x<747)
                    window.close();
                if (it->sprite.getPosition().x>302 && it->sprite.getPosition().x<497)
                {
                    options=true;
                    MenuBG.loadFromFile(img_path+"options.png");
                    MenuBGsprite.setTexture(MenuBG);
                    bullets.clear();
                    break;
                }
            }
            if (options && it->sprite.getPosition().y<195)
            {
                if (it->sprite.getPosition().x>305 && it->sprite.getPosition().x<355)
                {
                    if (player.hp<5)
                    {
                        player.hp++;
                        HP[player.hp - 1].setTexture(hp);
                    }
                    bullets.clear();
                    break;
                }
                if (it->sprite.getPosition().x>444 && it->sprite.getPosition().x<495)
                {
                    if (player.hp>=2)
                    {
                        HP[player.hp-1].setTexture(empty_hp);
                        player.hp--;
                    }
                    bullets.clear();
                    break;
                }
            }
            if (options && it->sprite.getPosition().y<=136)
            {
                if (it->sprite.getPosition().x>551 && it->sprite.getPosition().x<747)
                {
                    options=false;
                    MenuBG.loadFromFile(img_path+"menu.png");
                    MenuBGsprite.setTexture(MenuBG);
                    bullets.clear();
                    break;
                }
                if (it->sprite.getPosition().x>302 && it->sprite.getPosition().x<497)
                {
                    bullets.clear();
                    break;
                }
            }
        }
        bullets.remove_if(is_non_visible);
        player.control_menu(time);
        window.clear();
        window.draw(MenuBGsprite);
        window.draw(player.sprite);
        if (options)
            for (int i=0; i<5; i++)
                window.draw(HP[i]);
        for(it=bullets.begin(); it != bullets.end(); it++) window.draw(it->sprite);
        window.display();
    }
}

int main(){

	Event event;
	Clock clock;
    float reload_time, reload_time_enemies=0 ,reload_time_portal=0;

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
        reload_time_enemies += clock.getElapsedTime().asMicroseconds();
        reload_time_portal+=clock.getElapsedTime().asMicroseconds();
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


        //level 1 start

        if((!portal_open) && (portal_r<=1) && (reload_time_portal>=2)){
            portal_sprite.setScale(portal_r,portal_r);
            portal_r+=0.0002;
            reload_time_portal=0;
        }
        else{
            portal_open=true;
        }

        if (portal_open) {
            if ((count < 10) && (reload_time_enemies >= 5000000)) {
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
            en->move(time);
        }

        enemies.remove_if(destroyed);

        // level 1 finish

        backgroundS.move(0,0.1*time);
        backgroundSR.move(0,0.1*time);
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

        window.draw(player.sprite);
        window.display();
    }
	return 0;
}

//