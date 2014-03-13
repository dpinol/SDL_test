//
//  Game.cpp
//  SDL Game Programming Book
//
//
#include "Game.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "JewelBoard.h"
#include "SoundManager.h"
#include "PlayState.h"
#include <model/Match.h>
#include <utils/ValueEffect.h>
#include <iostream>

using namespace std;

Game* Game::s_pInstance = 0;

Game::Game():
  m_match(new Match),
  m_pWindow(0),
  m_pRenderer(0),
  m_bRunning(false)
{    
}

Game::~Game()
{
  // we must clean up after ourselves to prevent memory leaks
  m_pRenderer= 0;
  m_pWindow = 0;
}


bool Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen, int FPS)
{
  int flags = 0;

  m_FPS = FPS;
  dani::Effect::setFPS(FPS);

  if(fullscreen)
  {
    flags = SDL_WINDOW_FULLSCREEN;
  }

  // attempt to initialise SDL
  if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
  {
    cout << "SDL init success\n";
    // init the window
    m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

    if(m_pWindow != 0) // window init success
    {
      cout << "window creation success\n";
      m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);
      //width/height looks ok, but refresh_rate is 0 on a OSX Mavericks
      SDL_DisplayMode mode;
      SDL_GetCurrentDisplayMode(SDL_GetWindowDisplayIndex(m_pWindow), &mode);

      if(m_pRenderer != 0) // renderer init success
      {
        cout << "renderer creation success\n";
        SDL_SetRenderDrawColor(m_pRenderer, 0,0,0,255);
      }
      else
      {
        cout << "renderer init fail\n";
        return false; // renderer init fail
      }
    }
    else
    {
      cout << "window init fail\n";
      return false; // window init fail
    }
  }
  else
  {
    cout << "SDL init fail\n";
    return false; // SDL init fail
  }

  // add some sound effects - TODO move to better place
  //TheSoundManager::Instance()->load("assets/DST-Away.ogg", "music1", SOUND_MUSIC);
  //TheSoundManager::Instance()->load("assets/jump.wav", "jump", SOUND_SFX);

  //TheSoundManager::Instance()->playMusic("music1", -1);


  TheInputHandler::Instance()->initialiseJoysticks();

  m_playState.reset(new PlayState);
  m_playState->onEnter();
  m_bRunning = true; // everything inited successfully, start the main loop
  return true;
}

/*void Game::setCurrentLevel(int currentLevel)
{
    m_currentLevel = currentLevel;
    m_pGameStateMachine->changeState(new GameOverState());
    m_bLevelComplete = false;
}
*/
void Game::render()
{
  SDL_RenderClear(m_pRenderer);

  m_playState->render();

  SDL_RenderPresent(m_pRenderer);
}

void Game::update()
{
  m_playState->update();
}

void Game::handleEvents()
{
  TheInputHandler::Instance()->update();
}

void Game::clean()
{
  cout << "cleaning game\n";

  TheInputHandler::Instance()->clean();

  m_playState->clean();

  m_playState.reset();
  TheTextureManager::Instance()->clearTextureMap();

  SDL_DestroyWindow(m_pWindow);
  SDL_DestroyRenderer(m_pRenderer);
  SDL_Quit();
}

Match& Game::getMatch()
{
  return *m_match;
}



