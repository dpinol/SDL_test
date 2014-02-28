/**************************************************************************
** Qt Creator license header template
**   Special keywords: dpinol 28/02/2014 2014
**   Environment variables:
**   To protect a percent sign, use '%'.
**************************************************************************/

#include "log.h"
#include <iostream>
namespace dani {

  static bool _shouldLog = true;

  bool log::shouldLog()
  {
    return _shouldLog;
  }

  void log(std::string const & msg)
  {
    std::cout << msg << std::endl;
  }
}
