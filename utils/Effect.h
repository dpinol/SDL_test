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
#include <functional>
#include <iosfwd>



namespace dani
{

  class Effect
  {
  public:
    /**
     * @brief Effect
     * Effects will start in a non paused state so that isDone() returns true
     * (this avoid having to pause a effect until it's configure)
     * So it's the responsibility of each Effect subclass to call
     * resume() typically after configuring with a setXXX()
     */
    Effect();
    virtual ~Effect();

    /**
     * @brief update if not already done or paused, it calls updateImpl()
     * (in this way we spare a virtual call to updateImpl or isDone)
     * After updateImpl, it calls isDone
     */
    void update();

    void setVerbose(bool verbose = true);
    virtual void setPaused(bool paused = true);
    bool isPaused() const;

    /**
     * @brief restart resets to initial configuration and calls resume
     * @todo separate into restart & restartImpl ( restart would also call resume)
     */
    virtual void restart() = 0;

    /**
     * @brief isDone see nextNext, setSlave
     * when false is returned, updateImpl() will not be called again
     * until resume is called
     * @return
     */
    virtual bool isDone() const = 0;

    /**
     * @brief resume causes updateImpl() to be called again from update()
     * Is not required to restart from first
     * Calls resumeImpl
     */
    void resume();

    /**
     * @brief setNext to sequence effects
     * @param nextEffect when this effect isDone(), nextEffect will be unpaused
     * (will be updated() on same or next iteration, depending on relative order in effects list)
     * nextEffect is automatically paused
     */
    void setNext(Effect *nextEffect);

    /**
     * @brief setNext sets function to be called after effect is done
     * @param f
     */
    void setNext(std::function<void (void)> callback);

    /**
     * @brief setSlave A master will un/pause its slave when it itself un/pauses
     * Also pauses its slaves when isDone()
     * A master will restart its slave when restarted
     * @param slaveEffect
     */
    void setSlave(Effect *slaveEffect);

    /**
     * @brief setFPS If we know the FPS, we spare some Effect class to have a timer to
     * keep a given speed
     * @param FPS how many time per s will the Effect getter be called
     */
    static void setFPS(int FPS);

    virtual std::string toString() const = 0;
  protected:

    virtual void resumeImpl() {}
    virtual void updateImpl()  = 0;

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
    // to know whether we should call setNext
    bool m_isDone;
    Effect *m_next, *m_slave;
    std::function<void (void)> m_callback;
    static int m_FPS;
    bool m_verbose;
  }; //Effect

  class CompositeEffect: public Effect
  {
  public:
    /**
     * @brief CompositeEffect
     * @param ownChildren if true, clear/destructor will delete the children
     * It calls resume on the parent but not on the children
     */
    CompositeEffect(bool ownChildren = false);
    virtual  ~CompositeEffect();
    /**
     * @brief clearChildren removes children (and delete if owned)
     */
    void clearChildren();
    /**
     * @brief addChid
     * @param effect
     */
    void addChild(Effect &effect);
    void setPaused(bool paused = true) override;
    bool isDone() const override;
    void restart() override;
    std::string toString() const;
    std::vector<Effect*>::iterator begin();
    std::vector<Effect*>::iterator end();

  protected:
    virtual void updateImpl() override;
    std::vector<Effect*> m_children;
    bool m_ownChildren;
  };
}
#endif // Effect_H
