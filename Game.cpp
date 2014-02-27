#include "Game.h"
#include <SDL.h>
#include <iostream>

namespace dani
{
  Game::Game()
  {
    m_bRunning = true;
  }

  Game::~Game()
  {
  }


  void Game::render()
  {
    // set to black
    SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
    // clear the window to black
    SDL_RenderClear(m_pRenderer);
    // show the window
    SDL_RenderPresent(m_pRenderer);
  }

  void Game::clean()
  {
    std::cout << "cleaning game\n";
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    SDL_Quit();
  }
  void Game::handleEvents()
  {
    SDL_Event event;
    if(SDL_PollEvent(&event))
    {
      switch (event.type)
      {
      case SDL_QUIT:
        m_bRunning = false;
        break;
      default:
        break; }
    }
  }

  void Game::update()
  {

  }

  bool Game::init(const char* title, int xpos, int ypos, int width,
                  int height, int flags)
  {
    // initialize SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) >= 0)
    {
      // if succeeded create our window
      m_pWindow = SDL_CreateWindow("Chapter 1: Setting up SDL",
                                   xpos, SDL_WINDOWPOS_CENTERED,
                                   height, width,
                                   flags);
      // if the window creation succeeded create our renderer
      if(m_pWindow != 0)
      {
        m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
      }
    } else {
      return false; // sdl could not initialize
    }
    return true;
  }
}
