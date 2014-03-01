/**************************************************************************
** Qt Creator license header template
**   Special keywords: dpinol 28/02/2014 2014
**   Environment variables:
**   To protect a percent sign, use '%'.
**************************************************************************/

#ifndef DANI_LOG_H
#define DANI_LOG_H
#include <sstream>
#include "utils.h"

namespace dani {

  class log
  {
  public:
    enum Level
    {
      DEBUG = 0,
      INFO = 1,
      WARN = 2,
      ERROR=3
    };


    static bool shouldLog(Level callLevel);
    static void print(Level callLevel,const char *format ,std::string const & msg);
    static Level getLevel();
  };
#define DANI_LOG(callLevel, args) \
  do \
  { \
  if (DANI_UNLIKELY(dani::log::shouldLog(callLevel))) \
  { \
    std::stringstream ss; \
    ss << args; \
    dani::log::print(callLevel, "%s", ss.str().c_str()); \
  } \
} while (0)

#define LOG_DEBUG(args) DANI_LOG(dani::log::DEBUG, args)
#define LOG_INFO(args) DANI_LOG(dani::log::INFO, args)
#define LOG_WARN(args) DANI_LOG(dani::log::WARN, args)
#define LOG_ERROR(args) DANI_LOG(dani::log::ERROR, args)

}
#endif // LOG_H
