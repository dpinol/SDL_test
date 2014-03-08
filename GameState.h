//
//  IGameState.h
//  SDL Game Programming Book
//
//  Created by shaun mitchell on 09/02/2013.
//  Copyright (c) 2013 shaun mitchell. All rights reserved.
//

#ifndef SDL_Game_Programming_Book_IGameState_h
#define SDL_Game_Programming_Book_IGameState_h


#include <string>
#include <vector>
#include <memory>

namespace dani
{
  class CompositeEffect;
}

class GameObject;
class GameState
{
public:
    virtual ~GameState();
    
    virtual void update();
    virtual void render();
    
    virtual bool onEnter();
    virtual bool onExit() = 0;
    
    virtual void resume();
    
    virtual std::string getStateID() const = 0;
    
protected:
    virtual bool onEnterImpl() = 0;

    GameState();
    //@todo put everything on pimpl
    bool m_loadingComplete;
    bool m_exiting;
    std::vector<GameObject*> m_gameObjects;
    std::vector<std::string> m_textureIDList;
    std::unique_ptr<dani::CompositeEffect> m_effects;
};

#endif


