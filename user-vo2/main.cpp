#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <list>
#include "Entity.h"
#include "Player.h"
#include "SimpleBullet.h"
#include "Enemy.h"
//#include "Hp_bar.h"
//#include "bits/stdc++.h"


std::list<Enemy> enemies{};// list of all enemies on screen
std::list<Enemy>::iterator en ;

using namespace sf;

std::string sound_path = "C:/potom_pridumaem_game/music_and_sound/";  // Music/sound path;
std::string img_path = "C:/potom_pridumaem_game/images/";  // Image path;

Player player(img_path+"player.png",500,350,5,5,100); // Spawn player

//Hp_bar hp_bar_test;

SimpleBullet bullet_left (img_path+"player_bullet.png", player.x, player.y, 5, 5, 0.25); // Create bullet
SimpleBullet bullet_right (img_path+"player_bullet.png", player.x, player.y, 5, 5, 0.25); // Create bullet
SimpleBullet enemy_bullet (img_path+"bullet.png", 0, 0, 5, 5, 0.25);
//Enemy enemy(img_path+"Enemy.png", 50, 50,50, 50, 0.05); // Spawn enemy
Enemy left (img_path+"dt2.png", 100, 100,50, 50, 0.05);
Enemy right (img_path+"dt2.png", 700, 100 ,50, 50, -0.05);
Enemy Boss  (img_path+"Boss.png", 200, 200 ,50, 50, 0);
bool shield=false;
float timer=0;
int score=0;
RenderWindow window{};

Texture texture_Explode;
Sprite sprite_Explode;




float currentFrame = 1.0;

/*void explode(float x,float y){
    currentFrame += 0.5 * timer;
    if (currentFrame>6)
        {
            score+=1000000;// тут что делать после взрыва
        }
    texture_Explode.loadFromFile(img_path + std::to_string(int(currentFrame)) + "stage.png") ;
    sprite_Explode.setTexture(texture_Explode);
    sprite_Explode.setPosition(x,y);
    window.draw(sprite_Explode);
}
*/
bool destroyed (Enemy value)
{
    if (value.hp<=0){
        //explode=true;
        //x_explode=value.x;
        //y_explode=value.y;
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
                en->hp-=1;
                return true;
            } else return false;
        }
    else return value.y < 0 || value.x < 0 || value.x > window.getSize().x || value.y > window.getSize().y;
}


bool is_invisible (SimpleBullet value) {
    if (player.hp!=0)

            //std::advance(en,enemy);
            if (value.y < 0 || value.x < 0 || value.x > window.getSize().x || value.y > window.getSize().y) return true;
            else if (value.sprite.getGlobalBounds().intersects(player.sprite.getGlobalBounds())) {
                // en->sprite.setScale(0, 0);
                player.hp-=1;
                return true;
            } else return false;

    else return value.y < 0 || value.x < 0 || value.x > window.getSize().x || value.y > window.getSize().y;
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
void GameOver()
{
    Texture GO;
    Event event{};
    GO.loadFromFile(img_path+"gameover.png");
    Sprite gameover;
    gameover.setTexture(GO);
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::KeyPressed)
                return;
        }
        window.clear();
        window.draw(gameover);
        window.display();
    }
}
int main(){
	window.create(VideoMode(800, 600), "Potom Pridumaem Game"); // Creating window
	new_start_window();

	Event event{};
	Clock clock;
	float reload_time = 0,reload_time_enemies=0 ,reload_time_portal=0,reload_time_shift=0,shield_timer=0,reload_time_stop=0;
    bullet_left.sprite.setOrigin(25,25);
    bullet_left.sprite.setScale(0.5,0.5);
    bullet_right.sprite.setOrigin(25,25);
    bullet_right.sprite.setScale(0.5,0.5);
    int player_hp=5;
	std::list<SimpleBullet> bullets{}; // list of all bullets on the screen
    std::list<SimpleBullet> enemy_bullets{}; // list of all enemy bullets on the screen
    Music The_Final_Countdown;
    std::string The_Final_Countdown_file=sound_path+"The_Final_Countdown_8_Bit.ogg";
    The_Final_Countdown.openFromFile(The_Final_Countdown_file);
   // The_Final_Countdown.play();
    //The_Final_Countdown.setLoop(true);
    SoundBuffer buffer;
    buffer.loadFromFile(sound_path+"shoot2.ogg");// тут загружаем в буфер что то
    Sound shoot;
    shoot.setBuffer(buffer);

    //background
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

    //работа с боссом
    bool lasors=false;
    Texture lasor_texture;
    Sprite lasor_sprite;
    lasor_texture.loadFromFile(img_path+"lasor.png");
    lasor_sprite.setTexture(lasor_texture);


    //работа с порталами и не только
    Texture portal_texture;
    Sprite portal_sprite;
    std::string Portal_file=img_path+"Portal.png";
    portal_texture.loadFromFile(Portal_file);
    portal_sprite.setTexture(portal_texture);
    float portal_r=0;
    portal_sprite.setOrigin(93, 82);
    portal_sprite.setScale(portal_r,portal_r);
    int count=0;
    float shift=-50,direct=0.05;
    bool portal_close=false,portal_open=false,level2_start=false,first_time=true,level3_start=false,phase_1=true,phase_2=false,phase_3=false;
    std::vector <std::vector <bool>  > asteroid_field (25);
    Texture hp_texture;
    Sprite hp_sprite;
    std::string hp_file = img_path+"hp.png";
    hp_texture.loadFromFile(hp_file);
    hp_sprite.setTexture(hp_texture);

    //работа с полем астероидов
    Texture asteroid_small_texture;
    Sprite asteroid_small_sprite;
    std::string asteroid_small_file=img_path+"asteroid_small.png";
    asteroid_small_texture.loadFromFile(asteroid_small_file);
    asteroid_small_sprite.setTexture(asteroid_small_texture);
    asteroid_small_sprite.setOrigin(250,250);
    asteroid_small_sprite.setScale(0.65,0.65);
    for (int i=1;i<=24;i++){
        int limit=0;
        for (int j=1;j<=16;j++){
            int random=rand()%2;
            if(random==1) {
                if (limit==1){
                    limit=0;
                    asteroid_field[i].push_back(false);
                }
                else {
                    asteroid_field[i].push_back(true);
                    limit++;
                }
            }
            else{
                asteroid_field[i].push_back(false);
            }

        }
    }
    bullet_left.speed_x=0;
    bullet_right.speed_x=0;
    bullet_left.speed_y=-0.25;
    bullet_right.speed_y=-0.25;
    //hp_bar_test.life_bar();
    left.sprite.setOrigin(51,51);
    right.sprite.setOrigin(51,51);
  //  right.sprite.rotate(135);
	while (window.isOpen())
	{
		// Задаём начальную координату пули
		bullet_left.x=player.x+player.texture.getSize().x/2-15;
		bullet_left.y=player.y+player.texture.getSize().y/2-4;
        bullet_right.x=player.x+player.texture.getSize().x/2+15;
        bullet_right.y=player.y+player.texture.getSize().y/2-4;

       // float timer;
		// Работа с временем
        timer=clock.getElapsedTime().asMicroseconds();
		reload_time += clock.getElapsedTime().asMicroseconds();
        reload_time_enemies += clock.getElapsedTime().asMicroseconds();
        reload_time_portal+=clock.getElapsedTime().asMicroseconds();
        reload_time_shift+=clock.getElapsedTime().asMicroseconds();
        reload_time_stop+=clock.getElapsedTime().asMicroseconds();
        if (shield){
            shield_timer+=clock.getElapsedTime().asMicroseconds();
        }
		clock.restart();
		timer=timer/200;

		// Обработка событий
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

        if (Keyboard::isKeyPressed(Keyboard::Z) && (reload_time>=50000)){
            bullets.push_back(bullet_left);
            bullets.push_back(bullet_right);
            shoot.play();
            reload_time = 0;
        }

		player.control(timer);

        if (player.sprite.getGlobalBounds().intersects(asteroid_small_sprite.getGlobalBounds())){
            player.hp--;
            player.sprite.setColor(Color::Red);
        }
        if (player.hp<=0){
            GameOver();
        }
		std::list<SimpleBullet>::iterator it;
        std::list<SimpleBullet>::iterator enbu;
		for(it=bullets.begin(); it != bullets.end(); it++) {
			it->move(timer);
		}
        for(enbu=enemy_bullets.begin(); enbu != enemy_bullets.end(); enbu++) {
            enbu->move(timer);
        }
		bullets.remove_if(is_non_visible);
        enemy_bullets.remove_if(is_invisible);
        //level 1 start

        if((!portal_open) && (portal_r<=1) && (reload_time_portal>=2)){
            portal_sprite.setScale(portal_r,portal_r);
            portal_r+=0.002;
            reload_time_portal=0;
        }
        else{
            portal_open=true;
        }

         if (portal_open) {
            if ((count <10) && (reload_time_enemies >=10000000)) {
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
            en->move_enemy(timer, player.x, player.y);
            en->reload_shoot+=timer*200;
            if (en->reload_shoot>=1000000){
                en->reload_shoot=0;
                enemy_bullet.speed_x=-(en->x-player.x)/(fabsf(en->x-player.x))*0.025;
                enemy_bullet.speed_y=-(en->y-player.y)/(fabsf(en->y-player.y))*0.025;
                enemy_bullet.x=en->x;
                enemy_bullet.y=en->y;
                enemy_bullets.push_back(enemy_bullet);
            }
            //en->sprite.setRotation(en->angle);
        }

        enemies.remove_if(destroyed);


       // level 1 finish

//portal_close=true;

        if (enemies.empty() && portal_close){
            level2_start=true;
        }

        //level 2 start


        if (level2_start) {

            if (reload_time_shift >= 1) {
                reload_time_shift = 0;
                shift+=0.05;
            }
        }
        if (shift>=50){
            level2_start=false;
            level3_start=true;
        }
        //level 2 finish

        //level 3 start
/*
        if (level3_start){
            Boss.move_enemy(timer, 0, 0);
            if (phase_1){
                if (reload_time_stop>=4) {
                    if ((Boss.x>=250) && (Boss.x<=550)){
                        Boss.speed_x=direct;
                    }
                    else{
                        reload_time_stop=0;
                        lasors=true;
                        Boss.x-=direct;
                        direct=-direct;
                    }

                }
                if (Boss.hp<=15000){
                    shield=true;
                    if (shield_timer>=1){
                        shield=false;
                        phase_1=false;
                        phase_2=true;
                        shield_timer=0;
                    }
                }
            }
           // if (phase_2){


           // }
           // if (phase_3){


           // }

        }
*/
        //level 3 finish

        //background
		backgroundS.move(0, 0.05*timer);
		backgroundSR.move(0, 0.05*timer);
		if(backgroundS.getPosition().y>800)
			backgroundS.setPosition(0,-3200);
		if(backgroundSR.getPosition().y>800)
			backgroundSR.setPosition(0,-3200);




		window.clear();
        //draw background
        window.draw(backgroundS);
        window.draw(backgroundSR);



        //draw hp
        for (int i=0;i<player.hp;i++){
            hp_sprite.setPosition(700+i*20,580);
            window.draw(hp_sprite);
        }


        //draw portals
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

        //draw asteroid field
        if (level2_start){

            for (int i=1;i<=24;i++){
                for (int j=1;j<=16;j++){

                    if (first_time){
                        int random=rand()%10;
                        float random_angle=random*36;
                        asteroid_small_sprite.setRotation(random_angle);
                    }

                    if (asteroid_field[i][j]){
                        asteroid_small_sprite.setPosition(j*50-30,(i+shift)*50-25);
                        window.draw(asteroid_small_sprite);
                    }
                  //  if ((player.x==j*50-30) && (player.y==(i+shift)*50-25)){
                   //     player.hp--;
                   //     player.sprite.setColor(Color::Red);
                   // }
                }first_time=false;
            }

        }

        //draw lasors
        if(lasors){
            for (int i=0;i<2;i++){
                for (int k=0;k<=10;k++){
                    lasor_sprite.setPosition(Boss.x+10,Boss.y+k*5);
                    window.draw(lasor_sprite);
                }
            }
        }
        //draw enemies
        for(en=enemies.begin(); en != enemies.end(); en++){
            window.draw(en->sprite);

        }

        if(level3_start){
            window.draw(Boss.sprite);
        }
		for(it=bullets.begin(); it != bullets.end(); it++) window.draw(it->sprite);
        for(enbu=enemy_bullets.begin(); enbu != enemy_bullets.end(); enbu++) window.draw(enbu->sprite);
        //window.draw(hp_bar_test);

		window.draw(player.sprite);
		window.display();
	}
	
	return 0;
}

