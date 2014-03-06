/**************************************************************************
** Qt Creator license header template
**   Special keywords: dpinol 06/03/2014 2014
**   Environment variables:
**   To protect a percent sign, use '%'.
**************************************************************************/

#include "MovingObject.h"
#include <TextureManager.h>
#include <numeric>
#include <SDL2/SDL_render.h>
#include <SDL_image.h>


MovingObject::MovingObject(const std::string &imgFilename, int totalTimeMs, bool center, float rotateSpeed)
  : m_done(false),
    m_totalTimeMs(totalTimeMs),
    m_center(center),
    m_rotateSpeed(rotateSpeed),
    m_angle(0),
    m_trajectoryIndex(0)
{
  TheTextureManager::Instance()->load(imgFilename, "spark");
  SDL_Texture *texture = TheTextureManager::Instance()->getTextureMap()["spark"];

  if (m_center)
  {
    int access;
    Uint32 format;
    SDL_QueryTexture(texture, &format, &access, &m_width, &m_height);
    std::for_each(m_trajectory.begin(), m_trajectory.end(), [&](Vector2D &v)
    {
      v.setX( v.getX() - m_width / 2);
      v.setY( v.getY() - m_height / 2);
    });
  }

  Vector2D lastPoint;
  m_totalDistance = std::accumulate(m_trajectory.begin(), m_trajectory.end(), 0.0,
                                    [&](float acc, Vector2D const &p)
  {
    if (!lastPoint.isValid())
    {
      lastPoint = p;
      return 0.0f;
    }
    else
    {
      return (p - lastPoint).length();
    }
  });
}

MovingObject::~MovingObject()
{

}

void MovingObject::setTrajectory(Trajectory &trajectory)
{
  m_trajectory = std::move(trajectory);
  m_trajectoryIndex = 0;
  m_pixel = m_trajectory[0];
}

// load from file - int x, int y, int width, int height, std::string textureID, int numFrames, int callbackID = 0, int animSpeed = 0
void MovingObject::load(std::unique_ptr<LoaderParams> const &pParams)
{

}

// draw the object
void MovingObject::draw()
{
  TextureManager::Instance()->drawFrame("spark", (Uint32)m_pixel.getX(), (Uint32)m_pixel.getY(),
                                        m_width, m_height, 0, 0,
                                        NULL, m_angle);

}

// do update stuff
void MovingObject::update()
{
  if (m_rotateSpeed)
  {
    m_angle = (m_angle + m_rotateSpeed);
    if (m_angle >= 360)
      m_angle-= 360;
    else if  (m_angle < 0)
      m_angle += 360;
  }
  if ((m_pixel - m_trajectory[m_trajectoryIndex]).length() < 2)
  {
    m_trajectoryIndex++;
    if (m_trajectoryIndex == m_trajectory.size())
    {
      m_done = true;
      return;
    }
    m_stepSpeed = (m_trajectory[m_trajectoryIndex] - m_trajectory[m_trajectoryIndex - 1]);
    float stepTimeMs = m_totalTimeMs *  m_stepSpeed.length() / m_totalDistance;
    //m_stepSpeed.normalize();
    m_stepSpeed /= stepTimeMs;
  }
  m_pixel += m_stepSpeed;
}

// remove anything that needs to be deleted
void MovingObject::clean()
{

}

