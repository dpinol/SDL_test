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

/**
 * @brief The Match class manages a match being played.
 */
class Match
{
public:
  Match();
  virtual ~Match();
  void setBoardCallback(BoardCallback* callback);
  void restart();

  /**
   * @brief nextTurn must be called when cascades caused
   * by last moved are over
   * Causes score accumulations to
   */
  void nextTurn();

  /**
   * @brief scoreStrike
   * @param strikeLen number of jewels in strike
   * Each strikes achieved in a turn is worth 20*strikeLen plus the score
   * obtained so far in the current turn
   * @return score obtained by this score (not the total score)
   */
  int scoreStrike(int strikeLen);


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
