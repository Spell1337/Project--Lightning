/* --------------------------------------------------------------- //
   Copyright (C) 2010  Manuel Riecke
   Licensed under the terms of the GNU GPL 2.0
   See Copyright/Code.txt for details.
// --------------------------------------------------------------- */

#include "Chaser.h"
#include "Player.h"

sf::Image Chaser::gImage;

Chaser::Chaser(float x, float y)
{
  mSprite.SetImage(gImage);
  mSprite.SetPosition(x, y);
  mYDir = 0.0f;
  mInternalTimer = 0.0f;
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
  float ownY=mSprite.GetPosition().y;
  float difference=targetY-ownY;
  float targetYDir=sin(mInternalTimer)*10;
  
  if(difference < -50)
    targetYDir += std::max(difference/20.f, -10.f);
  else if(difference > +50)
    targetYDir += std::min(difference/20.f, +10.f);;
  mYDir = boundby(-100.f, float((mYDir+targetYDir*(timeDelta*4.f))/(1.f+(timeDelta*4.f))), +100.f);
}