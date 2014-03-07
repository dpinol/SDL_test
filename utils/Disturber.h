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
    static float getPhaseNormalized(float phase);

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
      float ratioNormalized = - 1  + 2 * curReldisturbance;
      return m_mean * (1 + m_maxRelDisturbance * ratioNormalized);
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

  protected:
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
    //int m_periodMs;
    mutable float m_curRadian;
    //larger than 10 for non stop
    float m_stopRadian;
    float m_incRadian;
  public:
    OscilleDisturbed()
    {
      setPeriod();
      m_curRadian = 0;
      m_stopRadian = 42;
    }

    /**
     * @brief set
     * @param mean
     * @param maxRelDisturbance  (1 - maxRelDisturbance) * mean  <= val <= (1 + maxRelDisturbance) * mean
     * @param periodMs how much time
     */
    void setPeriod(int periodMs = 1000)
    {
      m_incRadian = 2.0 * M_PI / IDisturbed::getFPS() / periodMs;
    }


    /**
     * @brief setStartPhase
     * @param startPhase degree in radian on where to start in the sin() function
     * So 0 mean at mean value increasing, PI/2 at max value,
     * PI at mean  value decreading, -PI/2 at min value
     * startPhase will be normalized
     */
    void setStartPhase(float startPhase = 0)
    {
      m_curRadian = Parent::getPhaseNormalized(startPhase);

    }

    void setStopPhase(float stopPhase)
    {
      m_stopRadian = Parent::getPhaseNormalized(stopPhase);
    }


    /**
     * @brief getPhase
     * @return will be in [0, 2PI]
     */
    float getPhase() const
    {
      return m_curRadian;
    }

    T get() const override
    {
      if (m_curRadian > m_stopRadian)
        return m_curRadian;
      m_curRadian += m_incRadian;
      if (m_curRadian > 2 * M_PI)
        m_curRadian -= 2 * M_PI;

      return Parent::getMapToRange((sin(m_curRadian) + 1) /2);
    }

  };
}
#endif // DISTURBER_H
