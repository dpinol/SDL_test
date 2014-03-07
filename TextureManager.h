//
//  TextureManager.h
//  SDL Game Programming Book
//
//  Created by shaun mitchell on 31/12/2012.
//  Copyright (c) 2012 shaun mitchell. All rights reserved.
//

#ifndef __TextureManager__
#define __TextureManager__

#include <iostream>
#include <string>
#include <map>
#include "SDL.h"

class TextureManager
{
public:

  static TextureManager* Instance()
  {
    if(s_pInstance == 0)
    {
      s_pInstance = new TextureManager();
      return s_pInstance;
    }

    return s_pInstance;
  }

  /**
     * @brief load an image from disk so that it can be later drawn
     * @param fileName
     * @param id to be used to draw it
     * @param pRenderer
     * @return
     */
  void load(std::string const &fileName, std::string const &id, SDL_Renderer* pRenderer = 0);

  void clearTextureMap();
  void clearFromTextureMap(std::string const &id);

  /**
     * @brief draw
     * @param id as specified at load
     * @param x for top left corner to be painted at
     + @param y for top left corner to be painted at
     * @param width at the original file. Will be drawn as per width * scale
     * @param height at the original file. Will be drawn as per height * scale
     * @param pRenderer
     * @param scale 1 for keeping source size
     * @param flip
     */
  void draw(std::string const &id, int x, int y, int width, int height, SDL_Renderer* pRenderer = 0, double angle = 0, int alpha = 255,
            double scale = 1.0, SDL_RendererFlip flip = SDL_FLIP_NONE);
  /**
     * @brief drawFrame
     * @param id
     * @param currentRow row within the sprite sheet
     * @param currentFrame frame with the row
     * @param pRenderer by default, the general one
     * @param angle
     * @param alpha
     * @param flip
     */
  void drawFrame(std::string const &id, int x, int y, int width, int height, int currentRow = 0, int currentFrame = 0,
                 SDL_Renderer* pRenderer = 0, double angle = 0, int alpha = 255, SDL_RendererFlip flip = SDL_FLIP_NONE);
  void drawTile(std::string const &id, int margin, int spacing, int x, int y, int width, int height,
                int currentRow, int currentFrame, SDL_Renderer *pRenderer);

  std::map<std::string, SDL_Texture*> getTextureMap() const { return m_textureMap; }

private:

  TextureManager() {}
  ~TextureManager() {}

  TextureManager(const TextureManager&);
  TextureManager& operator=(const TextureManager&);

  std::map<std::string, SDL_Texture*> m_textureMap;

  static TextureManager* s_pInstance;
};

typedef TextureManager TheTextureManager;

#endif /* defined(__SDL_Game_Programming_Book__TextureManager__) */
