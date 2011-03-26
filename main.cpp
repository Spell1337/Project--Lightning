#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Helpers.h"
#include "Player.h"
#include "Enemy.h"
#include "Chaser.h"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768

int main(int argc, char **argv)
{
  sf::RenderWindow app(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Project: Lightning");
  app.UseVerticalSync(true);
  float timeDelta = 0;
  float lastSecond = 0;
  int fps = 0;
  int fpsCounter = 0;
  float score = 0;
  sf::Clock basicClock;
  sf::Font font;
  font.LoadFromFile("Optimus.ttf", 24);
  sf::String scoreText("Score: 0", font, 24);
  scoreText.SetX(8);
  //sf::String fpsText("FPS: 0", font, 24);
  const sf::Input& input = app.GetInput();

  // Da playar
  sf::Image playerImg;
  playerImg.LoadFromFile("Player.png");
  Player player(playerImg);
  
  // Da background
  sf::Image background;
  background.LoadFromFile("Background.png");
  float xPos=0.f;
  
  // Some seperator between foreground and background
  sf::Image darkenerImg;
  darkenerImg.LoadFromFile("Darkener.png");
  sf::Sprite darkener(darkenerImg);
  darkener.SetScale(float(WINDOW_WIDTH)/darkenerImg.GetWidth(), float(WINDOW_HEIGHT)/darkenerImg.GetHeight());
  
  // Enemies
  std::vector<Enemy*> enemies;
  sf::Image chaserImg;
  chaserImg.LoadFromFile("Chaser.png");
  Chaser::SetImage(chaserImg);
  std::vector<int> positions{100, 200, 300, 400, 500, 600};
  foreach(int y, positions)
  {
    Chaser* chaser=new Chaser(sf::Randomizer::Random(0.f, 100.f),  y);
    chaser->setTarget(&player);
    enemies.push_back(chaser);
  }
  
  // Energy bars
  sf::Image liveBarImg;
  liveBarImg.LoadFromFile("LiveBar.png");
  sf::Image liveBarFullImg;
  liveBarFullImg.LoadFromFile("LiveBarFill.png");
  sf::Image energyBarImg;
  energyBarImg.LoadFromFile("EnergyBar.png");
  sf::Image energyBarFullImg;
  energyBarFullImg.LoadFromFile("EnergyBarFill.png");
  
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
    
    xPos+=timeDelta*800.f;
    score+=10.f*timeDelta;
    
    player.update(timeDelta);
    if(input.IsKeyDown(sf::Key::W))
      player.moveUp(timeDelta);
    else if(input.IsKeyDown(sf::Key::S))
      player.moveDown(timeDelta);

    foreach(Enemy* enemy, enemies)
      enemy->update(timeDelta);
    
    timeDelta=app.GetFrameTime();
    
    // Show stuff
    app.Clear();
    
    // Background
    {
      int x=-(int(xPos)%background.GetWidth());
      sf::Sprite bg_spriteA(background);
      bg_spriteA.SetPosition(background.GetWidth()+x, 0.0f);
      sf::Sprite bg_spriteB(background);
      bg_spriteB.SetPosition(x, 0.0f);
      app.Draw(bg_spriteA);
      app.Draw(bg_spriteB);
    }
    
    // Background seperator
    app.Draw(darkener);
    
    // Enemies
    foreach(Enemy* enemy, enemies)
      app.Draw(enemy->getSprite());
    
    // Player
    app.Draw(player.getSprite());
    
    // HUD
    scoreText.SetText("Score: "+toString(score));
    app.Draw(scoreText);
    
    liveBarFill.SetSubRect(sf::IntRect(0, 0, liveBarFullImg.GetWidth()*player.getLife(), liveBarFullImg.GetHeight()));
    app.Draw(liveBarFill);
    app.Draw(liveBar);
    
    energyBarFill.SetSubRect(sf::IntRect(0, 0, energyBarFullImg.GetWidth()*player.getEnergy(), energyBarFullImg.GetHeight()));
    app.Draw(energyBarFill);
    app.Draw(energyBar);
    
    app.Display();
  }
  
  Enemy* enemy;
  foreach(Enemy* enemy, enemies)
    delete enemy;

  return 0;
}


