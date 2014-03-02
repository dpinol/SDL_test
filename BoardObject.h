//
//  SDLGameObject.h
//  SDL Game Programming Book
//
//  Created by shaun mitchell on 19/01/2013.
//  Copyright (c) 2013 shaun mitchell. All rights reserved.
//

#ifndef __SDL_Game_Programming_Book__SDLGameObjectImpl__
#define __SDL_Game_Programming_Book__SDLGameObjectImpl__

#include <SDL.h>
#include "GameObject.h"

class JewelBoard;
class BoardObject : public GameObject
{
public:
  virtual ~BoardObject() {}

  virtual void load(std::unique_ptr<LoaderParams> const &pParams);

  virtual void draw();
  virtual void update();

  virtual void clean() {}
  virtual void collision() {}

  virtual std::string type() { return "Jewel"; }



protected:
  BoardObject();

  bool checkCollideTile(Vector2D newPos);

  void doDyingAnimation();


  // how long the death animation takes, along with a counter
  int m_dyingTime;
  int m_dyingCounter;

  // has the explosion sound played?
  bool m_bPlayedDeathSound;

  bool m_bFlipped;

  Vector2D m_lastSafePos;

  int m_jumpHeight;
};

#endif /* defined(__SDL_Game_Programming_Book__SDLGameObject__) */
