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
#include <model/JewelStrike.h>
#include "GameObjectFactory.h"
#include "GameObject.h"
#include "JewelDrag.h"
#include "model/Board.h"
#include <functional>


class JewelObject;
class ScorePanel;
struct SDL_MouseButtonEvent;

class JewelBoard : public GameObject, public BoardCallback
{
public:
    
    virtual ~JewelBoard() {}
    JewelBoard(Board &board, ScorePanel &panel);
    
    void draw() override;
    void update() override;
    void clean() override;
    std::string type() override { return "JewelBoard";}

    
    void load(std::unique_ptr<LoaderParams> const &pParams) override;

    //BoardCallback
    void kill(BoardPos pos) override;
    bool isAlive(BoardPos pos) const override;
    //

    /**
     * @brief getJewel
     * @param row 0 to SIZE
     * @param col
     * @return
     */
    JewelObject& getJewel(BoardPos const pos);
    JewelObject const& getJewel(BoardPos const pos) const;

    //using template more efficient than std::function
    /**
     * loops upwards to quickly propagate falling
     * @param alsoFirstRow default different than in Board
     */
    template<class F>
    void forAllPos(F const &funct, bool alsoFirstRow = true)
    {
      BoardPos pos;
      //for (pos.m_row = (alsoFirstRow ? 0 : 1); pos.m_row <= BoardPos::BoardPos::NUM_ROWS ; ++pos.m_row)
      for (pos.m_row = BoardPos::BoardPos::NUM_ROWS; pos.m_row >= (alsoFirstRow ? 0 : 1)  ; --pos.m_row)
          for (pos.m_col = 0 ; pos.m_col < BoardPos::BoardPos::NUM_COLS ; ++pos.m_col)
            funct(pos);
    }
    template<class F>
    inline void forAll(F const &funct, bool alsoFirstRow = true)
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

    Board &getModel();
    Board const &getModel() const;

private:
    /**
     * Just swap the 2 pointers to the Jewels
     */
    void pureSwap(BoardPos pos, BoardPos pos2);
    /** Move jewel to next row
     * @return true if it cannot fall anymore (supposing lower cells have already been updated)
     */
    void shiftDown(BoardPos pos);

    //extra row is for falling new jewels
    JewelObject* m_jewels[BoardPos::NUM_ROWS + 1][ BoardPos::NUM_COLS];

    void createInitialJewelsBoard();
    Board& m_model;
    ScorePanel& m_panel;
    /**
     * @brief _offset where board is painted
     */
    Vector2D const m_offset;
    Vector2D const m_size;
    JewelDrag m_drag;
    JewelStrike m_strike;
    bool m_jewelsFalling;
};


#endif /* JEWEL_BOARD */
