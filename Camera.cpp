//
//  Camera.cpp
//  SDLPlatformer
//
//  Created by shaun mitchell on 13/04/2013.
//  Copyright (c) 2013 shaun mitchell. All rights reserved.
//

#include "Game.h"
#include "Camera.h"

Camera* Camera::s_pCamera = new Camera();

Camera::Camera() : m_pTarget(0), m_pixel(0,0)
{
    
}

Camera::~Camera()
{
    delete m_pTarget;
}

const Vector2D Camera::getPixel() const
{
    if(m_pTarget != 0)
    {
        Vector2D pos(m_pTarget->getX() - (TheGame::Instance()->getGameWidth() / 2), 0);
        
        if(pos.getX() < 0)
        {
            pos.setX(0);
        }
        
        return pos;
    }
    
    return m_pixel;
    
    
    
//    //Center the camera over the dot
//    camera.x = ( box.x + DOT_WIDTH / 2 ) - SCREEN_WIDTH / 2;
//    camera.y = ( box.y + DOT_HEIGHT / 2 ) - SCREEN_HEIGHT / 2;
//    
//    //Keep the camera in bounds.
//    if( camera.x < 0 )
//    {
//        camera.x = 0;
//    }
//    if( camera.y < 0 )
//    {
//        camera.y = 0;
//    }
//    if( camera.x > LEVEL_WIDTH - camera.w )
//    {
//        camera.x = LEVEL_WIDTH - camera.w;
//    }
//    if( camera.y > LEVEL_HEIGHT - camera.h )
//    {
//        camera.y = LEVEL_HEIGHT - camera.h;
//    }
}

void Camera::update(Vector2D velocity)
{
    m_pixel += velocity;
    
    if(m_pixel.getX() < 0)
    {
        m_pixel.setX(0);
    }
}

