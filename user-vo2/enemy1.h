#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <string>
#include "Entity.h"
#include <iostream>
#include <cmath>

#define PI 3.14159265

using namespace sf;

class Enemy: public Entity {
public:
	Enemy(const std::string &file,float X, float Y, float W, float H): Entity(file, X, Y, W, H) {}


    double gogo(double time, double corner,double x,double y)
	{double	y2;
	double	x2;
       //bool mov=false;
	y2= std::cos(corner*PI/180)*speed*time;
	x2= std::sin(corner*PI/180)*speed*time;
      //  std::cout<<x2<<' '<<y2<<std::endl;
      //  if (((y+y2)==-(texture.getSize().y/2-h)) || ((x+x2)== -(texture.getSize().x/2-w))) {
         //   corner = 45 + corner;
         //   mov = true;
         //   y+=y2;
          //  x+=x2;
       // }
       // else if ((y-y2)==600-(texture.getSize().y/2-h)){
        //    corner=90+corner;
         //   mov=true;
         //   y-=y2;
          //  x+=x2;
      //  }
       // else if ((x+x2)>= -(texture.getSize().x/2-w)){
          //  corner=45+corner;
        //    mov=true;
     //       x+=x2;
       //     y+=y2;
     //   }

        //else if ((x-x2)==800-(texture.getSize().x/2-w)){
         //   corner=90-corner;
       //     mov=true;
         //   x-=x2;
        //    y+=y2;
       // }
       // else {
            x+=x2;
            y+=y2;
       // }
       // y2= std::cos(corner*PI/180)*speed*time;
       // x2= std::sin(corner*PI/180)*speed*time;

            sprite.setPosition(x,y);

        std::cout<<x2<<' '<<y2<<std::endl;
        return corner;
	}
};

#endif

