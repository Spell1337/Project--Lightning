/* --------------------------------------------------------------- //
   Copyright (C) 2010  Manuel Riecke
   Licensed under the terms of the GNU GPL 2.0
   See Copyright/Code.txt for details.
// --------------------------------------------------------------- */

#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Player;

class Enemy
{
public:
  virtual ~Enemy(){};
  virtual void update(float timeDelta)=0;
  void setTarget(Player* target){ mTarget = target; };
  const sf::Sprite& getSprite(){ return mSprite; };
protected:
  Player* mTarget;
  sf::Sprite mSprite;
};

#endif // ENEMY_H
