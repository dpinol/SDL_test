/**************************************************************************
** Qt Creator license header template
**   Special keywords: dpinol 07/03/2014 2014
**   Environment variables:
**   To protect a percent sign, use '%'.
**************************************************************************/

#include "Effect.h"
#include <utils/utils.h>
#include <stdexcept>

namespace dani
{

  Effect::Effect(bool paused)
    :m_paused(paused),
      m_slave(NULL),
      m_next(NULL)
  {
  }


  void Effect::setSlave(Effect *slaveEffect)
  {
    m_slave = slaveEffect;
  }

  void Effect::setNext(Effect *nextEffect)
  {
    m_next = nextEffect;
  }
  void Effect::setFPS(int FPS)
  {
    m_FPS = FPS;
  }

  void Effect::setPaused(bool paused)
  {
    m_paused = paused;
  }

  bool Effect::isPaused() const
  {
    return m_paused;
  }

  int Effect::getFPS()
  {
    if (DANI_UNLIKELY(m_FPS == 0))
      throw std::logic_error("Effect::setFPS not set");
    else
      return m_FPS;
  }

  int Effect::m_FPS = 0;

  float Effect::getPhaseNormalized(float phase)
  {
    while(phase > (float) M_PI)
      phase -= 2 * M_PI;
    while(phase < (float) -M_PI)
      phase += 2 * M_PI;
    return phase;
  }

  /******** Composite Effect****/
  void CompositeEffect::update()
  {

  }

  void CompositeEffect::addChid(std::unique_ptr<Effect> child)
  {
    m_children.push_back(std::move(child));
  }

}
