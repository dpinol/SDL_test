/**************************************************************************
** Qt Creator license header template
**   Special keywords: dpinol 04/03/2014 2014
**   Environment variables:
**   To protect a percent sign, use '%'.
**************************************************************************/

#include "init.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <signal.h>



namespace dani
{
  namespace init {
    int m_argc =-1;
    const char **m_argv = NULL;

    void verboseTerminate()
    {
      try
      {
        throw;
      } catch (std::exception const &e)
      {
        std::cerr << "Uncaught exception: " << e.what() << std::endl;
      }
      catch (...)
      {
        std::cerr << "Uncaught unknown exception" << std::endl;
      }
      std::cerr << "terminate exiting from :" << dani::getCallstack() << std::endl;
    }


    void my_handler (int param)
    {
      std::cerr << "Interrupted by signal "<< param << " at: " << std::endl
                   << dani::getCallstack() << std::endl;
      //user interruption
      if (param == SIGINT)
        abort();
    }

    void handleSignals()
    {
      void (*prev_handler)(int);

      prev_handler = signal(SIGINT, my_handler);
      prev_handler = signal(SIGFPE, my_handler);
      prev_handler = signal(SIGTERM, my_handler); //kill
#ifdef WIN32
      prev_handler = signal(SIGBREAK, my_handler);
#endif
      prev_handler = signal(SIGQUIT, my_handler);
      prev_handler = signal(SIGABRT, my_handler);
    }
    void init(int argc, const char **argv)
    {
      m_argc = argc;
      m_argv = argv;

      handleSignals();
      std::set_terminate(verboseTerminate);
    }

  }
}
