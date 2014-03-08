/**************************************************************************
** Qt Creator license header template
**   Special keywords: dpinol 07/03/2014 2014
**   Environment variables:
**   To protect a percent sign, use '%'.
**************************************************************************/

#ifndef Effect_H
#define Effect_H

#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <utility>

namespace dani
{

  class Effect
  {
  public:
    Effect(bool paused = false)
      :m_paused(paused)
    {
    }



    virtual void update() = 0;
    virtual void setPaused(bool paused = true);
    virtual bool isPaused() const;
    virtual void restart() = 0;
    /**
     * @brief setFPS If we know the FPS, we spare some Effect class to have a timer to
     * keep a given speed
     * @param FPS how many time per s will the Effect getter be called
     */
    static void setFPS(int FPS);
  protected:
    /**
     * @brief getPhaseNormalized normalizes to range [-PI,PI]
     * PI is also allowed because otherwise we could not express a whole loop
     * @param phase
     * @return
     */
    static float getPhaseNormalized(float phase);

    static int getFPS();
    bool m_paused;
  private:
    static int m_FPS;
  };}
#endif // Effect_H
