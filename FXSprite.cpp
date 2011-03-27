/* --------------------------------------------------------------- //
   Copyright (C) 2010  Manuel Riecke
   Licensed under the terms of the GNU GPL 2.0
   See Copyright/Code.txt for details.
// --------------------------------------------------------------- */

#include "FXSprite.h"
#include "main.h"

using namespace std;

map<string, FXSprite::FXDefintion> FXSprite::gDefinitions;

FXSprite::FXSprite(string type, float x, float y, float xScale, float yScale, float xDir, float yDir)
{
  const FXDefintion& definition=gDefinitions[type];
  mSprite.SetImage(definition.image);
  mSprite.SetCenter(definition.frameWidth/2, definition.image.GetHeight()/2);
  mSprite.SetPosition(x, y);
  mSprite.SetScale(xScale, yScale);
  //mSprite.SetBlendMode(sf::Blend::Add);
  mFrameNumber=definition.frameNumber;
  mFrameTime=definition.frameTime;
  mFrameWidth=definition.frameWidth;
  mFrameHeight=definition.image.GetHeight();
  mInternalTimer=0.0f;
  mXDir=xDir;
  mYDir=yDir;
}

void FXSprite::update(float timeDelta)
{
  mInternalTimer+=timeDelta;
  int frame=mInternalTimer/mFrameTime;
  mSprite.SetSubRect(sf::IntRect(mFrameWidth*frame+1, 0, mFrameWidth*frame+mFrameWidth, mFrameHeight));
  mSprite.Move(mXDir*timeDelta, mYDir*timeDelta);
  
  if(mInternalTimer > mFrameTime*(mFrameNumber+1))
    RemoveFx(this);
}

void FXSprite::RegisterFxType(string name, const sf::Image& image, float frameTime, int frameWidth)
{
  gDefinitions[name] = FXDefintion{image, frameTime, frameWidth, image.GetWidth()/frameWidth};
}
