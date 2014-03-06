/**************************************************************************
** Qt Creator license header template
**   Special keywords: dpinol 06/03/2014 2014
**   Environment variables:
**   To protect a percent sign, use '%'.
**************************************************************************/

#include "MovingObject.h"

MovingObject::MovingObject()
  : m_done(false)
{
}

MovingObject::~MovingObject()
{

}

// load from file - int x, int y, int width, int height, std::string textureID, int numFrames, int callbackID = 0, int animSpeed = 0
void MovingObject::load(std::unique_ptr<LoaderParams> const &pParams)
{

}

// draw the object
void MovingObject::draw()
{

}

// do update stuff
void MovingObject::update()
{
  getPixel();
}

// remove anything that needs to be deleted
void MovingObject::clean()
{

}

