/**************************************************************************
** Qt Creator license header template
**   Special keywords: dpinol 06/03/2014 2014
**   Environment variables:
**   To protect a percent sign, use '%'.
**************************************************************************/

#ifndef MOVINGOBJECT_H
#define MOVINGOBJECT_H

#include "GameObject.h"
#include <vector>
#include <utils/Vector2D.h>

class MovingObject : public GameObject
{
public:

  MovingObject();
  typedef std::vector<Vector2D> Trajectory;
  /**
   * @brief setTrajectory
   * @param trajectory will be moved in
   */
  void setTrajectory(Trajectory &trajectory);

  virtual ~MovingObject();

  // load from file - int x, int y, int width, int height, std::string textureID, int numFrames, int callbackID = 0, int animSpeed = 0
  virtual void load(std::unique_ptr<LoaderParams> const &pParams) override;

  // draw the object
  virtual void draw() override;

  // do update stuff
  virtual void update() override;

  // remove anything that needs to be deleted
  virtual void clean() override;


  // get the type of the object
  virtual std::string type() override { return "MovingObject";}

  bool m_done;
  Trajectory m_trajectory;
};

#endif // MOVINGOBJECT_H
