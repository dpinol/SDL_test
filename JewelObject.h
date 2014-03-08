/**************************************************************************
** Qt Creator license header template
**   Special keywords: dpinol 03/03/2014 2014
**   Environment variables:
**   To protect a percent sign, use '%'.
**************************************************************************/


#ifndef JEWEL_OBJECT_H
#define JEWEL_OBJECT_H

#include <SDL.h>
#include "GameObject.h"
#include <utils/ValueEffect.h>
#include "model/Jewel.h"
#include "JewelMove.h"
#include <SDL_timer.h>


class JewelBoard;

class JewelObject : public GameObject
{
public:
  /**
   * @brief JewelObject
   * @param jewel
   * @param firstRow if true, it will be marked as dead
   */
  JewelObject(Jewel &jewel, bool firstRow);
  virtual ~JewelObject() {}

  Jewel& getModel();
  Jewel const& getModel() const;

  virtual void load(std::unique_ptr<LoaderParams> const &pParams) override;

  virtual void draw() override;
  /** manages dying and dead states*/
  virtual void update() override;

  virtual void clean() override {}

  virtual std::string type() override { return "Jewel"; }

  void setMovement(JewelMove const &m);
  void kill();
  void resurrect();

  bool isFalling() const;
  bool isFallDone() const;
  void setFalling(bool falling =true);
  void fallStep();

  dani::Effect &swapWith(BoardPos relativeShift, bool andReturn);

  static constexpr short MARGIN = 2;
  static constexpr short SPRITE_SIZE = 35;
  //WIDTH & HEIGHT include margin
  static constexpr short WIDTH = SPRITE_SIZE + MARGIN * 2;
  static constexpr short HEIGHT = WIDTH;
  //in how many steps will it fall a single row
  static const short FALLING_STEPS;

protected:
  //swap place with adjacent
  dani::OscilleEffect<Vector2D> m_swapper;
  dani::OscilleEffect<float> m_dier;

  bool m_bfalling;
  //friend class JewelBoard;
  Jewel *m_model;
  short m_fallingStep;

};
#endif /* JEWEL_OBJECT_H */
