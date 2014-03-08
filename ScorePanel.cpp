/**************************************************************************
** Qt Creator license header template
**   Special keywords: dpinol 08/03/2014 2014
**   Environment variables:
**   To protect a percent sign, use '%'.
**************************************************************************/

#include "ScorePanel.h"
#include "Game.h"
#include <SDL_rect.h>
#include <SDL_test_font.h>

ScorePanel::ScorePanel()
{
}

void ScorePanel::draw()
{
  SDL_Rect rect;
  rect.x = 20;
  rect.y = 35;
  rect.w = 200;
  rect.h = 200;
  SDL_RenderFillRect(TheGame::Instance()->getRenderer(), &rect);
  SDLTest_DrawString(TheGame::Instance()->getRenderer(), 80, 80, "text");
}

void ScorePanel::update()
{

}
