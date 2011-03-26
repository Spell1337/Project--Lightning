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
  Player(sf::Image& image);
  void update(float delta);
  void moveUp(float delta);
  void moveDown(float delta);
  const sf::Sprite& getSprite(){ return mSprite; };
protected:
  float mLife;
  float mEnergyBar;
  float mYDir;
  sf::Sprite mSprite;
};

#endif // PLAYER_H
