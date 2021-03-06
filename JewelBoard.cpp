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
}


void JewelBoard::createInitialJewelsBoard()
{
  forAllPos([&](BoardPos const pos)
  {
    Jewel &jewel = m_match.getBoard().getJewel(pos, true);
    JewelObject *jo = new JewelObject(jewel, pos.m_row == 0);

    m_jewels[pos.m_row][pos.m_col] = jo;
    Vector2D pixel = getJewelPixel(pos);
    jo->getPixel() = pixel;
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

bool JewelBoard::isAlive(BoardPos pos) const
{
  return !getJewel(pos).isDead() && !getJewel(pos).isDying();
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
  return *m_jewels[pos.m_row][pos.m_col];
}

JewelObject const& JewelBoard::getJewel(BoardPos const pos) const
{
  assertBoardPos(pos);
  return *m_jewels[pos.m_row][pos.m_col];
}


/******* Model *******/


void JewelBoard::draw()
{
  forAllPos([&](BoardPos const &pos)
  {
    JewelObject &jewel = getJewel(pos);
    //if (jewel.getPixel().getY() +  jewel.getHeight() >= m_offset.getY())
    if (!jewel.isDead())
      jewel.draw();
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
void JewelBoard::pureSwap(BoardPos pos, BoardPos pos2)
{
  /*getJewel(BoardPos(pos.m_col, pos.m_row + 1)) = jo;
  getJewel(BoardPos(pos.m_col, pos.m_row)).resetFalling();*/
  std::swap( m_jewels[pos.m_row][pos.m_col], m_jewels[pos2.m_row][pos2.m_col]);
}
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
void JewelBoard::shiftDown(BoardPos pos)
{
  //JewelObject &jo = getJewel(pos);
  assert(pos.m_row < BoardPos::NUM_ROWS);

  {
    BoardPos next = pos.getBelow();
    //@bug still would rarely fails.pending to investigate
    //assert(getJewel(next).isDead());
    LOG_DEBUG("jewel " << next << " popped up ");

    pureSwap(pos, next);
    m_match.getBoard().pureSwap(pos, next);

    //it will be set to falling again if lower jewel is detected to be empty
    getJewel(next).setFalling(false);
    getJewel(pos).setFalling(false);
  }
}


void JewelBoard::update()
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
  bool boardChanged = false;
  int totalStrikesLen = 0;
  forAllPos([&](BoardPos pos)
  {
    JewelObject &jo = getJewel(pos);
    if (jo.isFallDone())
    {
      boardChanged = true;
      shiftDown(pos);
    }
    if (jo.isFalling() || jo.isDying())
      m_jewelsFalling = true;
    if (pos.m_row > 0 && !jo.isDying() && (jo.isFalling() || jo.isDead()))
    {
      m_jewelsFalling = true;
      BoardPos const upperPos = pos.getAbove();
      JewelObject &upper = getJewel(upperPos);
      if (!upper.isFalling())
      {
        upper.setFalling();
        //resurrect so that it will fall
        if (pos.m_row == 1 && upper.isDead())
        {
          LOG_INFO("Resurrecting " << upperPos);
          upper.resurrect();
          upper.getPixel() = getJewelPixel(upperPos);
        }
      }
    }
    jo.update();
  });

  //@todo call findMatch on falling jewels which are isStable
  //(and all jewels in strike also isStable). And then m_jewelsFalling can be removed
  //we cannot only check when boardChnaged because we would miss when new jewell from row 0
  //directly forms a vertical strike
  if ( !m_jewelsFalling)
  {
    //@todo move to model
    forAllPos([&](BoardPos pos)
    {
      JewelObject &jo = getJewel(pos);
      if (!jo.isFalling())
      {
        int strikesLen;
        strikesLen = m_strike.findMatch(pos, getJewel(pos).getModel().getColor());
        totalStrikesLen += strikesLen;
      }
    }, false);
    if (!m_jewelsFalling && totalStrikesLen == 0)
      TheGame::Instance()->getMatch().nextTurn();
  }
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
