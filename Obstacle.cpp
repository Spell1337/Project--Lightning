/* --------------------------------------------------------------- //
   Copyright (C) 2010  Manuel Riecke
   Licensed under the terms of the GNU GPL 2.0
   See Copyright/Code.txt for details.
// --------------------------------------------------------------- */

#include "Obstacle.h"
#include <SFML/Graphics/Image.hpp>
#include "Player.h"
#include "Enemy.h"
#include <iostream>

Obstacle::Obstacle(float x, float y, const sf::Image& image)
{
  mSprite.SetImage(image);
  mSprite.SetPosition(x, y);
  mRect = sf::FloatRect(x, y, x+image.GetWidth(), y+image.GetHeight());
  mHitPlayer = false;
}

void Obstacle::update(float delta, float xSpeed)
{
  mSprite.Move(delta*xSpeed, 0);
  mRect.Offset(delta*xSpeed, 0);
}

bool Obstacle::hits(const sf::FloatRect& other)
{
  return mRect.Intersects(other);
}

void Obstacle::hitCheck(Player* player)
{
  if(!mHitPlayer)
  {
    const sf::Vector2f& pos=player->getSprite().GetPosition();
    if(hits(sf::FloatRect(pos.x, pos.y, pos.x+5, pos.y+5)))
    {
      player->doLife(-0.5);
      mHitPlayer=true;
    }
  }
}

void Obstacle::hitCheck(Enemy* enemy)
{
  const sf::Vector2f& pos=enemy->getSprite().GetPosition();
  if(hits(sf::FloatRect(pos.x, pos.y, pos.x+5, pos.y+5)))
    enemy->destroy();
}
