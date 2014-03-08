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


}
