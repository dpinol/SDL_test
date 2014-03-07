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
  int IDisturbed::getFPS()
  {
    if (DANI_UNLIKELY(m_FPS == 0))
      throw std::logic_error("IDisturbed::setFPS not set");
    else
      return m_FPS;
  }

  int IDisturbed::m_FPS = 0;

}
