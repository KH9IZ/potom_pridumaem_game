//
// Created by Евгений on 30.12.2017.
//

#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

using namespace sf;

class Explosion {


public:
    Texture texture1,texture2,texture3,texture4,texture5,texture6;
    Sprite sprite1,sprite2,sprite3,sprite4,sprite5,sprite6;

    Explosion(const std::string &file, float x,float y)
    {
        texture1.loadFromFile(file+"stage1");
        texture2.loadFromFile(file+"stage2");
        texture3.loadFromFile(file+"stage3");
        texture4.loadFromFile(file+"stage4");
        texture5.loadFromFile(file+"stage5");
        texture6.loadFromFile(file+"stage6");
        sprite1.setTexture(texture1);
        sprite2.setTexture(texture2);
        sprite3.setTexture(texture3);
        sprite4.setTexture(texture4);
        sprite5.setTexture(texture5);
        sprite6.setTexture(texture6);
        sprite1.setPosition(x,y);
        sprite2.setPosition(x,y);
        sprite3.setPosition(x,y);
        sprite4.setPosition(x,y);
        sprite5.setPosition(x,y);
        sprite6.setPosition(x,y);
    }
};


#endif //POTOM_PRIDUMAEM_GAME_EXPLOSION_H
