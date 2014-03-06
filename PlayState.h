//
//  PlayState.h
//  SDL Game Programming Book
//
//  Created by shaun mitchell on 09/02/2013.
//  Copyright (c) 2013 shaun mitchell. All rights reserved.
//

#ifndef SDL_Game_Programming_Book_PlayState_h
#define SDL_Game_Programming_Book_PlayState_h

#include "GameState.h"
#include <vector>

class GameObject;
class SDLGameObject;
class JewelBoard;

class PlayState : public GameState
{
public:
    
    virtual ~PlayState() { }
    
    virtual void update();
    virtual void render();
    
    virtual bool onEnterImpl();
    virtual bool onExit();
    
    virtual std::string getStateID() const { return s_playID; }
    
    PlayState();

private:
    
    static const std::string s_playID;

    //JewelBoard* m_jewelBoard;
    
};


#endif
