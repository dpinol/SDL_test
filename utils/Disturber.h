/**************************************************************************
** Qt Creator license header template
**   Special keywords: dpinol 07/03/2014 2014
**   Environment variables:
**   To protect a percent sign, use '%'.
**************************************************************************/

#ifndef DISTURBER_H
#define DISTURBER_H

#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <utility>

namespace dani
{

  class IDisturbed
  {
  public:
    /**
     * @brief setFPS If we know the FPS, we spare some IDisturbed class to have a timer to
     * keep a given speed
     * @param FPS how many time per s will the Disturbed getter be called
     */
    static void setFPS(int FPS);
  protected:
    static int getFPS();
  private:
    static int m_FPS;
  };

  template <class T>
  class RangeDisturbed : public IDisturbed
  {
  public:
    virtual T get() const = 0;

    /**
     * @brief getMapToRange
     * @param curReldisturbance 0 to 1 within available range
     * @return
     */
    T getMapToRange(float curReldisturbance) const
    {
      assert(0 <= curReldisturbance);
      assert(1 >= curReldisturbance);
      return m_mean * (1 + m_maxRelDisturbance * (- 1  + 2 * curReldisturbance));
    }
    /**
     * @brief set
     * @param mean
     * @param amplitudeRatio  (1 - amplitudeRatio) * mean  <= val <= (1 + amplitudeRatio) * mean
     */
    void setMean(T mean, float amplitudeRatio = 0)
    {
      m_mean = std::move(mean);
      m_maxRelDisturbance = amplitudeRatio;
    }
    void setRange(T const &min, T const &max)
    {
      m_mean = (min + max) / 2.0;
      m_maxRelDisturbance = (max - min) / 2.0 / m_mean;
    }

  private:
    T m_mean;
    float m_maxRelDisturbance;
    //cache so that we can return by ref
    //T m_lastValue;
  };


  template <class T>
  class RandomDisturbed : public RangeDisturbed<T>
  {
    typedef RangeDisturbed<T> Parent;
  public:


    T get() const override
    {
      return Parent::getMapToRange(rand() / (float) RAND_MAX);
    }
  };




  template <class T>
  class OscilleDisturbed : public RangeDisturbed<T>
  {
    typedef RangeDisturbed<T> Parent;
    float m_maxRelDisturbance;
    //int m_periodMs;
    mutable float m_curRadian;
    float m_incRadian;
  public:
    OscilleDisturbed()
    {
      setPeriod();
    }

    /**
     * @brief set
     * @param mean
     * @param maxRelDisturbance  (1 - maxRelDisturbance) * mean  <= val <= (1 + maxRelDisturbance) * mean
     * @param periodMs how much time
     */
    void setPeriod(int periodMs = 1000)
    {
      m_curRadian = 0;
      m_incRadian = 2.0 * M_PI / IDisturbed::getFPS() / periodMs;
    }

    T get() const override
    {

      m_curRadian += m_incRadian;
      if (m_curRadian > 2 * M_PI)
        m_curRadian = 0;

      return Parent::getMapToRange((cos(m_curRadian) + 1) /2);
    }

  };
}
#endif // DISTURBER_H
