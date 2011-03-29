
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
#include "FXSprite.h"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768

using namespace std;

list<Bullet*> gBullets;
list<Enemy*> gEnemies;
list<Obstacle*> gObstacles;
list<FXSprite*> gEffects;

map<string, sf::SoundBuffer> gSoundBuffer;
map<string, float> gLastPlay;
list<sf::Sound*> gPlayingSounds;

float gTime = 0.0f;
float gSpeed = 800.f;
float gPoints = 0;

int gNumChasers=0;
bool gGameOver=false;

int main(int argc, char **argv)
{
  sf::RenderWindow app(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Project: Lightning");
  app.UseVerticalSync(true);
  float timeDelta = 0;
  float lastSecond = 0;
  int fps = 0;
  int fpsCounter = 0;
  float backgroundAccleration = 20.0f;
  sf::Clock basicClock;
  sf::Font font;
  font.LoadFromFile("Misc/Optimus.ttf", 200);
  sf::String scoreText("Score: 0", font, 24);
  scoreText.SetX(8);
  //sf::String fpsText("FPS: 0", font, 24);
  const sf::Input& input = app.GetInput();

  // Da playar
  sf::Image playerImg;
  playerImg.LoadFromFile("Image/Player.png");
  sf::Image playerImpulseAnim;
  playerImpulseAnim.LoadFromFile("Image/Impulse.png");
  Player player;
  player = Player(playerImg, playerImpulseAnim);
  
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
  
  // Obstacles
  sf::Image obstacleImage;
  obstacleImage.LoadFromFile("Image/Obstacle.png");
  int generatedEnvironment=10000;
  for(int i=1; i<5; i++)
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
  
  // Music
  sf::Music music;
  music.OpenFromFile("Sound/Music.ogg");
  music.SetLoop(true);
  music.Play();
  
  // Sounds
  LoadSound("Sound/Boom.wav");
  LoadSound("Sound/BoomPlayer.wav");
  LoadSound("Sound/Shoot.wav");
  LoadSound("Sound/Psui.wav");
  
  // Special effects
  sf::Image exploImg;
  exploImg.LoadFromFile("Image/Explosion.png");
  FXSprite::RegisterFxType("Explosion", exploImg, 0.05f, 64);
  
  sf::Image playerExploImg;
  playerExploImg.LoadFromFile("Image/ExplosionPlayer.png");
  FXSprite::RegisterFxType("PlrExplosion", playerExploImg, 0.05, 64);
  
  sf::Image playerEnergyDash;
  playerEnergyDash.LoadFromFile("Image/EnergyDash.png");
  FXSprite::RegisterFxType("EnergyDash", playerEnergyDash, 0.05, 100);
  
  // Game over text
  sf::String gameOverTextA("GAME OVER", font, 150);
  gameOverTextA.SetPosition(50, 50);
  sf::String gameOverTextB("", font, 150);
  gameOverTextB.SetPosition(250, 300);
  sf::String gameOverTextC("Press Space to Restart", font, 50);
  gameOverTextC.SetPosition(300, 500);
  
  while(app.IsOpened())
  {
    // Process events
    sf::Event Event;
    while(app.GetEvent(Event))
    {
      if (Event.Type == sf::Event::Closed)
        app.Close();

      if(Event.Type == sf::Event::KeyReleased)
        switch(Event.Key.Code)
        {
          case sf::Key::Escape:
            app.Close();
            break;
          default:
            break;
        }
      
        if(Event.Type == sf::Event::KeyPressed)
          switch(Event.Key.Code)
          {
            case sf::Key::Space:
              if(!gGameOver)
                player.energyDash();
              else if(gGameOver)
              {
                foreach(Enemy* enemy, gEnemies)
                  delete enemy;
                foreach(Bullet* bullet, gBullets)
                  delete bullet;
                foreach(Obstacle* obstacle, gObstacles)
                  delete obstacle;
                foreach(FXSprite* effect, gEffects)
                  delete effect;
                              
                gEnemies.clear();
                gNumChasers=0;
                gBullets.clear();
                gObstacles.clear();
                gEffects.clear();
                
                gGameOver = false;
                xPos = 0;
                player = Player(playerImg, playerImpulseAnim);
                gSpeed = 800.f;
                gPoints = 0;
                
                for(int i=2; i<5; i++)
                {
                  if(sf::Randomizer::Random(0, 1))
                    gObstacles.push_back(new Obstacle(i*2000+sf::Randomizer::Random(0, 300), sf::Randomizer::Random(-600, -400), obstacleImage));
                  if(sf::Randomizer::Random(0, 1))
                    gObstacles.push_back(new Obstacle(i*2000+sf::Randomizer::Random(0, 300), sf::Randomizer::Random(400, 600), obstacleImage));
                }
                generatedEnvironment=10000;
                gTime=0.0f;
              }
              break;
            default:
              break;
          }
    }

    // Calculate stuff
    gTime=basicClock.GetElapsedTime();
    fpsCounter++;
    if(gTime - lastSecond > 1.0)
    {
      lastSecond = gTime;
      fps = fpsCounter;
      fpsCounter = 0;
      
      list<sf::Sound*> temp=gPlayingSounds;
      foreach(sf::Sound* sound, temp)
      {
        if(sound->GetStatus()!=sf::Sound::Playing)
        {
          delete sound;
          gPlayingSounds.remove(sound);
        }
      }
      
      // Generate new environment
      if(xPos > generatedEnvironment)
      {
        for(int i=1; i<10; i++)
        {
          if(!sf::Randomizer::Random(0, 5))
            gObstacles.push_back(new Obstacle(i*2000+sf::Randomizer::Random(0, 300), 0, obstacleImage));
          else
          {
            if(sf::Randomizer::Random(0, 1))
              gObstacles.push_back(new Obstacle(i*2000+sf::Randomizer::Random(0, 300), sf::Randomizer::Random(-600, -400), obstacleImage));
            if(sf::Randomizer::Random(0, 1))
              gObstacles.push_back(new Obstacle(i*2000+sf::Randomizer::Random(0, 300), sf::Randomizer::Random(400, 600), obstacleImage));
          }
          if(sf::Randomizer::Random(0, 1))
            gObstacles.push_back(new Obstacle(i*2000+sf::Randomizer::Random(300, 500), sf::Randomizer::Random(-700, -500), obstacleImage));
          if(sf::Randomizer::Random(0, 1))
            gObstacles.push_back(new Obstacle(i*2000+sf::Randomizer::Random(300, 500), sf::Randomizer::Random(500, 700), obstacleImage));
          
          if(sf::Randomizer::Random(0.f, xPos) > 50000)
          {
            if(sf::Randomizer::Random(0, 1))
              gObstacles.push_back(new Obstacle(i*2000+sf::Randomizer::Random(400, 800), sf::Randomizer::Random(-700, -500), obstacleImage));
            if(sf::Randomizer::Random(0, 1))
              gObstacles.push_back(new Obstacle(i*2000+sf::Randomizer::Random(400, 800), sf::Randomizer::Random(500, 700), obstacleImage));
          }
        }
        generatedEnvironment=xPos+20000;
      }
      
      // Spawn new chasers
      if(gNumChasers < (3+gTime/30.0f))
      {
        Chaser* chaser=new Chaser(sf::Randomizer::Random(0, 200),  sf::Randomizer::Random(0, 500));
        chaser->setTarget(&player);
        gEnemies.push_back(chaser);
        gNumChasers++;
      }
      if(sf::Randomizer::Random(0, 4)==0)
        if(gNumChasers < (5+gTime/15.0f))
        {
          Chaser* chaser=new Chaser(sf::Randomizer::Random(0, 200),  sf::Randomizer::Random(0, 500));
          chaser->setTarget(&player);
          gEnemies.push_back(chaser);
          gNumChasers++;
        }  
    }
    
    xPos+=timeDelta*gSpeed;
    gSpeed+=timeDelta*backgroundAccleration;
    if(!gGameOver)
      gPoints+=10.f*timeDelta+0.0001*xPos*timeDelta;
    
    if(!gGameOver)
    {
      if(input.IsKeyDown(sf::Key::Up))
        player.moveUp(timeDelta);
      else if(input.IsKeyDown(sf::Key::Down))
        player.moveDown(timeDelta);
      
      if(input.IsKeyDown(sf::Key::Left))
        player.moveLeft(timeDelta);
      else if(input.IsKeyDown(sf::Key::Right))
        player.moveRight(timeDelta);
    }
    
    player.update(timeDelta);

    struct { float x; Obstacle* obstacle; } nearestObstacle;
    struct { float x; Obstacle* obstacle; } secondNearestObstacle;
    nearestObstacle.obstacle = NULL;
    nearestObstacle.x = 2000;
    secondNearestObstacle.obstacle = NULL;
    secondNearestObstacle.x = 2000;

    
    list<Obstacle*> tempObstacles=gObstacles;
    foreach(Obstacle* obstacle, tempObstacles)
    {
      obstacle->update(timeDelta, -gSpeed);
      
      float x = obstacle->getX();
      
      if(x < 2000)
        if(x > 0)
        {
          if(x < nearestObstacle.x)
          {
            nearestObstacle.x=x;
            nearestObstacle.obstacle=obstacle;
          }
          else if(x < secondNearestObstacle.x)
          {
            secondNearestObstacle.x=x;
            secondNearestObstacle.obstacle=obstacle;
          }
        }
      
      if(x < 1500)
      {
        obstacle->hitCheck(&player);
        list<Enemy*> tempEnemies=gEnemies;
        foreach(Enemy* enemy, tempEnemies)
          obstacle->hitCheck(enemy);
      }
      
      if(obstacle->getRect().Right < 0)
      {
        gObstacles.remove(obstacle);
        delete obstacle;
      }
    }
    
    foreach(Enemy* enemy, gEnemies)
      enemy->update(timeDelta, nearestObstacle.obstacle, secondNearestObstacle.obstacle);
    
    list<Bullet*> tempBullets=gBullets;
    foreach(Bullet* bullet, tempBullets)
    {
      bullet->update(timeDelta);
      bullet->hitCheck(&player);
    }
    
    list<FXSprite*> tempEffects=gEffects;
    foreach(FXSprite* fx, tempEffects)
      fx->update(timeDelta);
    
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
    if(!gGameOver)
    {
      app.Draw(player.getImpulseSprite());
      app.Draw(player.getSprite());
    }
    
    // Bullets
    foreach(Bullet* bullet, gBullets)
      app.Draw(bullet->getSprite());
    
    // Effects (Explosions and stuff)
    foreach(FXSprite* fx, gEffects)
      app.Draw(fx->getSprite());
    
    // HUD
    scoreText.SetText("Score: "+toString(gPoints));
    app.Draw(scoreText);
    
    app.Draw(liveBar);
    liveBarFill.SetSubRect(sf::IntRect(0, 0, liveBarFullImg.GetWidth()*player.getLife(), liveBarFullImg.GetHeight()));
    app.Draw(liveBarFill);
    
    
    app.Draw(energyBar);
    energyBarFill.SetSubRect(sf::IntRect(0, 0, energyBarFullImg.GetWidth()*player.getEnergy(), energyBarFullImg.GetHeight()));
    app.Draw(energyBarFill);
    
    if(gGameOver)
    {
      app.Draw(gameOverTextA);
      gameOverTextB.SetText(toString(gPoints));
      app.Draw(gameOverTextB);
      app.Draw(gameOverTextC);
    }
    
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

void RegisterFx(FXSprite* fx)
{
  gEffects.push_back(fx);
}

void RemoveFx(FXSprite* fx)
{
  gEffects.remove(fx);
  delete fx;
}

void RemoveEnemy(Enemy* enemy)
{
  gNumChasers--;
  gEnemies.remove(enemy);
  delete enemy;
}

void LoadSound(string name)
{
  gSoundBuffer[name].LoadFromFile(name);
}

void PlaySound(string name, float volume, float pitch)
{
  if(gTime - gLastPlay[name] > 0.2f)
  {
    sf::Sound* sound=new sf::Sound();
    sound->SetBuffer(gSoundBuffer[name]);
    sound->SetVolume(volume*100);
    sound->SetPitch(pitch);
    sound->Play();
    gPlayingSounds.push_back(sound);
    gLastPlay[name]=gTime;
  }
}

void DoPoints(int numPoints)
{
  if(!gGameOver)
    gPoints+=numPoints;
}

void GameOver()
{
  gGameOver=true;
}
