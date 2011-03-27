
#include <list>
#include <string>

class Enemy;
class Bullet;
extern float gSpeed;

void RegisterBullet(Bullet* bullet);
void RemoveBullet(Bullet* bullet);
void RemoveEnemy(Enemy* enemy);
void GameOver();
void LoadSound(std::string name);
void PlaySound(std::string name, float volume=1, float pitch=1);