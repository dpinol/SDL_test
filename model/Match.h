/**************************************************************************
** Qt Creator license header template
**   Special keywords: dpinol 09/03/2014 2014
**   Environment variables:
**   To protect a percent sign, use '%'.
**************************************************************************/

#ifndef MATCH_H
#define MATCH_H
#include <memory>

#include "Board.h"

class MatchImpl;
class Match
{
public:
  Match();
  virtual ~Match();
  void setBoardCallback(BoardCallback* callback);
  void restart();


  int getLevel() const;
  void setLevel(int currentLevel);

  int getScore() const;

  Board& getBoard();
  const Board& getBoard() const;
  void addScore(int addedScore);

  /**
   * @brief incPlayerLives
   * @param addedlives could be negative
   */
  void incPlayerLives(int addedlives);
  int getPlayerLives() const;


private:
  std::unique_ptr<MatchImpl> m_pimpl;
};

#endif // MATCH_H
