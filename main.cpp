
#include "main.h"
#include <list>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Helpers.h"
#include "Player.h"
#include "Enemy.h"
#include "Chaser.h"
#include "Bullet.h"
#include "Obstacle.h"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768

using namespace std;

list<Bullet*> gBullets;
list<Enemy*> gEnemies;
list<Obstacle*> gObstacles;

int main(int argc, char **argv)
{
  sf::RenderWindow app(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Project: Lightning");
  app.UseVerticalSync(true);
  float timeDelta = 0;
  float lastSecond = 0;
  int fps = 0;
  int fpsCounter = 0;
  float score = 0;
  float backgroundSpeed = 1400.f;
  sf::Clock basicClock;
  sf::Font font;
  font.LoadFromFile("Misc/Optimus.ttf", 24);
  sf::String scoreText("Score: 0", font, 24);
  scoreText.SetX(8);
  //sf::String fpsText("FPS: 0", font, 24);
  const sf::Input& input = app.GetInput();

  // Da playar
  sf::Image playerImg;
  playerImg.LoadFromFile("Image/Player.png");
  sf::Image playerImpulseAnim;
  playerImpulseAnim.LoadFromFile("Image/Impulse.png");
  Player player(playerImg, playerImpulseAnim);
  
  // Da background
  sf::Image background;
  background.LoadFromFile("Image/Background.png");
  float xPos=0.f;
  
  // Some seperator between foreground and background
  sf::Image darkenerImg;
  darkenerImg.LoadFromFile("Image/Darkener.png");
  sf::Sprite darkener(darkenerImg);
  darkener.SetScale(float(WINDOW_WIDTH)/darkenerImg.GetWidth(), float(WINDOW_HEIGHT)/darkenerImg.GetHeight());
  
  // Enemies
  sf::Image chaserImg;
  chaserImg.LoadFromFile("Image/Chaser.png");
  sf::Image bulletImg;
  bulletImg.LoadFromFile("Image/Bullet.png");
  Chaser::SetImage(chaserImg);
  Chaser::SetBulletImage(bulletImg);
  std::vector<int> positions{100, 300, 500};
  foreach(int y, positions)
  {
    Chaser* chaser=new Chaser(y/4,  y);
    chaser->setTarget(&player);
    gEnemies.push_back(chaser);
  }
  
  // Obstacles
  sf::Image obstacleImage;
  obstacleImage.LoadFromFile("Image/Obstacle.png");
  for(int i=0; i<50; i++)
  {
    if(sf::Randomizer::Random(0, 1))
      gObstacles.push_back(new Obstacle(i*2000+sf::Randomizer::Random(0, 300), sf::Randomizer::Random(-600, -400), obstacleImage));
    if(sf::Randomizer::Random(0, 1))
      gObstacles.push_back(new Obstacle(i*2000+sf::Randomizer::Random(0, 300), sf::Randomizer::Random(400, 600), obstacleImage));
  }
  
  // Energy bars
  sf::Image liveBarImg;
  liveBarImg.LoadFromFile("Image/LiveBar.png");
  sf::Image liveBarFullImg;
  liveBarFullImg.LoadFromFile("Image/LiveBarFill.png");
  sf::Image energyBarImg;
  energyBarImg.LoadFromFile("Image/EnergyBar.png");
  sf::Image energyBarFullImg;
  energyBarFullImg.LoadFromFile("Image/EnergyBarFill.png");
  
  sf::Sprite liveBar(liveBarImg);
  sf::Sprite liveBarFill(liveBarFullImg);
  liveBar    .SetPosition(20, WINDOW_HEIGHT-120);
  liveBarFill.SetPosition(20, WINDOW_HEIGHT-120);
  liveBarFill.SetBlendMode(sf::Blend::Add);
  
  sf::Sprite energyBar(energyBarImg);
  sf::Sprite energyBarFill(energyBarFullImg);
  energyBar    .SetPosition(20, WINDOW_HEIGHT-60);
  energyBarFill.SetPosition(20, WINDOW_HEIGHT-60);
  energyBarFill.SetBlendMode(sf::Blend::Add);
  
  while(app.IsOpened())
  {
    // Process events
    sf::Event Event;
    while(app.GetEvent(Event))
    {
      if (Event.Type == sf::Event::Closed)
        app.Close();

      if(Event.Type == sf::Event::KeyReleased)
      {
        switch(Event.Key.Code)
        {
          case sf::Key::Escape:
            app.Close();
            break;
          default:
            break;
        }
      }
    }

    // Calculate stuff
    float curTime=basicClock.GetElapsedTime();
    fpsCounter++;
    if(curTime - lastSecond > 1.0)
    {
      lastSecond = curTime;
      fps = fpsCounter;
      fpsCounter = 0;
    }
    
    xPos+=timeDelta*backgroundSpeed;
    score+=10.f*timeDelta;
    
    if(input.IsKeyDown(sf::Key::W))
      player.moveUp(timeDelta);
    else if(input.IsKeyDown(sf::Key::S))
      player.moveDown(timeDelta);
    player.update(timeDelta);

    foreach(Obstacle* obstacle, gObstacles)
    {
      obstacle->update(timeDelta, -backgroundSpeed);
      if(obstacle->getX() < 400)
      {
        obstacle->hitCheck(&player);
        list<Enemy*> tempEnemies=gEnemies;
        foreach(Enemy* enemy, tempEnemies)
          obstacle->hitCheck(enemy);
      }
    }
    
    foreach(Enemy* enemy, gEnemies)
      enemy->update(timeDelta);
    
    list<Bullet*> tempBullets=gBullets;
    foreach(Bullet* bullet, tempBullets)
    {
      bullet->update(timeDelta);
      bullet->hitCheck(&player);
    }
    
    timeDelta=app.GetFrameTime();
    
    // Show stuff
    app.Clear();
    
    // Background
    {
      int x= (-(int(xPos/6)%background.GetWidth()));
      sf::Sprite bg_spriteA(background);
      bg_spriteA.SetPosition(background.GetWidth()+x, 0.0f);
      sf::Sprite bg_spriteB(background);
      bg_spriteB.SetPosition(x, 0.0f);
      app.Draw(bg_spriteA);
      app.Draw(bg_spriteB);
    }
    
    // Background seperator
    app.Draw(darkener);
    
    // Obstacles
    foreach(Obstacle* obstacle, gObstacles)
      app.Draw(obstacle->getSprite());
    
    // Enemies
    foreach(Enemy* enemy, gEnemies)
      app.Draw(enemy->getSprite());
    
    // Player
    app.Draw(player.getImpulseSprite());
    app.Draw(player.getSprite());
    
    // Bullets
    foreach(Bullet* bullet, gBullets)
      app.Draw(bullet->getSprite());
    
    // HUD
    scoreText.SetText("Score: "+toString(score));
    app.Draw(scoreText);
    
    app.Draw(liveBar);
    liveBarFill.SetSubRect(sf::IntRect(0, 0, liveBarFullImg.GetWidth()*player.getLife(), liveBarFullImg.GetHeight()));
    app.Draw(liveBarFill);
    
    
    app.Draw(energyBar);
    energyBarFill.SetSubRect(sf::IntRect(0, 0, energyBarFullImg.GetWidth()*player.getEnergy(), energyBarFullImg.GetHeight()));
    app.Draw(energyBarFill);
    
    app.Display();
  }
  
  foreach(Enemy* enemy, gEnemies)
    delete enemy;
  foreach(Bullet* bullet, gBullets)
    delete bullet;
  foreach(Obstacle* obstacle, gObstacles)
    delete obstacle;

  return 0;
}

void RegisterBullet(Bullet* bullet)
{
  gBullets.push_back(bullet);
}

void RemoveBullet(Bullet* bullet)
{
  gBullets.remove(bullet);
  delete bullet;
}

void RemoveEnemy(Enemy* enemy)
{
  gEnemies.remove(enemy);
  delete enemy;
}

void GameOver()
{
  //cout << "Game over" << endl;
}
