/**************************************************************************
** Qt Creator license header template
**   Special keywords: dpinol 03/03/2014 2014
**   Environment variables:
**   To protect a percent sign, use '%'.
**************************************************************************/
#include "BoardTest.h"
#include "JewelStrikeTest.h"
#include <vector>

int main(int argc, const char** argv)
{
  std::vector<TestFixture*> tests;
  tests.push_back(new JewelStrikeTest);
  tests.push_back(new BoardTest);

  for(TestFixture * test: tests)
  {
    test->run();
  }
  return 0;
}
