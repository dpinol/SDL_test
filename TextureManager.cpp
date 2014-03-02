//
//  TextureManager.cpp
//  SDL Game Programming Book
//
//  Created by shaun mitchell on 31/12/2012.
//  Copyright (c) 2012 shaun mitchell. All rights reserved.
//
#include "TextureManager.h"
#include "SDL_image.h"
#include "SDL.h"
#include "Game.h"
#include <stdexcept>

TextureManager* TextureManager::s_pInstance = 0;

void TextureManager::load(std::string const &fileName, std::string const &id, SDL_Renderer* pRenderer)
{
    SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());
    
    if(pTempSurface == 0)
    {
      throw std::runtime_error(IMG_GetError());
    }
    
    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);
    
    SDL_FreeSurface(pTempSurface);
    
    if(pTexture != 0)
    {
        m_textureMap[id] = pTexture;
    }
    else
      throw std::runtime_error("Error loading " + fileName + ": " + SDL_GetError());
}
static SDL_Renderer* getRenderer(SDL_Renderer* pRenderer)
{
  if (pRenderer)
    return pRenderer;
  else
    return TheGame::Instance()->getRenderer();
}

void TextureManager::draw(std::string const &id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;
    
    srcRect.x = 0;
    srcRect.y = 0;
    //@todo get size automatic when 0
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
    destRect.x = x;
    destRect.y = y;
    
    SDL_RenderCopyEx(getRenderer(pRenderer), m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::drawFrame(const std::string &id, int x, int y, int width, int height, int currentRow, int currentFrame,
                               SDL_Renderer *pRenderer, double angle, int alpha, SDL_RendererFlip flip)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;
    srcRect.x = width * currentFrame;
    srcRect.y = height * currentRow;
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
    destRect.x = x;
    destRect.y = y;
    
    SDL_SetTextureAlphaMod(m_textureMap[id], alpha);
    SDL_RenderCopyEx(getRenderer(pRenderer), m_textureMap[id], &srcRect, &destRect, angle, 0, flip);
}

void TextureManager::drawTile(std::string const &id, int margin, int spacing, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer *pRenderer)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;
    srcRect.x = margin + (spacing + width) * currentFrame;
    srcRect.y = margin + (spacing + height) * currentRow;
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
    destRect.x = x;
    destRect.y = y;
    
    SDL_RenderCopyEx(getRenderer(pRenderer), m_textureMap[id], &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);
}


void TextureManager::clearTextureMap()
{
    m_textureMap.clear();
}

void TextureManager::clearFromTextureMap(std::string const &id)
{
    m_textureMap.erase(id);
}

