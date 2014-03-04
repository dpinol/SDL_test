/**************************************************************************
** Qt Creator license header template
**   Special keywords: dpinol 04/03/2014 2014
**   Environment variables:
**   To protect a percent sign, use '%'.
**************************************************************************/

#ifndef DANI_INIT_H
#define DANI_INIT_H

#include <string>
namespace dani
{
  namespace init
  {
    void init(int argc, const char **argv);
    int getNumArgs();
    std::string getArg(int index);
  }
}
#endif // INIT_H
