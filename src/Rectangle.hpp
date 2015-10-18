//---------------------------------------------------------------------------//
//!
//! \file   Rectangle.hpp
//! \author Alex Robinson
//! \brief  The rectangle class declaration
//!
//---------------------------------------------------------------------------//

#ifndef GDEV_RECTANGLE_HPP
#define GDEV_RECTANGLE_HPP

// GDev Includes
#include "Shape.hpp"

namespace GDev{

//! The rectangle class
class Rectangle : public Shape
{
  
public:

  //! Constructor
  Rectangle( const int x_position,
	     const int y_position,
	     const int width,
	     const int height,
	     const unsigned edge_thickness = 0u );

  //! Destructor
  ~Rectangle()
  { /* ... */ }

  //! Get the bounding box
  void getBoundingBox( SDL_Rect& bounding_box ) const;

  //! Get the bounding box x position
  int getBoundingBoxXPosition() const;

  //! Get the bounding box y position
  int getBoundingBoxYPosition() const;

  //! Get the bounding box width
  int getBoundingBoxWidth() const;

  //! Get the bounding box height
  int getBoundingBoxHeight() const;

  //! Get the center point
  void getCenterPoint( SDL_Point& center ) const;

  //! Get the center x position
  int getCenterXPosition() const;

  //! Get the center y position
  int getCenterYPosition() const;

  //! Check if a point is in (or on) the shape
  bool isPointIn( const int x_position,
		  const int y_position ) const;

  //! Check if a point is on the shape boundary
  bool isPointOn( const int x_position,
		  const int y_position ) const;

private:

  // The x position
  int d_x_position;
  
  // The y position
  int d_y_position;

  // The width
  int d_width;
  
  // The height
  int d_height;

  // The edge thickness
  unsigned d_edge_thickness;
};

} // end GDev namespace

#endif // end GDEV_RECTANGLE_HPP

//---------------------------------------------------------------------------//
// end Rectangle.hpp
//---------------------------------------------------------------------------//
