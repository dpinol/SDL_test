//
//  Game.h
//  SDL Game Programming Book
//
//

#ifndef __SDL_Game_Programming_Book__Game__
#define __SDL_Game_Programming_Book__Game__

#include "SDL.h"
#include "GameStateMachine.h"

#include <utils/Vector2D.h>
#include <vector>
#include <atomic>

class Match;

class Game
{
public:

  static Game* Instance()
  {
    if(s_pInstance == 0)
    {
      s_pInstance = new Game();
      return s_pInstance;
    }

    return s_pInstance;
  }


  /**
     * @brief init
     * @param title
     * @param xpos
     * @param ypos
     * @param width
     * @param height
     * @param fullscreen
     * @param FPS
     * @return
     */
  bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen, int FPS);

  void render();
  void update();
  void handleEvents();
  void clean();

  SDL_Renderer* getRenderer() const { return m_pRenderer; }
  SDL_Window* getWindow() const { return m_pWindow; }
  GameStateMachine* getStateMachine() { return m_pGameStateMachine; }


  bool running() { return m_bRunning; }

  void quit() { m_bRunning = false; }

  int getFPS() const { return m_FPS; }

  Match& getMatch();
private:

  std::unique_ptr<Match> m_match;
  SDL_Window* m_pWindow;
  SDL_Renderer* m_pRenderer;

  GameStateMachine* m_pGameStateMachine;

  bool m_bRunning;

  static Game* s_pInstance;

  int m_FPS;

  Game();
  ~Game();

  Game(const Game&);
  Game& operator=(const Game&);
};

typedef Game TheGame;

#endif /* defined(__SDL_Game_Programming_Book__Game__) */
