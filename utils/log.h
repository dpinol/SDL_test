/**************************************************************************
** Qt Creator license header template
**   Special keywords: dpinol 28/02/2014 2014
**   Environment variables:
**   To protect a percent sign, use '%'.
**************************************************************************/

#ifndef DANI_LOG_H
#define DANI_LOG_H
#include <sstream>

namespace dani {
  enum
  {
    DEBUG = 0,
    INFO = 1,
    ERROR
  };

  class log
  {
  public:
    static bool shouldLog();
    static void print(std::string const & msg);
  };
#define DANI_LOG(palLevel, args) \
  do \
  { \
  std::stringstream ss; \
  ss << args; \
  print(palLevel, "%s", ss.str().c_str()); \
} while (0)

#define LOG_DEBUG(args) DANI_LOG(dani::DEBUG, args)
#define LOG_INFO(args) DANI_LOG(dani::INFO, args)
#define LOG_ERROR(args) DANI_LOG(dani::ERROR, args)

}
#endif // LOG_H
