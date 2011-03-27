/* --------------------------------------------------------------- //
   Copyright (C) 2010  Manuel Riecke
   Licensed under the terms of the GNU GPL 2.0
   See Copyright/Code.txt for details.
// --------------------------------------------------------------- */

#include "Chaser.h"
#include "Player.h"
#include <SFML/System.hpp>
#include "Bullet.h"
#include "Obstacle.h"
#include "main.h"

sf::Image Chaser::gImage;
sf::Image Chaser::gBulletImg;

Chaser::Chaser(float x, float y)
{
  mSprite.SetImage(gImage);
  mSprite.SetCenter(gImage.GetWidth()/2, gImage.GetHeight()/2);
  mSprite.SetPosition(x, y);
  mYDir = 0.0f;
  mShootTimer = sf::Randomizer::Random(-2.f, 0.f);
  mInternalTimer = sf::Randomizer::Random(0.f, 20.f);
  mPersonality = sf::Randomizer::Random(-1.f, 1.f);
  mY = y;
}

template<typename A>
A boundby(A min, A val, A max)
{
  if(min > val)
    return min;
  if(max < val)
    return max;
  return val;
}

void Chaser::update(float timeDelta, Obstacle* nearestObstacle, Obstacle* secondNearestObstacle)
{
  mInternalTimer+=timeDelta;
  mShootTimer+=timeDelta;
  if(mShootTimer > 0.6f)
  {
    new Bullet(gBulletImg, mSprite.GetPosition().x, mSprite.GetPosition().y   , 1000, sf::Randomizer::Random(87, 93));
    new Bullet(gBulletImg, mSprite.GetPosition().x, mSprite.GetPosition().y-20, 1000, sf::Randomizer::Random(87, 93));
    mShootTimer=0.f;
  }
  
  mY+=mYDir;
  mSprite.SetY(mY);
  //mSprite.SetColor(sf::Color(255, 255, 255));
  
  float targetY=mTarget->getY();
  static const float checkDistance=gSpeed;
  if(nearestObstacle)
    if(nearestObstacle->hits(sf::FloatRect(mSprite.GetPosition().x, mSprite.GetPosition().y+mYDir, mSprite.GetPosition().x+checkDistance, mSprite.GetPosition().y+50+mYDir)))
    {
      //mSprite.SetColor(sf::Color(255, 0, 0));
      if(!nearestObstacle->hits(sf::FloatRect(mSprite.GetPosition().x, mSprite.GetPosition().y+250, mSprite.GetPosition().x+checkDistance, mSprite.GetPosition().y+300)))
      {
        //mSprite.SetColor(sf::Color(255, 255, 0));
        targetY=mY+300;
      }
      else if(!nearestObstacle->hits(sf::FloatRect(mSprite.GetPosition().x, mSprite.GetPosition().y-250, mSprite.GetPosition().x+checkDistance, mSprite.GetPosition().y-300)))
      {
        //mSprite.SetColor(sf::Color(0, 255, 255));
        targetY=mY-300;
      }
    }
  float difference=(targetY-mY+mPersonality*10);
  
  float targetYDir;
  
  if(difference < -5)
    targetYDir = std::max(-pow(abs(difference)/10., (3.+mPersonality/3)), -12.+mPersonality);
  else if(difference > +5)
    targetYDir = std::min(+pow(abs(difference)/10., (3.+mPersonality/3)), +12.+mPersonality);
  
  if(abs(targetYDir)<4.0)
    targetYDir=0;
  
  if(targetYDir > mYDir)
    mYDir = boundby(mYDir, mYDir+15*timeDelta, targetYDir);
  else
    mYDir = boundby(targetYDir, mYDir-15*timeDelta, mYDir);
}