/**************************************************************************
** Qt Creator license header template
**   Special keywords: dpinol 06/03/2014 2014
**   Environment variables:
**   To protect a percent sign, use '%'.
**************************************************************************/
#define _USE_MATH_DEFINES
#include <math.h>
#include "MovingObject.h"
#include "TextureManager.h"
#include "Game.h"
#include <numeric>
#include <SDL2/SDL_render.h>
#include <SDL_image.h>


MovingObject::MovingObject(const std::string &imgFilename, int totalTimeMs, bool center, float rotateSpeed)
  : m_done(false),
    m_totalTimeMs(totalTimeMs),
    m_center(center),
    m_rotateSpeed(rotateSpeed),
    m_angle(0),
    m_trajectoryIndex(0),
    m_minAlphaPerc(100),
    m_alphaDegree(0)
{
  TheTextureManager::Instance()->load(imgFilename, "spark");

}

MovingObject::~MovingObject()
{

}

void MovingObject::setAlphaOscillation(float minAlphaPercentage)
{
  m_minAlphaPerc = minAlphaPercentage;
  m_alphaDegree = 0;
}

void MovingObject::setTrajectory(Trajectory &trajectory)
{
  m_trajectory = std::move(trajectory);

  if (m_center)
  {
    int access;
    Uint32 format;
    SDL_Texture *texture = TheTextureManager::Instance()->getTextureMap()["spark"];
    SDL_QueryTexture(texture, &format, &access, &m_width, &m_height);
  }
  m_trajectoryIndex = 0;
  m_pixel = m_trajectory[0];

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

// load from file - int x, int y, int width, int height, std::string textureID, int numFrames, int callbackID = 0, int animSpeed = 0
void MovingObject::load(std::unique_ptr<LoaderParams> const &pParams)
{

}



// draw the object
void MovingObject::draw()
{
  int w = m_width, h = m_height;
  /* float sizeRatio = 1;
  if (m_minAlpha != 0)
  {
    //sizeRatio = 1 - (m_minAlpha / 100  + m_deltaIndex
    float randPerc = rand() / (float) RAND_MAX;
    sizeRatio =  1 - (m_minAlpha / 100) * 2 * randPerc;
    w *= sizeRatio;
    h *= sizeRatio;
  }*/
  int alpha = 255;

  if (m_minAlphaPerc != 0)
  {
    //float randPerc = rand() / (float) RAND_MAX;
    float oscil0to1 = (cos(m_alphaDegree) + 1) /2;
    alpha = 255 * (1 - (m_minAlphaPerc / 100) * oscil0to1);
  }
  Uint32 x = m_pixel.getX() - m_width / 2;
  Uint32 y = m_pixel.getY() - m_height / 2;

  TextureManager::Instance()->drawFrame("spark", x, y,
                                        w, h,
                                        0, 0,
                                        NULL, m_angle, alpha);

}

// do update stuff
void MovingObject::update()
{
  if (m_done)
    return;
  float dist = (m_pixel - m_trajectory[m_trajectoryIndex]).length();
  if (dist < 2)
  {
    m_trajectoryIndex++;
    if (m_trajectoryIndex == m_trajectory.size())
    {
      m_done = true;
      return;
    }
    m_stepSpeed = (m_trajectory[m_trajectoryIndex] - m_trajectory[m_trajectoryIndex - 1]);
    m_angle = m_stepSpeed.angle() * 2 * M_PI;
    float stepTimeMs = m_totalTimeMs *  m_stepSpeed.length() / m_totalDistance;
    //m_stepSpeed.normalize();
    //pix/frame = pix / (frame/ sec) / s
    m_stepSpeed /=  TheGame::Instance()->getFPS() * (stepTimeMs / 1000.0);
  }
  m_pixel += m_stepSpeed;

  if (m_minAlphaPerc != 100)
  {
    m_alphaDegree += 2.0 * M_PI / TheGame::Instance()->getFPS();
    if (m_alphaDegree > 2 * M_PI)
      m_alphaDegree = 0;
  }

}

// remove anything that needs to be deleted
void MovingObject::clean()
{

}

