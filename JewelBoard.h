//
//  JewelBoard.h
//  SDL Game Programming Book
//
//  Created by shaun mitchell on 26/03/2013.
//  Copyright (c) 2013 shaun mitchell. All rights reserved.
//

#ifndef __SDL_Game_Programming_Book__JewelBoard__
#define __SDL_Game_Programming_Book__JewelBoard__

#include <iostream>
#include "GameObjectFactory.h"
#include "BoardObject.h"
#include "JewelObject.h"

class JewelBoard : public BoardObject
{
public:
    
    virtual ~JewelBoard() {}
    JewelBoard();
    
    virtual void draw();
    virtual void update();
    virtual void clean();
    
    virtual void load(std::unique_ptr<LoaderParams> const &pParams);

    /**
     * @brief getJewel
     * @param row 0 to SIZE
     * @param col
     * @return
     */
    JewelObject* getJewel(int row, int col);
    JewelObject const* getJewel(int row, int col) const;

private:
    
    static unsigned kJewelsColors;

    int m_scrollSpeed;
    
    int count;
    int maxcount;
    
    SDL_Rect m_srcRect1;
    SDL_Rect m_srcRect2;
    
    SDL_Rect m_destRect1;
    SDL_Rect m_destRect2;
    
    int m_srcRect1Width;
    int m_srcRect2Width;
    
    int m_destRect1Width;
    int m_destRect2Width;
    constexpr static int SIZE = 8;
    //extra row is for falling new jewels
    JewelObject* m_jewels[SIZE + 1][ SIZE];

    void createInialJewelsBoard();
};

class JewelBoardCreator : public BaseCreator
{
public:
    
    virtual GameObject* createGameObject() const
    {
        return new JewelBoard();
    }
};

#endif /* defined(__SDL_Game_Programming_Book__JewelBoard__) */
