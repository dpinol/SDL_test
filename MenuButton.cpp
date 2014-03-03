//
//  MenuObject.cpp
//  SDL Game Programming Book
//
//  Created by shaun mitchell on 10/02/2013.
//  Copyright (c) 2013 shaun mitchell. All rights reserved.
//

#include "MenuButton.h"
#include "InputHandler.h"

MenuButton::MenuButton() : BoardObject(), m_callback(0), m_bReleased(true)
{
}

void MenuButton::load(std::unique_ptr<LoaderParams> const &pParams)
{
    BoardObject::load(std::move(pParams));
    m_callbackID = pParams->getCallbackID();
    m_currentFrame = MOUSE_OUT;
}

void MenuButton::draw()
{
    BoardObject::draw();
}

void MenuButton::update()
{
    Vector2D const &pMousePos = TheInputHandler::Instance()->getMousePosition();

    //@todo implement isInside
    if(pMousePos.getX() < (m_pixel.getX() + m_width) && pMousePos.getX() > m_pixel.getX()
       && pMousePos.getY() < (m_pixel.getY() + m_height) && pMousePos.getY() > m_pixel.getY())
    {
        if(TheInputHandler::Instance()->getMouseButtonState(LEFT) && m_bReleased)
        {
            m_currentFrame = CLICKED;
            
            if(m_callback != 0)
            {
                m_callback();
            }
            
            m_bReleased = false;
        }
        else if(!TheInputHandler::Instance()->getMouseButtonState(LEFT))
        {
            m_bReleased = true;
            m_currentFrame = MOUSE_OVER;
        }
    }
    else
    {
        m_currentFrame = MOUSE_OUT;
    }
}

void MenuButton::clean()
{
    BoardObject::clean();
}
