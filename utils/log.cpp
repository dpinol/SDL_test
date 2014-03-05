/**************************************************************************
** Qt Creator license header template
**   Special keywords: dpinol 28/02/2014 2014
**   Environment variables:
**   To protect a percent sign, use '%'.
**************************************************************************/

#include "log.h"
#include <iostream>
#include <algorithm>
namespace dani {

  static log::Level _level = log::INFO;

  void log::init(int argc, const char **argv)
  {
    std::string levels[] = {"--debug", "--info", "--warn", "--error"};
    for(int i = 1; i < argc; i++)
    {
      auto it = std::find(std::begin(levels), std::end(levels), argv[i]);
      if (it != std::end(levels))
      {
        _level = static_cast<log::Level>( it - std::begin(levels));
        break;
      }
    }
  }

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
