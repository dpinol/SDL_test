/**************************************************************************
** Qt Creator license header template
**   Special keywords: dpinol 03/03/2014 2014
**   Environment variables:
**   To protect a percent sign, use '%'.
**************************************************************************/

#include "JewelBoard.h"
#include "ScorePanel.h"
#include "JewelObject.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "Game.h"
#include <model/JewelSwap.h>
#include <model/Match.h>
#include <model/Board.h>
#include "utils/utils.h"
#include "utils/log.h"
#include <assert.h>
#include <algorithm>
#include <numeric>


#include <SDL_test_font.h>
#include <SDL_events.h>

struct RGB { int r,g,b;};
RGB getJewelColor(Jewel::COLOR col)
{
  switch(col)
  {
  case 0:
    return {0,0,255};
  case 1:
    return {0,255,0};
  case 2:
    return {255,255,0};
  case 3:
    return {255,0,255};
  default:
    return {255,0,0};
  }
}


class ScorePopUpEffect : public dani::CompositeEffect
{
  JewelBoard &m_board;
  dani::RangeEffect<Vector2D> m_mover;
  dani::RangeEffect<int> m_fader;
  static constexpr int DURATION_MS = 3000;
  RGB m_rgb;
  Vector2D m_pixel;
  std::string m_score;
public:
  ScorePopUpEffect(JewelBoard &board)
    :m_board(board)
  {
    addChild(m_mover);
    addChild(m_fader);
  }

  void trigger(BoardPos pos, int score)
  {
    m_score = dani::toString(score);
    JewelObject &jo = m_board.getJewel(pos);
    m_rgb = getJewelColor(jo.getModel().getColor());
    //@todo get text size estimate and center
    m_pixel = jo.getPixel() + Vector2D(JewelObject::WIDTH /2 - 8, JewelObject::HEIGHT /2 -8);
    m_mover.setRange(m_pixel, m_pixel - Vector2D(0, 2 * JewelObject::HEIGHT), DURATION_MS);
    m_fader.setRange(255, 0, DURATION_MS);
    resume();
  }


  void renderImpl() override
  {
    if (m_mover.isDone())
      return;
    //    dani::CompositeEffect::updateImpl();
    //get color from
    SDL_SetRenderDrawColor(TheGame::Instance()->getRenderer(), m_rgb.r, m_rgb.g, m_rgb.b, m_fader.get());

    SDLTest_DrawString(TheGame::Instance()->getRenderer(), m_mover.get().getX(), m_mover.get().getY(),
                       m_score.c_str());
  }
};

JewelBoard::JewelBoard(Match &match):
  m_match(match),
  m_offset(342, 86),
  m_size(JewelObject::WIDTH * BoardPos::NUM_COLS, JewelObject::HEIGHT * (BoardPos::NUM_ROWS + 1) ),
  m_drag(*this),
  m_strike(m_match.getBoard(), this),
  m_jewelsFalling(true),
  m_scoreEffects(true)
{
  //at most we'll need one per column
  for (int i=0; i < BoardPos::NUM_COLS; i++)
  {
    m_scoreEffects.addChild(*new ScorePopUpEffect(*this));
  }
  m_effects->addChild(m_scoreEffects);
  getModel().setCallback(this);

  TheTextureManager::Instance()->load("assets/jewels.png", "jewels");

  createInitialJewelsBoard();

  LOG_INFO(*this << std::endl);

}


void JewelBoard::createInitialJewelsBoard()
{
  forAllCols([&](short col)
  {
    Column &column = m_jewels[col];
    BoardPos pos(col, 0);
    for (; pos.m_row <= BoardPos::NUM_ROWS; pos.m_row++)
    {
      Jewel &jewel = m_match.getBoard().getJewel(pos, true);
      JewelObject *jo = new JewelObject(jewel, pos.m_row == 0);
      column.push_back(jo);
      Vector2D pixel = getJewelPixel(pos);
      jo->getPixel() = pixel;
    }
  });
}

void JewelBoard::kill(std::vector<BoardPos> const & killed)
{
  int newKilled = 0;
  for(BoardPos pos: killed)
  {
    JewelObject &j = getJewel(pos);
    if (!j.isDead())
    {
      newKilled++;
      getJewel(pos).kill(); //.setColor(Jewel::NO_COLOR);
    }
  }
  scoreAt(killed, newKilled);
}

bool JewelBoard::isStable(BoardPos pos) const
{
  JewelObject const &jo = getJewel(pos);
  return !jo.isDead() && !jo.isDying() && !jo.isFalling();
}

void JewelBoard::load(std::unique_ptr<LoaderParams> const &pParams)
{
  //@todo load dimensions from xml
}

/******* Model *******/
#ifdef NDEBUG
inline static void assertBoardPos(BoardPos const)
{
}
#else
inline static void assertBoardPos(BoardPos const pos)
{
  if (!pos.isValid(true))
    throw std::runtime_error("BoardPos " + dani::toString(pos) + "is not valid");
}
#endif

Board const &JewelBoard::getModel() const
{
  return m_match.getBoard();
}

Board &JewelBoard::getModel()
{
  return m_match.getBoard();
}

JewelObject& JewelBoard::getJewel(BoardPos const pos)
{
  assertBoardPos(pos);
  return *m_jewels[pos.m_col][pos.m_row];
}

JewelObject const& JewelBoard::getJewel(BoardPos const pos) const
{
  assertBoardPos(pos);
  return *m_jewels[pos.m_col][pos.m_row];
}


/******* Model *******/

bool JewelBoard::isVisible(BoardPos pos) const
{
  return getJewel(pos).getPixel().getY() > m_offset.getY();
}

void JewelBoard::draw()
{
  forAllPos([&](BoardPos const &pos)
  {
    //will never show ROW0
    if (isVisible(pos))
    {
      JewelObject &jewel = getJewel(pos);
      //if (!jewel.isDead())
      jewel.draw();
    }
  });
  GameObject::draw();
}

Vector2D JewelBoard::getJewelPixel(BoardPos pos) const
{
  return Vector2D(m_offset.getX() + JewelObject::WIDTH * pos.m_col,
                  m_offset.getY() + JewelObject::HEIGHT * pos.m_row);
}

BoardPos JewelBoard::getJewelAt(Vector2D const &v) const
{
  if (!v.isInside(m_offset, m_offset + m_size))
    return BoardPos();
  return BoardPos((v.getX() - m_offset.getX()) / JewelObject::WIDTH,
                  (v.getY() - m_offset.getY()) / JewelObject::HEIGHT);
}

/**
 * @brief wa swaps jewels at specified positions
 * but only if final position achieves a strike
 * @param pos1
 * @param pos2
 * @return whether they could be swap

bool swap(BoardPos const pos1, BoardPos const pos2);

bool JewelBoard::swap(BoardPos const pos1, BoardPos const pos2)
{
  JewelSwap sw(m_match.getBoard());
  sw.setPositions(pos1, pos2);
  return sw.run();
}
*/

/**
 * draft
 * bool isStable(BoardPos pos)
  {
    while (pos.m_row <= BoardPos::NUM_ROWS)
    {
       pos =next.getBelow();
      JewelObject &below = getJewel(pos)
      if (below.isFalling() || below.isDead())
        return false;
    }
    return true;
  }
 */


/*
0|1,
1|2-
2|,1
3|-2
4|33
*/
/*
0|2,
1|,2
2|1
*/


inline BoardPos JewelBoard::itToRow(BoardPos forCol, Column::iterator it, Column::iterator first)
{
  return BoardPos(forCol.m_col, it -first);
}

//from http://en.cppreference.com/w/cpp/algorithm/rotate
void JewelBoard::rotate(BoardPos toPos, BoardPos fromPos)
{
  Column &column = m_jewels[fromPos.m_col];
  Column::iterator first = column.begin();
  Column::iterator n_first = column.begin() + fromPos.m_row + 1;
  Column::iterator last = column.begin() + toPos.m_row + 1;

  Column::iterator next = n_first;
  while (first != next) {
    std::iter_swap(first, next);
    getModel().pureSwap(itToRow(toPos, first, column.begin()), itToRow(toPos, next, column.begin()));
    first++;
    next++;
    if (next == last) {
      next = n_first;
    } else if (first == n_first) {
      n_first = next;
    }
  }
}
void JewelBoard::pureSwap(BoardPos toPos, BoardPos fromPos)
{
  assert(fromPos.m_col == toPos.m_col);

  LOG_INFO("jewel " << fromPos << " falling until " << toPos);

  int numKilled = toPos.m_row - fromPos.m_row;

  //create unit test!
  rotate(toPos, fromPos);
  //55522

  Column &column = m_jewels[fromPos.m_col];

  BoardPos fallFrom(fromPos.m_col, 0);

  column[0]->getPixel() = getJewelPixel(fallFrom);
  column[0]->resurrect();

  BoardPos fallUntil(toPos.m_col, toPos.m_row);
  for (; fallUntil.m_row > 0 ; fallUntil.m_row--)
  {
    JewelObject *j = column[fallUntil.m_row];
    //
    if (j->isDead())
    {
      //stack rest of dead above the row0
      j->resurrect();
      fallFrom.m_row--;
      j->getPixel() = getJewelPixel(fallFrom);
//      assert(fallUntil.m_row - fallFrom.m_row <= BoardPos::NUM_ROWS);
    }
    j->fallUntil(getJewelPixel(fallUntil));

  }
}
void JewelBoard::shiftDown(BoardPos pos)
{
}
/*
0|1,
1|2-
2|,1
3|-2
4|33
*/

/*
0|2,
1|,2
2|1
*/

bool JewelBoard::findJustDeads(short col)
{
  bool changed = false;
  BoardPos pos(col, BoardPos::BoardPos::NUM_ROWS);
  //valid when already falling
  BoardPos targetPos;
  for (; pos.m_row >= 0  ; --pos.m_row)
  {
    JewelObject &jo = getJewel(pos);
    if (targetPos.isValid())
    {
      if(!jo.isDead() || pos.m_row == 0)
      {
        pureSwap(targetPos, pos);
        //targetPos.m_row--;
        break;
      }
    }
    else if (pos.m_row >= 1)
    {
      JewelObject &above = getJewel(pos.getAbove());
      if (jo.isDead() && !above.isFalling())
      {
        targetPos = pos;
        LOG_INFO("Falling to " << pos);
        changed = true;
      }
    }
  }
  return changed;
}

bool JewelBoard::update()
{
  GameObject::update();
  //@todo should we block while block are falling?
  bool clicked = TheInputHandler::Instance()->getMouseButtonState(LEFT);
  if (clicked)
    m_drag.drag();
  else
    m_drag.drop();

  m_match.getBoard().update();
  m_jewelsFalling = false;
  int totalStrikesLen = 0;

  bool changed = false;

  forAllCols([&](short col)
  {
    changed = findJustDeads(col) || changed;
  });
  if (changed)
    LOG_INFO(*this << std::endl);
  changed = false;

  /*0->1
  1->2
  2->0*/
  //dead jewels also fall. In this way they recycle the row 0
  bool changed2 = false;
  forAllCols([&](short col)
  {
    JewelObject &row0 = getJewel(BoardPos(col, 0));
    BoardPos pos(col, BoardPos::BoardPos::NUM_ROWS);
    Vector2D targetPos;
    for (; pos.m_row >= 0  ; --pos.m_row)
    {
      JewelObject &jo = getJewel(pos);
      changed2 = jo.update() || changed2;
      if (jo.isFalling())
      {
        LOG_DEBUG(pos << " falling");
        m_jewelsFalling = true;
      }
    }

  });
  if (changed2)
    LOG_INFO(*this << std::endl);


  bool changed3 = false;

  //@todo call findMatch on falling jewels which are isStable
  //(and all jewels in strike also isStable). And then m_jewelsFalling can be removed
  //we cannot only check when boardChnaged because we would miss when new jewell from row 0
  //directly forms a vertical strike
  //if ( !m_jewelsFalling)
  {
    //@todo move to model
    forAllPos([&](BoardPos pos)
    {
      if (isStable(pos))
      {
        //JewelObject &jo = getJewel(pos);
        int strikesLen;
        strikesLen = m_strike.findMatch(pos, getJewel(pos).getModel().getColor());
        totalStrikesLen += strikesLen;
        if (strikesLen > 0)
          changed3 = true;
      }
      //jo.resetFall();
    }, false);
    if (!m_jewelsFalling && totalStrikesLen == 0)
      TheGame::Instance()->getMatch().nextTurn();
  }
  if (changed3)
    LOG_INFO(*this << std::endl);
  return changed|| changed2 || changed3;
}


void JewelBoard::scoreAt(std::vector<BoardPos> const & killed, int numJewels)
{
  int newPoints = m_match.scoreStrike(numJewels);
  //show popup at center roughly
  BoardPos center = std::accumulate(killed.begin(), killed.end(), BoardPos(0, 0));
  center.m_row /= killed.size();
  center.m_col /= killed.size();
  BoardPos closestPos = *std::min_element(killed.begin(), killed.end(),
                                          [](BoardPos pos1, BoardPos pos2)
  {return (pos1 - pos2).length();});

  ScorePopUpEffect *idleEffect;
  idleEffect = dynamic_cast<ScorePopUpEffect*>(*std::find_if(std::begin(m_scoreEffects),
                                                             std::end(m_scoreEffects),
                                                             [](dani::Effect *effect)
  {
                                                 return effect->isDone();
                                               }));

  idleEffect->trigger(closestPos, newPoints);
}

void JewelBoard::clean()
{
  forAll([&](JewelObject &jewel)
  {
    jewel.clean();
  });

  GameObject::clean();
}

std::ostream & operator<<(std::ostream & strm, JewelBoard &board)
{
  BoardPos pos;
  for (pos.m_row = 0; pos.m_row <= BoardPos::BoardPos::NUM_ROWS  ; ++pos.m_row)
  {
    for (pos.m_col = 0; pos.m_col < BoardPos::BoardPos::NUM_COLS ; ++pos.m_col)
      strm << board.getJewel(pos);
    strm << std::endl;
  }
  return strm;
}

