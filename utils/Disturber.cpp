/**************************************************************************
** Qt Creator license header template
**   Special keywords: dpinol 07/03/2014 2014
**   Environment variables:
**   To protect a percent sign, use '%'.
**************************************************************************/

#include "Disturber.h"
#include <utils/utils.h>
#include <stdexcept>

namespace dani
{
  void IDisturbed::setFPS(int FPS)
  {
    m_FPS = FPS;
  }

  void IDisturbed::setPaused(bool paused)
  {
    m_paused = paused;
  }

  bool IDisturbed::isPaused() const
  {
    return m_paused;
  }

  int IDisturbed::getFPS()
  {
    if (DANI_UNLIKELY(m_FPS == 0))
      throw std::logic_error("IDisturbed::setFPS not set");
    else
      return m_FPS;
  }

  int IDisturbed::m_FPS = 0;

  float IDisturbed::getPhaseNormalized(float phase)
  {
    while(phase > M_PI)
      phase -= 2 * M_PI;
    while(phase < -M_PI)
      phase += 2 * M_PI;
    return phase;
  }


}
