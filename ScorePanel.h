/**************************************************************************
** Qt Creator license header template
**   Special keywords: dpinol 08/03/2014 2014
**   Environment variables:
**   To protect a percent sign, use '%'.
**************************************************************************/

#ifndef SCOREPANEL_H
#define SCOREPANEL_H

#include "GameObject.h"

class ScorePanel: public GameObject
{
public:
  ScorePanel();

  void draw() override;

  // do update stuff
  virtual void update();

  // get the type of the object
  std::string type() override { return "scorePanel";}

};

#endif // SCOREPANEL_H
