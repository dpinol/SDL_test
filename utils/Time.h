/**************************************************************************
** Qt Creator license header template
**   Special keywords: dpinol 28/02/2014 2014
**   Environment variables:
**   To protect a percent sign, use '%'.
**************************************************************************/

#ifndef PAL_TIME_H
#define PAL_TIME_H

#include <SDL_stdinc.h>
#include <SDL_timer.h>
#include "utils/utils.h"

class Time
{
  Uint32 _nextTime;
  Uint32 const _periodMs;

public:
  Time(Uint32 periodMs)
    : _nextTime(SDL_GetTicks() + periodMs),
      _periodMs(periodMs)
  {
  }

  void restart()
  {
    _nextTime = SDL_GetTicks() + _periodMs;
  }

  bool isTime() const
  {
    return  DANI_UNLIKELY(SDL_TICKS_PASSED(SDL_GetTicks(), _nextTime));
  }
};

#endif // TIME_H
