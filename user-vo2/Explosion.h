//
// Created by Евгений on 30.12.2017.
//

#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
//#include <vector>
using namespace sf;

class Explosion {


public:
    Texture texture;
    Sprite sprite;
    int i=1;
    bool explosion_finished=false;
   // std::vector <std::string> v;

    Explosion(const std::string &file, float x,float y)
    {
        std::string str= std::to_string(i);
        std::string file_exp=file+"stage"+str;
        texture.loadFromFile(file_exp);
        sprite.setTexture(texture);
        sprite.setPosition(x,y);

    }
};


#endif //POTOM_PRIDUMAEM_GAME_EXPLOSION_H
