/* --------------------------------------------------------------- //
   Copyright (C) 2010  Manuel Riecke
   Licensed under the terms of the GNU GPL 2.0
   See Copyright/Code.txt for details.
// --------------------------------------------------------------- */

#include "Player.h"
#include "FXSprite.h"
#include <cmath>
#include "main.h"

Player::Player(sf::Image& image, sf::Image& impulse)
{
  mLife = 1.0f;
  mEnergyBar = 1.0f;
  mYDir = 0.0f;
  mXAdvancement = 0;
  mDestroyed=false;
  mSprite.SetImage(image);
  mSprite.SetPosition(350, 400);
  mSprite.SetCenter(image.GetWidth()/2, image.GetHeight()/2);
  mImpulse.SetImage(impulse);
  mImpulse.SetBlendMode(sf::Blend::Add);
}

void Player::update(float delta)
{ 
  float xAdvancement=mSprite.GetPosition().x-350;
  mSprite.Move(-xAdvancement*delta*2+mXDir*delta, mYDir*delta);
  
  mYDir = mYDir-mYDir*std::min(delta*3, 1.0f);
  mXDir = mXDir-mXDir*std::min(delta*3, 1.0f);
  mTime+=delta;
  
  int frame=int(mTime*8)%5;
  mImpulse.SetPosition(mSprite.GetPosition()+sf::Vector2f(-60, -25));
  mImpulse.SetSubRect(sf::IntRect(40*frame+1, 0, 40*frame+40, 40));
  
  if(mLife < 1.0f)
  {
    mLife+=0.01f*delta;
    if(mLife>1.0f)
      mLife=1.0f;
  }
  
  if(mEnergyBar < 1.0f)
  {
    mEnergyBar+=1.0f*delta;
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

void Player::moveLeft(float delta)
{
  mXDir -= 1500.f*delta;
}

void Player::moveRight(float delta)
{
  mXDir += 1500.f*delta;
}

void Player::energyDash()
{
  if(mEnergyBar > 0.9f)
  {
    RegisterFx(new FXSprite("EnergyDash", mSprite.GetPosition().x+150, mSprite.GetPosition().y, 3));
    mSprite.SetX(mSprite.GetPosition().x+300);
    mEnergyBar-=0.9f;
    PlaySound("Sound/Psui.wav");
  }
}

void Player::doLife(float change)
{
  if(!mDestroyed)
  {
    mLife+=change;
    if(mLife>1.0f)
      mLife=1.0f;
    else if(mLife<0.0f)
    {
      mLife=0.0f;
      GameOver();
      RegisterFx(new FXSprite("PlrExplosion", mSprite.GetPosition().x, mSprite.GetPosition().y, 5, 5));
      mDestroyed=true;
      PlaySound("Sound/BoomPlayer.wav");
    }
  }
}