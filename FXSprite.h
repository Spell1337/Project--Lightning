/* --------------------------------------------------------------- //
   Copyright (C) 2010  Manuel Riecke
   Licensed under the terms of the GNU GPL 2.0
   See Copyright/Code.txt for details.
// --------------------------------------------------------------- */

#ifndef FXSPRITE_H
#define FXSPRITE_H

#include <map>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Sprite.hpp>

class FXSprite
{
public:
  struct FXDefintion
  {
    sf::Image image;
    float frameTime;
    int frameWidth;
    int frameNumber;
  };
public:
  FXSprite(std::string type, float x, float y, float xScale = 1, float yScale = 1, float xDir = 0, float yDir = 0);
  static void RegisterFxType(std::string name, const sf::Image& image, float frameTime, int frameWidth);
  void update(float timeDelta);
  const sf::Sprite& getSprite(){ return mSprite; };
protected:
  sf::Sprite mSprite;
  float mFrameTime;
  int mFrameWidth;
  int mFrameHeight;
  int mFrameNumber;
  float mInternalTimer;
  float mXDir;
  float mYDir;
  static std::map<std::string, FXDefintion> gDefinitions;
};

#endif // FXSPRITE_H
