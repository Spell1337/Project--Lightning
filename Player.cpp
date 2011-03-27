/* --------------------------------------------------------------- //
   Copyright (C) 2010  Manuel Riecke
   Licensed under the terms of the GNU GPL 2.0
   See Copyright/Code.txt for details.
// --------------------------------------------------------------- */

#include "Player.h"
#include <cmath>
#include "main.h"

Player::Player(sf::Image& image, sf::Image& impulse)
{
  mLife = 1.0f;
  mEnergyBar = 1.0f;
  mYDir = 0.0f;
  mXAdvancement = 0;
  mSprite.SetImage(image);
  mSprite.SetPosition(250, 400);
  mSprite.SetCenter(image.GetWidth()/2, image.GetHeight()/2);
  mImpulse.SetImage(impulse);
  mImpulse.SetBlendMode(sf::Blend::Add);
}

void Player::update(float delta)
{ 
  mSprite.Move(-mXAdvancement*delta*4, mYDir*delta);
  mXAdvancement-=mXAdvancement*delta*4;
  
  mYDir = mYDir-mYDir*std::min(delta*3, 1.0f);
  mTime+=delta;
  
  int frame=int(mTime*8)%5;
  mImpulse.SetPosition(mSprite.GetPosition()+sf::Vector2f(-60, -25));
  mImpulse.SetSubRect(sf::IntRect(40*frame+1, 0, 40*frame+40, 40));
  
  if(mEnergyBar < 1.0f)
  {
    mEnergyBar+=0.1f*delta;
    if(mEnergyBar>1.0f)
      mEnergyBar=1.0f;
  }
}

void Player::moveDown(float delta)
{
  mYDir += 2000.f*delta;
}

void Player::moveUp(float delta)
{
  mYDir -= 2000.f*delta;
}

void Player::energyBash()
{
  if(mEnergyBar > 0.5f)
  {
    mSprite.SetX(mSprite.GetPosition().x+300);
    mXAdvancement+=300;
    mEnergyBar-=0.4f;
  }
}

void Player::doLife(float change)
{
  mLife+=change;
  if(mLife>1.0f)
    mLife=1.0f;
  else if(mLife<0.0f)
  {
    mLife=0.0f;
    GameOver();
  }
}