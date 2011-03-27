/* --------------------------------------------------------------- //
   Copyright (C) 2010  Manuel Riecke
   Licensed under the terms of the GNU GPL 2.0
   See Copyright/Code.txt for details.
// --------------------------------------------------------------- */

#ifndef CHASER_H
#define CHASER_H

#include "Enemy.h"
#include <SFML/Graphics/Image.hpp>

class Chaser : public Enemy
{
public:
    Chaser(float x, float y);
    virtual void update(float timeDelta, Obstacle* nearestObstacle, Obstacle* secondNearestObstacle);
    static void SetImage(const sf::Image& newImage){ gImage = newImage; };
    static void SetBulletImage(const sf::Image& newImage){ gBulletImg = newImage; };
protected:
    static sf::Image gImage;
    static sf::Image gBulletImg;
    float mYDir;
    float mY;
    float mTargetX;
    float mInternalTimer;
    float mShootTimer;
    float mPersonality;
    float mDistance;
    float mPersonalityX;
};

#endif // CHASER_H
