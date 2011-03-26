/* --------------------------------------------------------------- //
   Copyright (C) 2010  Manuel Riecke
   Licensed under the terms of the GNU GPL 2.0
   See Copyright/Code.txt for details.
// --------------------------------------------------------------- */

#ifndef BULLET_H
#define BULLET_H
#include <SFML/Graphics/Sprite.hpp>

class Bullet
{
public:
  void update();
  sf::Sprite& getSprite(){ return mSprite; };
protected:
  sf::Sprite mSprite;
};

#endif // BULLET_H
