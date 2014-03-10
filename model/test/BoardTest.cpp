/**************************************************************************
** Qt Creator license header template
**   Special keywords: dpinol 03/03/2014 2014
**   Environment variables:
**   To protect a percent sign, use '%'.
**************************************************************************/

#include "BoardTest.h"
#include "model/Board.h"

BoardTest::BoardTest()
{
}
struct DummyBoardCallback : public BoardCallback
{
  void kill(BoardPos ) override
  {
    //getJewel(pos).setColor(Jewel::NO_COLOR);
  }
  bool isAlive(BoardPos ) const override
  {
    //@bug
   // return getJewel(pos).getCol
    return true;
  }
};

void BoardTest::run()
{
  DummyBoardCallback callback;
  Board board;
  board.setCallback(&callback);
}
