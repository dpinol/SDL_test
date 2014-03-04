/**************************************************************************
** Qt Creator license header template
**   Special keywords: dpinol 03/03/2014 2014
**   Environment variables:
**   To protect a percent sign, use '%'.
**************************************************************************/


#ifndef JEWEL_OBJECT_H
#define JEWEL_OBJECT_H

#include <SDL.h>
#include "BoardObject.h"
#include "model/Jewel.h"
#include "JewelMove.h"
#include <SDL_timer.h>


class JewelBoard;

class JewelObject : public BoardObject
{
public:
  JewelObject(Jewel &jewel);
  virtual ~JewelObject() {}

  Jewel& getModel();
  Jewel const& getModel() const;

  virtual void load(std::unique_ptr<LoaderParams> const &pParams) override;

  virtual void draw() override;
  virtual void update() override;

  virtual void clean() override {}

  virtual std::string type() override { return "Jewel"; }

  void setMovement(JewelMove const &m);
  void kill();
  virtual void doDyingAnimation() override;
  bool isFalling() const;
  void setFalling(bool falling);
  short getFallingStep() const;


  static constexpr short WIDTH = 35;
  static constexpr short HEIGHT = 35;

protected:

  //friend class JewelBoard;
  Jewel *m_model;
  short m_fallingStep;

};
#endif /* JEWEL_OBJECT_H */
