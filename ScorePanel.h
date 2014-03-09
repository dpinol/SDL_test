/**************************************************************************
** Qt Creator license header template
**   Special keywords: dpinol 08/03/2014 2014
**   Environment variables:
**   To protect a percent sign, use '%'.
**************************************************************************/

#ifndef SCOREPANEL_H
#define SCOREPANEL_H

#include "GameObject.h"

class Match;
class ScorePanel: public GameObject
{
public:
  ScorePanel(Match &match);

  void draw() override;

  // do update stuff
  virtual void update();

  // get the type of the object
  std::string type() override { return "scorePanel";}
private:
  Match &m_match;
};

#endif // SCOREPANEL_H
