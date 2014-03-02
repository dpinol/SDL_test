//
//  CollisionManager.cpp
//  SDL Game Programming Book
//
//  Created by shaun mitchell on 28/03/2013.
//  Copyright (c) 2013 shaun mitchell. All rights reserved.
//

#include "CollisionManager.h"
#include "Collision.h"
#include "TileLayer.h"

/*
void CollisionManager::checkPlayerEnemyCollision(Player* pPlayer, const std::vector<GameObject*> &objects)
{
    SDL_Rect pRect1;
    pRect1.x = pPlayer->getPixel().getX();
    pRect1.y = pPlayer->getPixel().getY();
    pRect1.w = pPlayer->getWidth();
    pRect1.h = pPlayer->getHeight();

    SDL_Rect pRect2;

    for(int i = 0; i < objects.size(); i++)
    {
        if(objects[i]->type() != std::string("Enemy") || !objects[i]->updating())
        {
            continue;
        }
        
        pRect2.x = objects[i]->getPixel().getX();
        pRect2.y = objects[i]->getPixel().getY();
        pRect2.w = objects[i]->getWidth();
        pRect2.h = objects[i]->getHeight();
        
        if(RectRect(&pRect1, &pRect2))
        {
            if(!objects[i]->dead() && !objects[i]->dying())
            {
                pPlayer->collision();
            }
        }
        
        delete pRect2;
    }
    
    delete pRect1;
}*/
