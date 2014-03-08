//
//  GameObject.h
//  SDL Game Programming Book
//
//  Created by shaun mitchell on 06/01/2013.
//  Copyright (c) 2013 shaun mitchell. All rights reserved.
//

#ifndef SDL_Game_Programming_Book_GameObject_h
#define SDL_Game_Programming_Book_GameObject_h

//#include <boost/archive/xml_oarchive.hpp>
//#include <boost/archive/xml_iarchive.hpp>
#include "LoaderParams.h"
#include <utils/Vector2D.h>
#include <string>
#include <memory>
#include <vector>

namespace dani
{
  class CompositeEffect;
}

class GameObject
{
public:
    
    // base class needs virtual destructor
    virtual ~GameObject();
    
    // load from file - int x, int y, int width, int height, std::string textureID, int numFrames, int callbackID = 0, int animSpeed = 0
    virtual void load(std::unique_ptr<LoaderParams> const &pParams) = 0;
    
    // draw the object
    virtual void draw() = 0;
    
    // do update stuff
    virtual void update();
    
    // remove anything that needs to be deleted
    virtual void clean();
    
    
    // get the type of the object
    virtual std::string type() = 0;
    
    // getters for common variables
    Vector2D& getPixel() { return m_pixel; }
    Vector2D const& getPixel() const { return m_pixel; }
    Vector2D& getVelocity() { return m_velocity; }
    Vector2D const& getVelocity() const { return m_velocity; }
    
    int getWidth() { return m_width; }
    int getHeight() { return m_height; }
   
    // scroll along with tile map
    void scroll(float scrollSpeed)
    {
        if(type() != std::string("Player")) // player is never scrolled
        {
            m_pixel.setX(m_pixel.getX() - scrollSpeed);
        }
    }
    
    // is the object currently being updated?
    bool updating() { return m_bUpdating; }
    
    // is the object dead?
    bool isDead() const { return m_bDead; }
    
    // is the object doing a death animation?
    bool isDying() const { return m_bDying; }
    
    // set whether to update the object or not
    void setUpdating(bool updating) { m_bUpdating = updating; }
    
        
protected:
    
    // constructor with default initialisation list
    GameObject() ;

    // movement variables
    Vector2D m_pixel;
    Vector2D m_velocity;
    Vector2D m_acceleration;
    
    // size variables
    int m_width;
    int m_height;
    
    // animation variables
    int m_currentRow;
    int m_currentFrame;
    int m_numFrames;
    std::string m_textureID;
    
    // common boolean variables
    bool m_bUpdating;
    bool m_bDead;
    bool m_bDying;
    // how long the death animation takes, along with a counter
    int m_dyingTime;
    int m_dyingCounter;

    // rotation
    double m_angle;
    
    // blending
    int m_alpha;
    std::unique_ptr<dani::CompositeEffect> m_effects;
    
};

#endif
