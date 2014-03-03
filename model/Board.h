/**************************************************************************
** Qt Creator license header template
**   Special keywords: dpinol 03/03/2014 2014
**   Environment variables:
**   To protect a percent sign, use '%'.
**************************************************************************/

#ifndef BOARD_H
#define BOARD_H

#include "BoardPos.h"
#include "Jewel.h"

struct BoardCallback
{
  virtual void kill(BoardPos pos) = 0;
};

class Board : public BoardCallback
{
public:
  Board(BoardCallback &callback);

  Jewel &getJewel(BoardPos pos);
  Jewel const &getJewel(BoardPos pos) const;

  void kill(BoardPos pos) override;

private:
  BoardCallback& m_callback;
  Jewel m_jewels[BoardPos::SIZE + 1][BoardPos::SIZE];
};

#endif // BOARD_H
