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
#include "JewelMove.h"

class JewelBoard;
class JewelObject : public BoardObject
{
public:
  typedef unsigned char COLOR;
  virtual ~JewelObject() {}

  virtual void load(std::unique_ptr<LoaderParams> const &pParams);

  virtual void draw();
  virtual void update();

  virtual void clean() {}
  virtual void collision() {}

  virtual std::string type() { return "Jewel"; }

  Vector2D & getPosition();
  void setMovement(JewelMove const &m);

protected:
  COLOR const m_color;
  JewelObject(COLOR color);
  friend class JewelBoard;

  bool checkCollideTile(Vector2D newPos);

  void doDyingAnimation();


  // how long the death animation takes, along with a counter
  int m_dyingTime;
  int m_dyingCounter;

  // has the explosion sound played?
  bool m_bPlayedDeathSound;

  bool m_bFlipped;

};

#endif /* defined(__SDL_Game_Programming_Book__SDLGameObject__) */
