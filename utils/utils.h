/**************************************************************************
** Qt Creator license header template
**   Special keywords: dpinol 28/02/2014 2014
**   Environment variables:
**   To protect a percent sign, use '%'.
**************************************************************************/

#ifndef DANI_UTILS_H
#define DANI_UTILS_H

#include <sstream>
#ifdef WIN32
#define DANI_LIKELY(x)       (x)
#define DANI_UNLIKELY(x)     (x)
#else
#define DANI_LIKELY(x)       __builtin_expect((x),1)
#define DANI_UNLIKELY(x)     __builtin_expect((x),0)
#endif

namespace dani {

  template<class T>
  inline std::string toString(T const &o)
  {
    std::stringstream ss;
    ss << o;
    return ss.str();
  }
}
#endif // DANI_UTILS_H
