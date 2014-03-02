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
#include "model/BoardPos.h"
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

  COLOR getColor() const { return m_color;}
  BoardPos const getBoardPos() const { return m_boardPos;}
  void setMovement(JewelMove const &m);
  void kill();

protected:

  JewelObject(COLOR color);
  friend class JewelBoard;

  bool checkCollideTile(Vector2D newPos);

  COLOR const m_color;
  BoardPos m_boardPos;



  bool m_bFlipped;
};
#endif /* defined(__SDL_Game_Programming_Book__SDLGameObject__) */
