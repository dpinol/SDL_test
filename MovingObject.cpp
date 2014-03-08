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
#include <utils/utils.h>
#include <utils/Effect.h>

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
  m_effects->addChild(m_alpha);
  m_effects->addChild(m_scale);
  TheTextureManager::Instance()->load(imgFilename, "spark");
  int access;
  Uint32 format;
  SDL_Texture *texture = TheTextureManager::Instance()->getTextureMap()["spark"];
  SDL_QueryTexture(texture, &format, &access, &m_width, &m_height);


  /* if (m_maxOscilllationPerc != 0)
  {
    for (int i =0; i < 10; i++)
    {
      //1 - ratio + i * 2 * ratio = 1 - ratio * (-1 + 2*i)
      float r = 1 - (m_maxOscilllationPerc / 100.0) * ( -1 + 2* i / 10.0);
      TheTextureManager::Instance()->load(imgFilename, "spark" + dani::toString(i), NULL, r * m_width, r* m_height);
    }
  }*/
}

MovingObject::~MovingObject()
{  
}

void MovingObject::setRandomSize(float amplitudeRatio)
{
  m_scale.setMean(1, amplitudeRatio);
  m_scale.setPaused();
}

void MovingObject::setAlphaOscillation(float minAlphaRatio)
{
  //m_minAlphaPerc = minAlphaRatio;
  //m_alphaDegree = 0;
  m_alpha.setRange( 255 *  minAlphaRatio, 255);
  m_alpha.setPaused();
}

void MovingObject::setTrajectory(Trajectory &trajectory)
{
  m_trajectory = std::move(trajectory);
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
  float scale = m_scale.get();

  Uint32 x = m_pixel.getX() - m_width * scale / 2;
  Uint32 y = m_pixel.getY() - m_height * scale / 2;

  TextureManager::Instance()->draw("spark", x, y,
                                   m_width, m_height,
                                   NULL, m_angle, m_alpha.get(), scale);

}

// do update stuff
void MovingObject::update()
{
  if (m_done)
    return;
  m_effects->update();
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
    m_angle = m_stepSpeed.angle() * 180.0 / M_PI;
    float stepTimeMs = m_totalTimeMs *  m_stepSpeed.length() / m_totalDistance;
    //m_stepSpeed.normalize();
    //pix/frame = pix / (frame/ sec) / s
    m_stepSpeed /=  TheGame::Instance()->getFPS() * (stepTimeMs / 1000.0);
  }
  m_pixel += m_stepSpeed;

  /*
  if (m_minAlphaPerc != 100)
  {
    m_alphaDegree += 5 * 2.0 * M_PI / TheGame::Instance()->getFPS();
    if (m_alphaDegree > 2 * M_PI)
      m_alphaDegree = 0;
  }*/


  /*  float scale = 1;
  if (m_maxOscilllationPerc != 0)
  {
    //sizeRatio = 1 - (m_minAlpha / 100  + m_deltaIndex
    float randPerc = rand() / (float) RAND_MAX;
    scale =  1 + (m_maxOscilllationPerc / 100.0) * (- 1  + 2 * randPerc);

  }
//  float scale = 1 - (m_maxOscilllationPerc / 100.0) * ( -1 + 2* i / 10.0);

  for(dani::Effect* dist: m_Effects)
  {
    dist->run();
  }*/
}

// remove anything that needs to be deleted
void MovingObject::clean()
{

}

