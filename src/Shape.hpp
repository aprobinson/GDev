//---------------------------------------------------------------------------//
//!
//! \file   Shape.hpp
//! \author Alex Robinson
//! \brief  The shape base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef GDEV_SHAPE_HPP
#define GDEV_SHAPE_HPP

// SDL Includes
#include <SDL2/SDL.h>

namespace GDev{

//! The shape base class
class Shape
{
  
public:

  //! Default constructor
  Shape()
  { /* ... */ }

  //! Destructor
  virtual ~Shape()
  { /* ... */ }

  //! Get the bounding box
  virtual void getBoundingBox( SDL_Rect& bounding_box ) const = 0;

  //! Get the bounding box x position
  virtual int getBoundingBoxXPosition() const = 0;

  //! Get the bounding box y position
  virtual int getBoundingBoxYPosition() const = 0;

  //! Get the bounding box width
  virtual int getBoundingBoxWidth() const = 0;

  //! Get the bounding box height
  virtual int getBoundingBoxHeight() const = 0;

  //! Get the center point
  virtual void getCenterPoint( SDL_Point& center ) const = 0;

  //! Get the center x position
  virtual int getCenterXPosition() const = 0;

  //! Get the center y position
  virtual int getCenterYPosition() const = 0;

  //! Check if a point is in (or on) the shape
  virtual bool isPointIn( const int x_position,
			  const int y_position ) const = 0;

  //! Check if a point is on the shape boundary
  virtual bool isPointOn( const int x_position,
			  const int y_position ) const = 0;
};

} // end GDev namespace

#endif // end GDEV_SHAPE_HPP

//---------------------------------------------------------------------------//
// end Shape.hpp
//---------------------------------------------------------------------------//
