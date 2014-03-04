/**************************************************************************
** Qt Creator license header template
**   Special keywords: dpinol 03/03/2014 2014
**   Environment variables:
**   To protect a percent sign, use '%'.
**************************************************************************/


#ifndef JEWEL_BOARD
#define JEWEL_BOARD

#include <iostream>
#include "model/BoardPos.h"
#include "GameObjectFactory.h"
#include "BoardObject.h"
#include "JewelDrag.h"
#include "model/Board.h"
#include <functional>


class JewelObject;
struct SDL_MouseButtonEvent;
class JewelBoard : public BoardObject, BoardCallback
{
public:
    
    virtual ~JewelBoard() {}
    JewelBoard();
    
    virtual void draw();
    virtual void update();
    virtual void clean();
    
    virtual void load(std::unique_ptr<LoaderParams> const &pParams);

    //BoardCallback
    void kill(BoardPos pos) override;


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
    void forAllPos(F const &funct, bool alsoFirstRow = false)
    {
      BoardPos pos;
      for (pos.m_row = (alsoFirstRow ? 0 : 1); pos.m_row <= BoardPos::BoardPos::NUM_ROWS ; ++pos.m_row)
          for (pos.m_col = 0 ; pos.m_col < BoardPos::BoardPos::NUM_COLS ; ++pos.m_col)
            funct(pos);
    }
    template<class F>
    inline void forAll(F const &funct, bool alsoFirstRow = false)
    {
      forAllPos([&](BoardPos const &pos)
      {
         funct(getJewel(pos));
      }, alsoFirstRow);
    }
    /**
     * @brief getJewelAt
     * @param ev
     * @return not valid board if not withn board
     */
    BoardPos getJewelAt(const Vector2D &pixel) const;
    Vector2D getJewelPixel(BoardPos pos) const;

private:
    /** Move jewel to next row*/
    void shiftDown(BoardPos pos);

    //extra row is for falling new jewels
    JewelObject* m_jewels[BoardPos::NUM_ROWS + 1][ BoardPos::NUM_COLS];

    void createInitialJewelsBoard();
    Board m_model;
    /**
     * @brief _offset where board is painted
     */
    Vector2D const m_offset;
    Vector2D const m_bottomDown;
    JewelDrag m_drag;

};

class JewelBoardCreator : public BaseCreator
{
public:
    
    virtual JewelBoard* createGameObject() const
    {
        return new JewelBoard();
    }
};

#endif /* JEWEL_BOARD */
