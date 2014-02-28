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
      ERROR
    };


    static bool shouldLog(Level callLevel);
    static void print(const char *format ,std::string const & msg);
    static Level getLevel();
  };
#define DANI_LOG(callLevel, args) \
  do \
  { \
  if (DANI_UNLIKELY(shouldLog(callLevel)) \
  { \
    std::stringstream ss; \
    ss << args; \
    print(palLevel, "%s", ss.str().c_str()); \
  } \
} while (0)

#define LOG_DEBUG(args) DANI_LOG(dani::DEBUG, args)
#define LOG_INFO(args) DANI_LOG(dani::INFO, args)
#define LOG_ERROR(args) DANI_LOG(dani::ERROR, args)

}
#endif // LOG_H
