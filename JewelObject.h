//
//  SDLGameObject.h
//  SDL Game Programming Book
//
//  Created by shaun mitchell on 19/01/2013.
//  Copyright (c) 2013 shaun mitchell. All rights reserved.
//

#ifndef __SDL_Game_Programming_Book__SDLGameObject__
#define __SDL_Game_Programming_Book__SDLGameObject__

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



  static constexpr short WIDTH = 35;
  static constexpr short HEIGHT = 35;

protected:

  //friend class JewelBoard;
  Jewel *m_model;
  bool m_isFalling;

};
#endif /* defined(__SDL_Game_Programming_Book__SDLGameObject__) */
