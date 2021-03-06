//
//  Vector2D.h
//  SDL Game Programming Book
//
//  Created by shaun mitchell on 27/01/2013.
//  Copyright (c) 2013 shaun mitchell. All rights reserved.
//

#ifndef __SDL_Game_Programming_Book__Vector2D__
#define __SDL_Game_Programming_Book__Vector2D__

#include <iostream>
#include <math.h>

/**
 * @brief The Vector2D class
 * @todo change to Board position?
 */
class Vector2D
{
public:
    Vector2D()
    {
        m_x = -1;
        m_y = -1;
    }
    
    Vector2D(float x, float y): m_x(x), m_y(y) {}

    void clear()
    {
      m_x = m_y = -1;
    }

    bool isValid() const
    {
      return m_x >= 0 && m_y >= 0;
    }
    
    inline float getX() const { return m_x; }
    inline float getY() const { return m_y; }
    
    void setX(float x) { m_x = x; }
    void setY(float y) { m_y = y; }
    
    float length() const { return sqrt(m_x * m_x + m_y * m_y); }

    /**
     * @brief angle will be 0 when y is 0
     * @return angle in radians with respect to x axis
     */
    float angle() const { return atan( m_y /m_x);}
    
    Vector2D operator+(const Vector2D& v2) const { return Vector2D(m_x + v2.getX(), m_y + v2.getY()); }
    friend Vector2D& operator+=(Vector2D& v1, const Vector2D& v2)
    {
        v1.m_x += v2.getX();
        v1.m_y += v2.getY();
        
        return v1;
    }
    
    Vector2D operator-(const Vector2D& v2) const { return Vector2D(m_x - v2.getX(), m_y - v2.getY()); }
    friend Vector2D& operator-=(Vector2D& v1, const Vector2D& v2)
    {
        v1.m_x -= v2.getX();
        v1.m_y -= v2.getY();
        
        return v1;
    }

    
    Vector2D operator*(float scalar) const
    {
        return Vector2D(m_x * scalar, m_y * scalar);
    }
    
    Vector2D& operator*=(float scalar)
    {
        m_x *= scalar;
        m_y *= scalar;
        
        return *this;
    }
    
    Vector2D operator/(float scalar) const
    {
        return Vector2D(m_x / scalar, m_y / scalar);
    }
    
    Vector2D& operator/=(float scalar)
    {
        m_x /= scalar;
        m_y /= scalar;
        
        return *this;
    }

    /**
    * @brief isInside
    * @param topLeft
    * @param bottomDown
    * @return whether this lies within the rectangle (excluding bottomDown.getX and bottomDown.getY)
    */
   inline bool isInside(const Vector2D &topLeft, const Vector2D &bottomDown) const
   {
     return topLeft.getX() <= getX() && topLeft.getY() <= getY()
         && bottomDown.getX() > getX() && bottomDown.getY() > getY();
   }
    
    void normalize()
    {
        int l = length();
        if ( l > 0)
        {
            (*this) *= 1 / l;
        }
    }
private:
    float m_x;
    float m_y;
};

inline std::ostream& operator<<(std::ostream& os, const Vector2D& obj)
{
  os << "(" << obj.getX() << "," << obj.getY() << ")";
  return os;
}



#endif /* defined(__SDL_Game_Programming_Book__Vector2D__) */
