#include <string>
#include <vector>
#include <list>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../navipudge666/Entity.h"
#include "../navipudge666/Player.h"
#include "../navipudge666/SimpleBullet1.h"
#include "../navipudge666/Enemy.h"


using namespace sf;

std::string sound_path = "../music_and_sound/";  // Music/sound path;
std::string img_path="../images/";

RenderWindow window(VideoMode(800,600), "Potom Pridumaem");

Player player(img_path+"player.png",0,0,5,5,1.5/100);
SimpleBullet boss_bullet (img_path+"boss_bullet.png", 0, 0, 5, 5, 0.15);

SimpleBullet bullet_left (img_path+"player_bullet.png", player.x, player.y, 5, 5, 0.25); // Create bullet
SimpleBullet bullet_right (img_path+"player_bullet.png", player.x, player.y, 5, 5, 0.25); // Create bullet

SimpleBullet enemy_bullet (img_path+"bullet.png", 0, 0, 5, 5, 0.25);
//Enemy enemy(img_path+"Enemy.png", 50, 50,50, 50, 0.05); // Spawn enemy
Enemy left (img_path+"dt2.png", 100, 100,50, 50, 0.05);
Enemy right (img_path+"dt2.png", 700, 100 ,50, 50, -0.05);
Enemy Boss  (img_path+"Boss.png", 300, 250 ,50, 50, 0.1);
bool shield=false;
float timer=0;
int score=0;


std::list<Enemy> enemies{};// list of all enemies on screen
std::list<Enemy>::iterator en ;

Texture texture_Explode;

float currentFrame = 1.0;

/*
void explode(float x,float y){
    currentFrame += 0.5 * timer;
    if (currentFrame>6)
    {
        score+=1000000;// тут что делать после взрыва
    }
   // texture_Explode.loadFromFile(img_path + std::to_string(int(currentFrame)) + "stage.png") ;
}*/

bool destroyed (Enemy value)
{
    if (value.hp<=0){
        score+=1000000;
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
            en->hp-=5;
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

bool cmp_enemies(Enemy a, Enemy b)
{
    return a.sprite.getPosition().y < b.sprite.getPosition().y;
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
    Bullet.speed_y=-0.1;

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

void GameOver()
{
    Texture GO;
    Event event{};
    GO.loadFromFile(img_path+"gameover.png");
    Sprite gameover;
    gameover.setTexture(GO);
    float time=0; Clock exit;
    while (window.isOpen())
    {

        time=exit.getElapsedTime().asSeconds();
        std::cout<<time<<std::endl;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (time >= 3 && event.type == Event::KeyPressed)
                return;
        }
        window.clear();
        window.draw(gameover);
        window.display();
    }
}

int main(){

	Event event;
	Clock clock;
    float reload_time = 0,reload_time_enemies=0 ,reload_time_portal=0,reload_time_shift=0,shield_timer=0,reload_time_stop=0, player_shield=0,reload_time_boss_bullet=0;

    bullet_left.sprite.setOrigin(25,25);
    bullet_left.sprite.setScale(0.5,0.5);
    bullet_right.sprite.setOrigin(25,25);
    bullet_right.sprite.setScale(0.5,0.5);

    std::list<SimpleBullet> bullets{}; // list of all bullets on the screen
    std::list<SimpleBullet> enemy_bullets{}; // list of all enemy bullets on the screen
    Music The_Final_Countdown;
    std::string The_Final_Countdown_file=sound_path+"The_Final_Countdown_8_Bit.ogg";
    The_Final_Countdown.openFromFile(The_Final_Countdown_file);
    //The_Final_Countdown.play();
  //  The_Final_Countdown.setLoop(true);


    Music randomtrack;
    Music track_1;
    Music track_2;
    Music track_3;
    track_1.openFromFile(sound_path+"track_0.ogg");
    track_2.openFromFile(sound_path+"track_1.ogg");
    track_3.openFromFile(sound_path+"track_2.ogg");
    int track=1;
    SoundBuffer buffer;
    buffer.loadFromFile(sound_path+"shoot.ogg");// тут загружаем в буфер что то
    Sound shoot;
    shoot.setBuffer(buffer);
    SoundBuffer buffer_2;
    buffer_2.loadFromFile(sound_path+"shoot2.ogg");// тут загружаем в буфер что то
    Sound shoot_2;
    shoot.setBuffer(buffer_2);
    track_2.play();
    track_2.setLoop(true);

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
    Boss.sprite.setScale(1,-1);
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
    bool portal_close=false,portal_open=false,level2_start=false,first_time=true,level3_start=false,phase_1=true,phase_2=false,phase_3=false,first_time_boss=true;
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

    Enemy enemy(img_path+"Enemy.png",100,100,14,14,0.1);

    SimpleBullet Bullet(img_path+"bullet.png", player.x, player.y, 5, 5, 0.1);
   // std::list<SimpleBullet> bullets{};

    bullet_left.speed_x=0;
    bullet_right.speed_x=0;
    bullet_left.speed_y=-0.25;
    bullet_right.speed_y=-0.25;
    left.sprite.setOrigin(51,51);
    right.sprite.setOrigin(51,51);

    StartPicture();
    Menu();
    while (window.isOpen())
    {
        while (window.isOpen()) {

            // Задаём начальную координату пули
            bullet_left.x = player.x + player.texture.getSize().x / 2 - 15;
            bullet_left.y = player.y + player.texture.getSize().y / 2 - 4;
            bullet_right.x = player.x + player.texture.getSize().x / 2 + 15;
            bullet_right.y = player.y + player.texture.getSize().y / 2 - 4;

            // Работа с временем
            timer=clock.getElapsedTime().asMicroseconds();
            reload_time += clock.getElapsedTime().asMicroseconds();
            reload_time_enemies += clock.getElapsedTime().asMicroseconds();
            reload_time_portal+=clock.getElapsedTime().asMicroseconds();
            reload_time_shift+=clock.getElapsedTime().asMicroseconds();
            reload_time_stop+=clock.getElapsedTime().asMicroseconds();
            player_shield+=clock.getElapsedTime().asSeconds();
            reload_time_boss_bullet+=clock.getElapsedTime().asSeconds();
            if (shield){
                shield_timer+=clock.getElapsedTime().asMicroseconds();
            }

            clock.restart();
            timer=timer/200;

            // Обработка событий
            while (window.pollEvent(event)) {
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
            enemies.sort((enemies.begin(), enemies.end(), cmp_enemies));
            for(it=bullets.begin(); it != bullets.end(); it++) {
                it->move(timer);
            }
            for(enbu=enemy_bullets.begin(); enbu != enemy_bullets.end(); enbu++) {
                enbu->move(timer);
            }
            bullets.remove_if(is_non_visible);
            enemy_bullets.remove_if(is_invisible);

/*
            //level 1 start

            if ((!portal_open) && (portal_r <= 1) && (reload_time_portal >= 2)) {
                portal_sprite.setScale(portal_r, portal_r);
                portal_r += 0.0002;
                reload_time_portal = 0;
            } else {
                portal_open = true;
            }

            if (portal_open) {
                if ((count < 20) && (reload_time_enemies >= 3000000)) {
                    enemies.push_back(left);
                    enemies.push_back(right);
                    left.speed_x=-left.speed_x;
                    right.speed_x=-right.speed_x;
                    count += 2;
                    reload_time_enemies = 0;
                }
            }

            if (count == 20) {
                portal_close = true;
            }

            for (en=enemies.begin(); en != enemies.end(); en++){
                en->move_enemy(timer,0 ,0);
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

            if (enemies.empty() && portal_close) {
                level2_start = true;
            }

            //level 2 start


            if (level2_start) {

                if (reload_time_shift >= 1) {
                    reload_time_shift = 0;
                    shift+=0.005;
                }
            }
            if (shift>=50){
                level2_start=false;
                level3_start=true;
            }

            //level 2 finish
*/
            //level 3 start

            level3_start=true; phase_1=true;
        if (level3_start)
        {
            if (reload_time_boss_bullet>=4){
                boss_bullet.x=Boss.x;
                boss_bullet.y=Boss.y;
                boss_bullet.speed_y=0.15;
                enemy_bullets.push_back(boss_bullet);

            }

            if (phase_1)
            {
                if ((Boss.speed>0 && Boss.x>600) || (Boss.speed<0 && Boss.x<000))
                    Boss.speed=-Boss.speed;
                Boss.x+=Boss.speed*timer;
                Boss.sprite.setPosition(Boss.x,Boss.y);
            }
           // if (phase_2){


           // }
           // if (phase_3){


           // }

        }

            //level 3 finish

            backgroundS.move(0, 0.1 * timer);
            backgroundSR.move(0, 0.1 * timer);
            if (backgroundS.getPosition().y > 800)
                backgroundS.setPosition(0, -3200);
            if (backgroundSR.getPosition().y > 800)
                backgroundSR.setPosition(0, -3200);

            window.clear();
            window.draw(backgroundS);
            window.draw(backgroundSR);

            //draw enemies
            for (en = enemies.begin(); en != enemies.end(); en++) {
                window.draw(en->sprite);
            }

            //draw hp
            for (int i=0;i<player.hp;i++){
                hp_sprite.setPosition(700+i*20,580);
                window.draw(hp_sprite);
            }


            //draw portals
            if (count <= 20) {

                if ((portal_close) && (portal_r >= 0) && (reload_time_portal >= 2)) {
                    portal_sprite.setScale(portal_r, portal_r);
                    portal_r -= 0.002;
                    reload_time_portal = 0;
                }

                portal_sprite.rotate(1);
                portal_sprite.setPosition(100, 100);
                window.draw(portal_sprite);
                portal_sprite.setPosition(700, 100);
                window.draw(portal_sprite);
            }

            //draw enemies
            for (en = enemies.begin(); en != enemies.end(); en++) {
                window.draw(en->sprite);
            }

            //draw asteroid field
            if (level2_start) {

                for (int i = 1; i <= 24; i++) {
                    for (int j = 1; j <= 16; j++) {

                        if (first_time) {
                            int random = rand() % 10;
                            asteroid_small_sprite.rotate(36 * random);
                        }

                        if (asteroid_field[i][j]) {
                            asteroid_small_sprite.setPosition(j * 50 - 30, (i + shift) * 50 - 25);
                            window.draw(asteroid_small_sprite);
                        }
                    }
                }
                first_time = false;
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

            if(level3_start){
                window.draw(Boss.sprite);
            }
            for(it=bullets.begin(); it != bullets.end(); it++) window.draw(it->sprite);
            for(enbu=enemy_bullets.begin(); enbu != enemy_bullets.end(); enbu++) window.draw(enbu->sprite);

            window.draw(player.sprite);
            window.display();
        }
        GameOver();
        shift = -50;
    }
	return 0;
}

//