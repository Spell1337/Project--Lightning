/* --------------------------------------------------------------- //
   Copyright (C) 2010  Manuel Riecke
   Licensed under the terms of the GNU GPL 2.0
   See Copyright/Code.txt for details.
// --------------------------------------------------------------- */

#include "Chaser.h"
#include "Player.h"
#include <SFML/System.hpp>

sf::Image Chaser::gImage;

Chaser::Chaser(float x, float y)
{
  mSprite.SetImage(gImage);
  mSprite.SetPosition(x, y);
  mYDir = 0.0f;
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

void Chaser::update(float timeDelta)
{
  mInternalTimer+=timeDelta;
  mY+=mYDir;
  mSprite.SetY(mY);
  
  float targetY=mTarget->getY();
  float difference=(targetY-mY+mPersonality*10);
  float targetYDir;
  
  if(difference < -5)
    targetYDir = std::max(-pow(abs(difference)/10., (3.+mPersonality/3)), -6.+mPersonality);
  else if(difference > +5)
    targetYDir = std::min(+pow(abs(difference)/10., (3.+mPersonality/3)), +6.+mPersonality);
  
  if(abs(targetYDir)<2.0)
    targetYDir=0;
  
  if(targetYDir > mYDir)
    mYDir = boundby(mYDir, mYDir+10*timeDelta, targetYDir);
  else
    mYDir = boundby(targetYDir, mYDir-10*timeDelta, mYDir);
}