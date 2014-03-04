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

class JewelBoard;
class JewelObject : public BoardObject
{
public:
  JewelObject(Jewel &jewel);
  virtual ~JewelObject() {}

  Jewel& getModel();
  Jewel const& getModel() const;

  virtual void load(std::unique_ptr<LoaderParams> const &pParams);

  virtual void draw();
  virtual void update();

  virtual void clean() {}

  virtual std::string type() { return "Jewel"; }

  void setMovement(JewelMove const &m);
  void kill();

  static constexpr short WIDTH = 35;
  static constexpr short HEIGHT = 35;

protected:

  //friend class JewelBoard;
  Jewel *m_model;

};
#endif /* defined(__SDL_Game_Programming_Book__SDLGameObject__) */
