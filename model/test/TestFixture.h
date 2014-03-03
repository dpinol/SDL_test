/**************************************************************************
** Qt Creator license header template
**   Special keywords: dpinol 03/03/2014 2014
**   Environment variables:
**   To protect a percent sign, use '%'.
**************************************************************************/

#ifndef TESTFIXTURE_H
#define TESTFIXTURE_H
#include <stdexcept>
#include <string>

class TestFixture
{
public:
  TestFixture();
  virtual void run() = 0;

/*  template <class T>
  void assertEquals(T const &a, T const &b)
  {
    if ( a != b)
      throw std::logic_error("asserEquals failed");
  }
  */
};



#define TEST_ASSERT_CORE(correct, msg) \
do { \
if (!correct) \
  throw std::logic_error(msg + " failed at" + __FILE__ + ":" + std::to_string(__LINE__)); \
} while(0)

#define TEST_ASSERT(val) \
  TEST_ASSERT_CORE(val, "TEST_ASSERT")

#define TEST_ASSERT_EQUALS(a, b) \
  TEST_ASSERT_CORE(a== b, "TEST_ASSERT_EQUALS")



#endif // TESTFIXTURE_H
