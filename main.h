
#include <list>

class Bullet;
extern std::list<Bullet*> gBullets;
void RegisterBullet(Bullet* bullet);
void RemoveBullet(Bullet* bullet);
void GameOver();