/**************************************************************************
** Qt Creator license header template
**   Special keywords: dpinol 07/03/2014 2014
**   Environment variables:
**   To protect a percent sign, use '%'.
**************************************************************************/

#ifndef DISTURBER_H
#define DISTURBER_H

#include <stdlib.h>

namespace dani
{
  class IDisturber
  {
  public:
    virtual void run() = 0;
  };

  template <class T>
  class Disturber : public IDisturber
  {
  public:
    Disturber(T & value)
    :m_value(value)
    {
    }

    T & m_value;
  };

  template <class T>
  class RandomDisturber : public Disturber<T>
  {
    typedef Disturber<T> Parent;
    float m_maxRelDisturbance;
  public:
    /**
     * @brief RandomDisturber
     * @param value initial value
     */
    RandomDisturber(T& value)
      :Parent(value),
        m_maxRelDisturbance(0)
    {
    }
    /**
     * @brief setMultiplier
     * @param maxRelDisturbance  (1 - maxRelDisturbance) * val0  <= val1 <= (1 + maxRelDisturbance) * val0
     */
    void setMaxRelDisturbance(float maxRelDisturbance)
    {
      m_maxRelDisturbance = maxRelDisturbance;
    }

    void run() override
    {
      float randPerc = rand() / (float) RAND_MAX;
      Parent::m_value =  1 + m_maxRelDisturbance * (- 1  + 2 * randPerc);
    }
  };
}
#endif // DISTURBER_H
