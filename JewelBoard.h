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
#include "model/BoardPos.h"
#include <functional>

class JewelObject;
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
     * @brief swap swaps jewels at specified positions
     * but only if final position achieves a strike
     * @param pos1
     * @param pos2
     * @return whether they could be swap
     */
    bool swap(BoardPos const pos1, BoardPos const pos2);
    /**
     * @brief getJewel
     * @param row 0 to SIZE
     * @param col
     * @return
     */
    JewelObject& getJewel(BoardPos const pos);
    JewelObject const& getJewel(BoardPos const pos) const;

    //using template more efficient than std::function
    template<class F>
    void forAll(F const &funct)
    {
      BoardPos pos(-1, -1);
      for (pos.m_row = 1; pos.m_row <= BoardPos::BoardPos::SIZE ; ++pos.m_row)
          for (pos.m_col = 0 ; pos.m_col < BoardPos::BoardPos::SIZE ; ++pos.m_col)
            funct(getJewel(pos));
    }

private:
    
    static constexpr short kJewelsColors = 5;

    //extra row is for falling new jewels
    JewelObject* m_jewels[BoardPos::SIZE + 1][ BoardPos::SIZE];

    void createInialJewelsBoard();
};

class JewelBoardCreator : public BaseCreator
{
public:
    
    virtual JewelBoard* createGameObject() const
    {
        return new JewelBoard();
    }
};

#endif /* defined(__SDL_Game_Programming_Book__JewelBoard__) */
