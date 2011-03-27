
#include <list>

class Enemy;
class Bullet;
extern std::list<Bullet*> gBullets;
void RegisterBullet(Bullet* bullet);
void RemoveBullet(Bullet* bullet);
void RemoveEnemy(Enemy* enemy);
void GameOver();