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
#include <memory>
#include <vector>

namespace dani
{

  class Effect
  {
  public:
    Effect(bool paused = false);



    virtual void update() = 0;
    virtual void setPaused(bool paused = true);
    virtual bool isPaused() const;
    /**
     * @brief isDone see nextNext, setSlave
     * @return
     */
    virtual bool isDone() const = 0;

    virtual void restart() = 0;
    /**
     * @brief setNext to sequence effects
     * @param nextEffect when this effect isDone(), nextEffect will be unpaused
     * nextEffect is automatically paused
     */
    void setNext(Effect *nextEffect);

    /**
     * @brief setSlave a master u/pauses its slaved whe it itself un/pauses
     * Also pauses its slaves when isDone()
     * @param slaveEffect
     */
    void setSlave(Effect *slaveEffect);

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
    Effect *m_next, *m_slave;
    static int m_FPS;
  }; //Effect

  class CompositeEffect: public Effect
  {
    void addChid(std::unique_ptr<Effect>);
    virtual void update() override;
  private:
    std::vector<std::unique_ptr<Effect>> m_children;
  };
}
#endif // Effect_H
