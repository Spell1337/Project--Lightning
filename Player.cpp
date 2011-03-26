/* --------------------------------------------------------------- //
   Copyright (C) 2010  Manuel Riecke
   Licensed under the terms of the GNU GPL 2.0
   See Copyright/Code.txt for details.
// --------------------------------------------------------------- */

#include "Player.h"
#include <cmath>

Player::Player(sf::Image& image)
{
  mLife = 1.0f;
  mEnergyBar = 1.0f;
  mYDir = 0.0f;
  mSprite.SetImage(image);
  mSprite.SetPosition(200, 400);
}

void Player::update(float delta)
{
  mSprite.Move(0, mYDir*delta);
  mYDir = mYDir-mYDir*std::min(delta*3, 1.0f);
}

void Player::moveDown(float delta)
{
  mYDir += 2000.f*delta;
}

void Player::moveUp(float delta)
{
  mYDir -= 2000.f*delta;
}