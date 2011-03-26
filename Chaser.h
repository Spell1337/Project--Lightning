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
    virtual void update(float timeDelta);
    static void SetImage(const sf::Image& newImage){ gImage = newImage; };
protected:
    static sf::Image gImage;
    float mYDir;
    float mY;
    float mInternalTimer;
};

#endif // CHASER_H
