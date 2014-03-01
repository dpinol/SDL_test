/**************************************************************************
** Qt Creator license header template
**   Special keywords: dpinol 28/02/2014 2014
**   Environment variables:
**   To protect a percent sign, use '%'.
**************************************************************************/

#include "log.h"
#include <iostream>
namespace dani {

  static log::Level _level = log::DEBUG;

  log::Level log::getLevel()
  {
    return _level;
  }

  bool log::shouldLog(Level callLevel)
  {
    return callLevel >= _level;
  }

  void log::print(Level , char const *format, std::string const & msg)
  {
    printf(format, msg.c_str());
    fflush(stdout);
  }
}
