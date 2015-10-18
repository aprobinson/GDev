//---------------------------------------------------------------------------//
//!
//! \file   Rectangle.cpp
//! \author Alex Robinson
//! \brief  The rectangle class definition
//!
//---------------------------------------------------------------------------//

// GDev Includes
#include "Rectangle.hpp"
#include "DBCMacros.hpp"

namespace GDev{

// Constructor
Rectangle::Rectangle( const int x_position,
		      const int y_position,
		      const int width,
		      const int height,
		      const unsigned edge_thickness )
  : d_x_position( x_position ),
    d_y_position( y_position ),
    d_width( width ),
    d_height( height ),
    d_edge_thickness( edge_thickness )
{
  // Make sure the size is valid
  testPrecondition( width > 0 );
  testPrecondition( height > 0 );
}

// Get the bounding box
void Rectangle::getBoundingBox( SDL_Rect& bounding_box ) const
{
  bounding_box.x = d_x_position;
  bounding_box.y = d_y_position;
  bounding_box.w = d_width;
  bounding_box.h = d_height;
}

// Get the bounding box x position
int Rectangle::getBoundingBoxXPosition() const
{
  return d_x_position;
}

// Get the bounding box y position
int Rectangle::getBoundingBoxYPosition() const
{
  return d_y_position;
}

// Get the bounding box width
int Rectangle::getBoundingBoxWidth() const
{
  return d_width;
}

// Get the bounding box height
int Rectangle::getBoundingBoxHeight() const
{
  return d_height;
}

// Get the center point
void Rectangle::getCenterPoint( SDL_Point& center ) const
{
  center.x = d_x_position + d_width/2;
  center.y = d_y_position + d_height/2;
}

// Get the center x position
int Rectangle::getCenterXPosition() const
{
  return d_x_position + d_width/2;
}

// Get the center y position
int Rectangle::getCenterYPosition() const
{
  return d_y_position + d_height/2;
}

// Check if a point is in (or on) the shape
bool Rectangle::isPointIn( const int x_position,
			   const int y_position ) const
{
  bool is_in = true;
  
  if( x_position < d_x_position )
    is_in = false;
  else if( x_position > d_x_position + d_width )
    is_in = false;

  if( y_position < d_y_position )
    is_in = false;
  else if( y_position > d_y_position + d_height )
    is_in = false;

  return is_in;
}

// Check if a point is on the shape boundary
bool Rectangle::isPointOn( const int x_position,
			   const int y_position ) const
{
  bool is_on = true;

  if( d_edge_thickness > 0u )
  {
    // Outside of rectangle
    if( x_position < d_x_position || x_position > d_x_position + d_width )
      is_on = false;
    // Potentially inside
    if( x_position > d_x_position + d_edge_thickness &&
	x_position < d_x_position + d_width - d_edge_thickness )
    {
      // Outside
      if( y_position < d_y_position || y_position > d_y_position + d_height )
	is_on = false;
      // Completely inside
      else if( y_position > d_y_position + d_edge_thickness &&
	       y_position < d_y_position + d_height - d_edge_thickness )
	is_on = false;
    }
    // Potentially on
    else
    {
      // Outside
      if( y_position < d_y_position || y_position > d_y_position + d_height )
	is_on = false;
    }
  }
  else
    is_on = false;
  
  return is_on;
}

} // end GDev namespace

//---------------------------------------------------------------------------//
// end Rectangle.cpp
//---------------------------------------------------------------------------//
