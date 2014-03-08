/**************************************************************************
** Qt Creator license header template
**   Special keywords: dpinol 07/03/2014 2014
**   Environment variables:
**   To protect a percent sign, use '%'.
**************************************************************************/

#ifndef ValueEffect_H
#define ValueEffect_H

#include "Effect.h"
#include <utils/utils.h>

#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <utility>

namespace dani
{

  template <class T>
  class ValueEffect : public Effect
  {
  public:
    inline T const &get() const
    {
      return m_value;
    }

    /* virtual void setPaused(bool paused = true)
    {
      m_value
    }
    void restart()
    {
      m_value =
    }*/

    std::string toString() const override
    {
      return dani::toString(m_value);
    }
  protected:
    T m_value;
  };

  template <class T>
  class RangeEffect : public ValueEffect<T>
  {
  public:

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
      return m_mean + (m_maxDisturbance * ratioNormalized);
    }

    /**
     * @brief set
     * @param mean if paused, will always return this number
     * @param amplitudeRatio  mean - maxDisturbance <= val <= mean + maxDisturbance
     */
    void setMean(T mean, T const &maxDisturbance = 0)
    {
      m_mean = std::move(mean);
      m_maxDisturbance = maxDisturbance;
    }


    void setRange(T const &min, T const &max)
    {
      m_mean = (min + max) / 2.0;
      m_maxDisturbance = (max - min) / 2.0;
    }

  protected:
    T m_mean;
    T m_maxDisturbance;
    //cache so that we can return by ref
    //T m_lastValue;
  }; //RangeEffect


  template <class T>
  class RandomEffect : public RangeEffect<T>
  {
    typedef RangeEffect<T> Parent;
  public:

    constexpr bool isDone() const override
    {
      return false;
    }

    void updateImpl() override
    {
        Parent::m_value = Parent::getMapToRange(rand() / (float) RAND_MAX);
    }
  };




  template <class T>
  class OscilleEffect : public RangeEffect<T>
  {
    typedef RangeEffect<T> Parent;
    //int m_periodMs;
    float m_startRadian;
    mutable float m_curRadian;
    //larger than 10 for non stop
    float m_stopRadian;
    float m_incRadian;
  public:
    OscilleEffect()
    {
      setPeriod();
      m_startRadian = 0;
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
      m_incRadian = 2.0 * M_PI / Effect::getFPS() / (periodMs / 1000.0);
    }

    constexpr bool isDone() const override
    {
      return m_curRadian >= m_stopRadian;
    }

/*    void restart()
    {
      m_curRadian = m_startRadian;
    }
*/

    /**
     * @brief setStartPhase
     * @param startPhase degree in radian on where to start in the sin() function
     * So 0 mean at mean value increasing, PI/2 at max value,
     * PI at mean  value decreasing, -PI/2 at min value
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

    void updateImpl() override
    {

      m_curRadian += m_incRadian;
      if(isDone())
        m_curRadian = m_stopRadian;
      else
        m_curRadian = Parent::getPhaseNormalized(m_curRadian);

      Parent::m_value = Parent::getMapToRange((sin(m_curRadian) + 1) /2);
    }

  };
}
#endif // Effect_H
