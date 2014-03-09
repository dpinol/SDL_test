/**************************************************************************
** Qt Creator license header template
**   Special keywords: dpinol 09/03/2014 2014
**   Environment variables:
**   To protect a percent sign, use '%'.
**************************************************************************/

#include "Match.h"
#include "Board.h"

class MatchImpl
{
public:
  MatchImpl()
    : m_currentLevel(1),
      m_score(0),
      m_playerLives(3)
//    m_playerLives(3),
//    m_bLevelComplete(false)
  {
  }
  Board m_board;
  int m_level;
  int m_score;
  int m_playerLives;

  int m_currentLevel;
  //int m_nextLevel;
  //bool m_bLevelComplete;

};


Match::Match()
  :m_pimpl(new MatchImpl)
{
  restart();
}

Match::~Match()
{

}

Board& Match::getBoard()
{
  return m_pimpl->m_board;
}

void Match::setBoardCallback(BoardCallback* callback)
{
  m_pimpl->m_board.setCallback(callback);
}

int Match::getLevel() const
{
  return m_pimpl->m_currentLevel;
}

int Match::getScore() const
{
  return m_pimpl->m_score;
}

void Match::addScore(int addedScore)
{
  m_pimpl->m_score += addedScore;
}
/*

void setCurrentLevel(int currentLevel);
int getCurrentLevel() const{ return m_currentLevel; }

*/

void Match::restart()
{
  m_pimpl->m_playerLives = 3;
}

void Match::incPlayerLives(int addedlives)
{
  m_pimpl->m_playerLives += addedlives;
}

int Match::getPlayerLives() const
{
  return m_pimpl->m_playerLives;
}

