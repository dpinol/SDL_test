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

  /**
   * Update calculates and value which can be checked by get()
   * T is required to have ordering, +, * operators
   */
  template <class T>
  class ValueEffect : public Effect
  {
  public:
    using Effect::resume;
  public:
    inline T const &get() const
    {
      return m_value;
    }

    std::string toString() const override
    {
      return dani::toString(m_value);
    }
  protected:
    T m_value;
  };


#if 0
   typename DISTANCE_FUNCTION
  DISTANCE_FUNCTION m_distanceFunction;
  m_distanceFunction distanceFunction
  * @param tolerance also useful because we cannot assume that m_value==end
  * or that T<= is defined (and we don't know either in which direction we're going)

#endif
  /** Value will take interpolated values within a range during a specified time
   * It does not loose accuracy neither assumes that T/integer is defined
   * (which causes some memory overhead, and hence might make sense to create another subclass which does)
   */
  template <class T>
  class RangeEffect : public ValueEffect<T>
  {
  protected:
    using ValueEffect<T>::m_value;
    T m_start;
    T m_end;
    T m_tolerance;
    int m_durationMs;
    bool m_increasing;
    int m_pendingUpdateCalls, m_totalUpdateCalls;
  public:
    /**
     * @brief setRange
     * @param start
     * @param end
     * @param durationMs
     */
    void setRange(T start, T end, int durationMs)
    {
      m_start = std::move(start);
      m_value = m_start;
      m_end = std::move(end);
      m_durationMs = durationMs;
      m_pendingUpdateCalls = Effect::getFPS() * (durationMs / 1000.0);
      m_totalUpdateCalls = m_pendingUpdateCalls;
      Effect::resume();
    }

    void restart() override
    {
      m_value = m_start;
      m_pendingUpdateCalls = m_totalUpdateCalls;
    }

    bool isDone() const override
    {
      return m_pendingUpdateCalls == 0;
    }

    void updateImpl() override
    {
      if (m_pendingUpdateCalls == 1)
        m_value = m_end;
      else
      {
        m_value =  m_start +
            (m_end - m_start) *((m_totalUpdateCalls - m_pendingUpdateCalls) / m_totalUpdateCalls);
      }
      m_pendingUpdateCalls--;
    }
  };

  /**
   * Effect which will is able to go on forever:
   * eg. with random values, with sinusoidal function..
   */
  template <class T>
  class LoopEffect : public ValueEffect<T>
  {
  protected:
    using ValueEffect<T>::m_value;

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
     * @brief set configures and calls resume()
     * @param mean if paused, will always return this number
     * @param amplitudeRatio  mean - maxDisturbance <= val <= mean + maxDisturbance
     */
    void setMean(T mean, T const &maxDisturbance = 0)
    {
      m_mean = std::move(mean);
      m_maxDisturbance = maxDisturbance;
      Effect::resume();
    }


    /**
     * @brief setRange configures and calls resume()
     * @param min
     * @param max
     */
    void setRange(T const &min, T const &max)
    {
      m_mean = (min + max) / 2.0;
      m_maxDisturbance = (max - min) / 2.0;
      Effect::resume();
    }

  protected:
    T m_mean;
    T m_maxDisturbance;
    //cache so that we can return by ref
    //T m_lastValue;
  }; //RangeEffect


  template <class T>
  class RandomEffect : public LoopEffect<T>
  {
  protected:
    using LoopEffect<T>::m_value;
  public:
    void restart() override
    {
      Effect::resume();
    }

    constexpr bool isDone() const override
    {
      return false;
    }

    void updateImpl() override
    {
        m_value = LoopEffect<T>::getMapToRange(rand() / (float) RAND_MAX);
    }
  }; //RandomEffect




  template <class T>
  class OscilleEffect : public LoopEffect<T>
  {
  protected:
    using LoopEffect<T>::m_value;
    typedef LoopEffect<T> Parent;
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

    void restart() override
    {
      m_curRadian = m_startRadian;
      Effect::resume();
    }


    /**
     * @brief setStartPhase
     * @param startPhase degree in radian on where to start in the sin() function
     * So 0 mean at mean value increasing, PI/2 at max value,
     * PI at mean  value decreasing, -PI/2 at min value
     * startPhase will be normalized
     * calls resume()
     */
    void setStartPhase(float startPhase = 0)
    {
      m_curRadian = Parent::getPhaseNormalized(startPhase);
      Parent::resume();
    }

    /**
     * @brief setStopPhase
     * Calls resume
     * @param stopPhase
     */
    void setStopPhase(float stopPhase)
    {
      m_stopRadian = Parent::getPhaseNormalized(stopPhase);
      Parent::resume();
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
        // we don't want to go past stop radian
        m_curRadian = m_stopRadian;
      else
        m_curRadian = Parent::getPhaseNormalized(m_curRadian);

      m_value = Parent::getMapToRange((sin(m_curRadian) + 1) /2);
    }

  };
}
#endif // Effect_H
