/**************************************************************************
** Qt Creator license header template
**   Special keywords: dpinol 03/03/2014 2014
**   Environment variables:
**   To protect a percent sign, use '%'.
**************************************************************************/

#include "JewelDrag.h"
#include "JewelObject.h"
#include "JewelBoard.h"
#include <utils/log.h>
#include "InputHandler.h"

JewelDrag::JewelDrag(JewelBoard &board)
  :m_board(board)
{
}

void JewelDrag::update()
{

}

void JewelDrag::drag()
{
  Vector2D const &pMousePos = TheInputHandler::Instance()->getMousePosition();

  if (!m_fromPixel.isValid())
  {
    //drag start
    BoardPos pos = m_board.getJewelAt(pMousePos);
    if (pos.isValid())
    {
      m_fromPixel = pMousePos;
      m_fromPos = pos;
    }
  }
  else
  {
    //move jewel only vertical or horizontal
    Vector2D shift = pMousePos - m_fromPixel;
    BoardPos shiftPos;
    if (shift.getX() > JewelObject::WIDTH / 2)
        shiftPos = BoardPos(1,0);
    else if (shift.getX() < -JewelObject::WIDTH / 2)
        shiftPos = BoardPos(-1,0);
    else if (shift.getY() > JewelObject::HEIGHT / 2)
        shiftPos = BoardPos(0, 1);
    else if (shift.getY() < -JewelObject::HEIGHT / 2)
        shiftPos = BoardPos(0, -1);
    else
      return;
    m_toPos = m_fromPos + shiftPos;
    m_board.swap(m_fromPos, m_toPos);
  }
}

void JewelDrag::drop()
{
  m_fromPixel.clear();
  m_fromPos.clear();
  /*
  Vector2D const &pMousePos = TheInputHandler::Instance()->getMousePosition();
  if (m_dragging.isValid() && !TheInputHandler::Instance()->getMouseButtonState(LEFT))
  {
    BoardPos const dropping = getJewelAt(pMousePos);
    if (dropping.isValid() && (m_dragging - dropping).isDirection())
      swap(m_dragging, dropping);
    else
      LOG_DEBUG("Swap not valid because dropping outside grid or too far");
  }
  m_dragging = BoardPos();
  */
}


