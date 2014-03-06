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
    /**
     * @brief getArg
     * @param index 0 returns the exec name
     * @return
     */
    std::string getArg(int index);
    bool hasArg(const char *arg);
  }
}
#endif // INIT_H
