/**************************************************************************
** Qt Creator license header template
**   Special keywords: dpinol 08/03/2014 2014
**   Environment variables:
**   To protect a percent sign, use '%'.
**************************************************************************/

#include "ScorePanel.h"
#include "Game.h"
#include <utils/utils.h>
#include <model/Match.h>

#include <SDL_rect.h>
#include <SDL_test_font.h>

ScorePanel::ScorePanel(Match &match)
  :m_match(match)
{
}

void ScorePanel::draw()
{
  SDL_Rect rect;
  rect.x = 20;
  rect.y = 35;
  rect.w = 200;
  rect.h = 200;
  SDL_Renderer *renderer = TheGame::Instance()->getRenderer();
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderFillRect(renderer, &rect);
  //SDL_FillRect()
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDLTest_DrawString(renderer, 80, 80, ("Score: " + dani::toString(m_match.getScore())).c_str());
}

void ScorePanel::update()
{

}
