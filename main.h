
#include <list>
#include <string>

class FXSprite;
class Enemy;
class Bullet;

extern float gSpeed;

void RegisterBullet(Bullet* bullet);
void RemoveBullet(Bullet* bullet);

void RegisterFx(FXSprite* fx);
void RemoveFx(FXSprite* fx);

void RemoveEnemy(Enemy* enemy);

void LoadSound(std::string name);
void PlaySound(std::string name, float volume=1, float pitch=1);

void GameOver();