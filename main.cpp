#include<SDL.h>
#include "Game.h"

// our Game object
int main(int argc, char* argv[])
{
  dani::Game game;
  game.init("Chapter 1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
  while(game.running())
  {
    game.handleEvents();
    game.update();
    game.render();
  }
  game.clean();
  return 0;
}
