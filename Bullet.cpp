/* --------------------------------------------------------------- //
   Copyright (C) 2010  Manuel Riecke
   Licensed under the terms of the GNU GPL 2.0
   See Copyright/Code.txt for details.
// --------------------------------------------------------------- */

#include "Bullet.h"
#include "main.h"
#include <SFML/Graphics/Image.hpp>
#include <SFML/System/Vector2.hpp>
#include "Player.h"

Bullet::Bullet(const sf::Image& image, float x, float y, float dir, float rotation)
{
  mSprite.SetImage(image);
  mSprite.SetPosition(x, y);
  mSprite.SetRotation(rotation);
  mSprite.SetCenter(image.GetWidth()/2, image.GetHeight()/2);
  mDir=sf::Vector2f(sin(rotation*3.14159265/180)*dir, cos(rotation*3.14159265/180)*dir);
  RegisterBullet(this);
}

void Bullet::update(float delta)
{
  mSprite.Move(mDir.x*delta, mDir.y*delta);
}

void Bullet::hitCheck(Player* player)
{
  sf::Vector2f distance=player->getSprite().GetPosition()-mSprite.GetPosition();
  if(abs(distance.x) < 10 && abs(distance.y) < 10)
  {
    player->doLife(-0.05);
    RemoveBullet(this);
  }
}