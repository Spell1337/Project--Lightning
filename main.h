
#include <list>

class Enemy;
class Bullet;
extern float gSpeed;
void RegisterBullet(Bullet* bullet);
void RemoveBullet(Bullet* bullet);
void RemoveEnemy(Enemy* enemy);
void GameOver();