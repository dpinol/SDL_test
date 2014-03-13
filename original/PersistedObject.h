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
class PersistedObject : public GameObject
{
public:
  virtual ~PersistedObject() {}

  virtual void load(std::unique_ptr<LoaderParams> const &pParams);

  virtual void draw();
  virtual void update();

  virtual void clean() {}
  virtual void collision() {}

  virtual std::string type() { return "PersistedObject"; }



protected:
  PersistedObject();

  virtual void doDyingAnimation();


};

#endif /* defined(__SDL_Game_Programming_Book__SDLGameObject__) */
