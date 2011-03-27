/* --------------------------------------------------------------- //
   Copyright (C) 2010  Manuel Riecke
   Licensed under the terms of the GNU GPL 2.0
   See Copyright/Code.txt for details.
// --------------------------------------------------------------- */

#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <SFML/Graphics/Sprite.hpp>

class Player;
class Enemy;

class Obstacle
{
public:
  Obstacle(float x, float y, const sf::Image& image);
  const sf::FloatRect& getRect();
  void update(float delta, float xSpeed);
  bool hits(const sf::FloatRect& other);
  void hitCheck(Player* player);
  void hitCheck(Enemy* enemy);
  const sf::Sprite& getSprite(){ return mSprite; };
  float getX(){ return mRect.Left; };
protected:
  sf::Sprite mSprite;
  sf::FloatRect mRect;
  bool mHitPlayer;
};

#endif // OBSTACLE_H
