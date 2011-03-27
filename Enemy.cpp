/* --------------------------------------------------------------- //
   Copyright (C) 2010  Manuel Riecke
   Licensed under the terms of the GNU GPL 2.0
   See Copyright/Code.txt for details.
// --------------------------------------------------------------- */

#include "Enemy.h"
#include "main.h"
#include "Player.h"

void Enemy::destroy()
{
  mTarget->doLife(0.2f);
  RemoveEnemy(this);
}