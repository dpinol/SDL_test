//
//  AnimatedGraphic.cpp
//  SDL Game Programming Book
//
//  Created by shaun mitchell on 17/02/2013.
//  Copyright (c) 2013 shaun mitchell. All rights reserved.
//

#include "AnimatedGraphic.h"

using namespace std;

AnimatedGraphic::AnimatedGraphic() : BoardObject()
{
    
}

void AnimatedGraphic::load(std::unique_ptr<LoaderParams> const &pParams)
{
    BoardObject::load(pParams);
    m_animSpeed = pParams->getAnimSpeed();
}

void AnimatedGraphic::draw()
{
    BoardObject::draw();
}

void AnimatedGraphic::update()
{
    m_currentFrame = int(((SDL_GetTicks() / (1000 / m_animSpeed)) % m_numFrames));
}

void AnimatedGraphic::clean()
{
    BoardObject::clean();
}
