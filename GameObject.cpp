/**************************************************************************
** Qt Creator license header template
**   Special keywords: dpinol 08/03/2014 2014
**   Environment variables:
**   To protect a percent sign, use '%'.
**************************************************************************/
#include "GameObject.h"
#include <utils/Effect.h>

GameObject::GameObject() :  m_pixel(0,0),
  m_velocity(0,0),
  m_acceleration(0,0),
  m_width(0),
  m_height(0),
  m_currentRow(0),
  m_currentFrame(0),
  m_bUpdating(false),
  m_bDead(false),
  m_bDying(false),
  m_dyingTime(0),
  m_dyingCounter(0),
  m_angle(0),
  m_alpha(255),
  m_effects(new dani::CompositeEffect)
{
}

GameObject::~GameObject()
{

}

void GameObject::update()
{
  m_effects->update();
}

void GameObject::clean()
{
  m_effects->clearChildren();
}
