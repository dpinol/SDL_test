/**************************************************************************
** Qt Creator license header template
**   Special keywords: dpinol 07/03/2014 2014
**   Environment variables:
**   To protect a percent sign, use '%'.
**************************************************************************/

#include "Effect.h"
#include <utils/utils.h>
#include <utils/log.h>
#include <stdexcept>
#include <numeric>

namespace dani
{

  Effect::Effect()
    :m_paused(false),
      m_isDone(true),
      m_slave(NULL),
      m_next(NULL),
      m_callback(NULL),
      m_verbose(false)
  {
  }

  Effect::~Effect()
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

  void Effect::resume()
  {
    m_isDone = false;
    resumeImpl();
  }

  void Effect::render()
  {
    if (m_isDone || m_paused)
      return;
    renderImpl();
  }


  void Effect::update()
  {
    if (m_isDone || m_paused)
      return;
    updateImpl();
    if (DANI_UNLIKELY(m_verbose))
      LOG_INFO(std::string(typeid(*this).name())  + toString());

    if (isDone())
    {
      if (DANI_UNLIKELY(m_verbose))
        LOG_INFO(std::string(typeid(*this).name())   + "isDone() returned true!");

      if (m_next)
        m_next->setPaused(false);
      if (m_callback)
        m_callback();
      m_isDone = true;
    }
  }

  void Effect::setVerbose(bool verbose)
  {
    m_verbose = verbose;
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
  CompositeEffect::CompositeEffect(bool ownChildren)
    :m_ownChildren(ownChildren)
  {
    Effect::resume();
  }

  CompositeEffect::~CompositeEffect()
  {
    clearChildren();
  }

  void CompositeEffect::resumeImpl()
  {
   // Effect::resume();
    for(auto &effect: m_children)
    {
      effect->resume();
    }
  }

  void CompositeEffect::updateImpl()
  {
    for(auto &effect: m_children)
    {
      effect->update();
    }
  }

  void CompositeEffect::renderImpl()
  {
    for(auto &effect: m_children)
      effect->render();
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
    if (m_ownChildren)
    {
      for(auto &effect: m_children)
      {
        delete effect;
      }
    }
    m_children.clear();
  }

  void CompositeEffect::addChild(Effect &child)
  {
    m_children.push_back(&child);
  }

  bool CompositeEffect::isDone() const
  {
    return false;
    /*
     * otherwise a child cannot call its parent's resume
    return std::all_of(m_children.begin(), m_children.end(),
                       [](Effect const* e)
    {return e->isDone();});*/
  }

  void CompositeEffect::restart()
  {
    for(auto &effect: m_children)
    {
      effect->restart();
    }
  }

  std::string CompositeEffect::toString() const
  {
    std::string ret;
    for(Effect* e: m_children)
    {
      ret += e->toString() + "; ";
    }
    return ret;
  }
  std::vector<Effect*>::iterator CompositeEffect::begin()
  {
    return m_children.begin();
  }

  std::vector<Effect*>::iterator CompositeEffect::end()
  {
    return m_children.begin();
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
