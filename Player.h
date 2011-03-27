/* --------------------------------------------------------------- //
   Copyright (C) 2010  Manuel Riecke
   Licensed under the terms of the GNU GPL 2.0
   See Copyright/Code.txt for details.
// --------------------------------------------------------------- */

#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Image.hpp>

class Player
{
public:
  Player(sf::Image& image, sf::Image& impulse);
  void update(float delta);
  void moveUp(float delta);
  void moveDown(float delta);
  float getY(){ return mSprite.GetPosition().y; };
  const sf::Sprite& getSprite(){ return mSprite; };
  const sf::Sprite& getImpulseSprite(){ return mImpulse; };
  float getLife(){ return mLife;};
  float getEnergy(){ return mEnergyBar;};
  void doLife(float change);
protected:
  float mLife;
  float mEnergyBar;
  float mYDir;
  float mTime;
  sf::Sprite mSprite;
  sf::Sprite mImpulse;
};

#endif // PLAYER_H
