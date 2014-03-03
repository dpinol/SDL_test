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
  void kill(BoardPos pos)
  {

  }
};

void BoardTest::run()
{
  DummyBoardCallback callback;
  Board board(callback);
}
