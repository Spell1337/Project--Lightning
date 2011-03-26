#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Helpers.h"

int main(int argc, char **argv)
{
  sf::RenderWindow app(sf::VideoMode(800, 600), "Project: Lightning");
  float timeDelta = 0;
  float lastSecond = 0;
  int fps = 0;
  int fpsCounter = 0;
  sf::Clock basicClock;
  sf::String fpsText("FPS: 0", sf::Font::GetDefaultFont(), 12);
  sf::Image playerImg;
  playerImg.LoadFromFile("Player.png");
  sf::Sprite player(playerImg);
  player.SetPosition(400, 300);
  sf::Input& input = app.GetInput();
  
  //sf::Font font;
  //font.LoadFromFile("arial.ttf", 24);
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

    timeDelta=app.GetFrameTime();
    // Show stuff
    app.Clear();
    fpsText.SetText("FPS: "+toString(fps));
    app.Draw(fpsText);
    app.Display();
  }

  return 0;
}


