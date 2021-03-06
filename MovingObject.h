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
#include <utils/ValueEffect.h>
#include <memory>

class MovingObject : public GameObject
{
public:

  /**
   * @brief MovingObject
   * @param imgFilename filename of image to display
   * @param center whether image should be centered to each position
   */
  MovingObject(std::string const &imgFilename, int totalTimeMs, bool center = false, float rotateSpeed = 0);
  virtual ~MovingObject();

  /**
   * @brief setAlphaOscillation image alpha value will gradually loop
   * @param minAlphaRatio if 0.75, it will oscille betwen 192 and 255
   */
  void setAlphaOscillation(float minAlphaRatio = 0.0);

  /**
   * @brief setSizeOscillation image scale will random change
   * @param amplitudeRatio if 0.1, size will oscille betwen x0.9 and x1.1
   */
  void setRandomSize(float amplitudeRatio = 0.0);


  typedef std::vector<Vector2D> Trajectory;
  /**
   * @brief setTrajectory
   * @param trajectory will be moved in
   */
  void setTrajectory(Trajectory &trajectory);



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
  bool const m_center;
  float const m_rotateSpeed;
  float m_angle;
  Trajectory m_trajectory;
  int m_trajectoryIndex;
  float m_totalDistance;
  Vector2D m_stepSpeed;
  int m_totalTimeMs;

  dani::RandomEffect<float> m_scale;
  dani::OscilleEffect<float> m_alpha;
};

#endif // MOVINGOBJECT_H
