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
  Player(){};
  Player(sf::Image& image, sf::Image& impulse);
  void update(float delta);
  void moveUp(float delta);
  void moveDown(float delta);
  void moveLeft(float delta);
  void moveRight(float delta);
  void energyDash();
  float getY(){ return mSprite.GetPosition().y; };
  const sf::Sprite& getSprite(){ return mSprite; };
  const sf::Sprite& getImpulseSprite(){ return mImpulse; };
  float getLife(){ return mLife;};
  float getEnergy(){ return mEnergyBar;};
  void doLife(float change);
protected:
  bool mDestroyed;
  float mLife;
  float mEnergyBar;
  float mXDir;
  float mYDir;
  float mTime;
  float mXAdvancement;
  sf::Sprite mSprite;
  sf::Sprite mImpulse;
private:
};

#endif // PLAYER_H
