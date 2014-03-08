/**************************************************************************
** Qt Creator license header template
**   Special keywords: dpinol 07/03/2014 2014
**   Environment variables:
**   To protect a percent sign, use '%'.
**************************************************************************/

#include "Effect.h"
#include <utils/utils.h>
#include <stdexcept>
#include <numeric>

namespace dani
{

  Effect::Effect(bool paused)
    :m_paused(paused),
      m_isDone(false),
      m_slave(NULL),
      m_next(NULL),
      m_callback(NULL)
  {
  }
#if 0
  /**
   * @brief restart
   * resets m_isDone and calls restartImpl
   */
  void restart();

  void Effect::restart()
  {
    m_isDone = false;
    restartImpl();
  }
#endif

  void Effect::update()
  {
    if (isDone())
    {
      if (!m_isDone)
      {
        if (m_next)
          m_next->setPaused(false);
        if (m_callback)
          m_callback();
        m_isDone = true;
      }
    }
    else
    {
      m_isDone = false;
      if (!isPaused())
        updateImpl();
    }
  }

  void Effect::setSlave(Effect *slaveEffect)
  {
    m_slave = slaveEffect;
  }

  void Effect::setNext(Effect *nextEffect)
  {
    m_next = nextEffect;
  }

  void Effect::setNext(std::function<void (void)> callback)
  {
    m_callback = callback;
  }

  void Effect::setFPS(int FPS)
  {
    m_FPS = FPS;
  }

  void Effect::setPaused(bool paused)
  {
    m_paused = paused;
    if (m_slave)
      m_slave->setPaused(paused);
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
  void CompositeEffect::updateImpl()
  {
    for(auto &effect: m_children)
    {
      effect->update();
    }
  }

  void CompositeEffect::setPaused(bool paused)
  {
    for(auto &effect: m_children)
    {
      effect->setPaused(paused);
    }
  }

  void CompositeEffect::clearChildren()
  {
    m_children.clear();
  }

  void CompositeEffect::addChild(Effect &child)
  {
    m_children.push_back(&child);
  }

  bool CompositeEffect::isDone() const
  {
    return std::all_of(m_children.begin(), m_children.end(),
                        [](Effect* e)
    {return e->isDone();});
  }

/*  void CompositeEffect::restartImpl()
  {
    for(auto &effect: m_children)
    {
      effect->restart();
    }
  }
*/
}
