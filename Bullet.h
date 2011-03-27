/* --------------------------------------------------------------- //
   Copyright (C) 2010  Manuel Riecke
   Licensed under the terms of the GNU GPL 2.0
   See Copyright/Code.txt for details.
// --------------------------------------------------------------- */

#ifndef BULLET_H
#define BULLET_H
#include <SFML/Graphics/Sprite.hpp>

class Player;
class Bullet
{
public:
  Bullet(const sf::Image& image, float x, float y, float dir, float rotation = 0);
  void update(float delta);
  void hitCheck(Player* player);
  sf::Sprite& getSprite(){ return mSprite; };
protected:
  sf::Sprite mSprite;
  sf::Vector2f mDir;
};

#endif // BULLET_H
