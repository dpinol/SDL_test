/**************************************************************************
** Qt Creator license header template
**   Special keywords: dpinol 28/02/2014 2014
**   Environment variables:
**   To protect a percent sign, use '%'.
**************************************************************************/

#include "utils.h"
#ifdef __GNUC__
# include <cxxabi.h>
#include <unistd.h>
#include <dlfcn.h>
#include <execinfo.h>
#endif

namespace dani {


  std::string getCallstack()
  {
#ifdef __GNUC__
    std::string ret;
    void* callstack[128];
    int i, frames = backtrace(callstack, 128);
    char** strs = backtrace_symbols(callstack, frames);
    for (i = 0; i < frames; ++i)
    {
      const char *symname = strs[i];
      char *demangled = NULL;

      Dl_info info;
      int rc;
      rc = dladdr(callstack[i], &info);
      if (info.dli_sname)
      {
        int status;
        demangled =  abi::__cxa_demangle(info.dli_sname, NULL, 0, &status);
        if ((status == 0) && (demangled != 0))
          symname = demangled;
        else
          symname = info.dli_sname;
      }
      ret += std::string(symname) + "\n";
      if(demangled)
        free(demangled);
    }
    free(strs);
    return ret;
#else
    return "backtrace not available";
#endif
  }
}

