//
//  MenuState.h
//  SDL Game Programming Book
//
//  Created by shaun mitchell on 09/02/2013.
//  Copyright (c) 2013 shaun mitchell. All rights reserved.
//

#ifndef __SDL_Game_Programming_Book__MenuState__
#define __SDL_Game_Programming_Book__MenuState__

#include <vector>
#include "MenuState.h"
#include "GameObject.h"

class MainMenuState : public MenuState
{
public:
    
    virtual ~MainMenuState() {}

    void update() override;
    //virtual void render();
    
    virtual bool onEnterImpl() override;
    virtual bool onExit() override;
    
    virtual std::string getStateID() const override { return s_menuID; }
    
private:
    
    virtual void setCallbacks(const std::vector<Callback>& callbacks);
    
    // call back functions for menu items
    static void s_menuToPlay();
    static void s_exitFromMenu();
    
    static const std::string s_menuID;
    
};

#endif /* defined(__SDL_Game_Programming_Book__MenuState__) */
