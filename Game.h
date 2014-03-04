//
//  Game.h
//  SDL Game Programming Book
//
//

#ifndef __SDL_Game_Programming_Book__Game__
#define __SDL_Game_Programming_Book__Game__

#include "SDL.h"
#include "GameStateMachine.h"
//#include "SDL_mixer.h"
#include "Vector2D.h"
#include <vector>
#include <atomic>

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

    
    bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    
    void render();
    void update();
    void handleEvents();
    void clean();
    
    SDL_Renderer* getRenderer() const { return m_pRenderer; }
    SDL_Window* getWindow() const { return m_pWindow; }
    GameStateMachine* getStateMachine() { return m_pGameStateMachine; }
    
    void setPlayerLives(int lives) { m_playerLives = lives; }
    const int getPlayerLives() { return m_playerLives; }
    
    void setCurrentLevel(int currentLevel);
    const int getCurrentLevel() { return m_currentLevel; }

    bool running() { return m_bRunning; }
    
    void quit() { m_bRunning = false; }
    
    int getGameWidth() const { return m_gameWidth; }
    int getGameHeight() const { return m_gameHeight; }
    
    
private:
    
    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;
    
    GameStateMachine* m_pGameStateMachine;
    
    bool m_bRunning;
    
    static Game* s_pInstance;
    
    int m_gameWidth;
    int m_gameHeight;
    int m_playerLives;
    
    int m_currentLevel;
    int m_nextLevel;
    bool m_bLevelComplete;
    
    
    Game();
    ~Game();
    
    Game(const Game&);
	Game& operator=(const Game&);
};

typedef Game TheGame;

#endif /* defined(__SDL_Game_Programming_Book__Game__) */
