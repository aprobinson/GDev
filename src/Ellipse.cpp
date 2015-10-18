//---------------------------------------------------------------------------//
//!
//! \file   Ellipse.cpp
//! \author Alex Robinson
//! \brief  The ellipse class definition
//!
//---------------------------------------------------------------------------//

// GDev Includes
#include "Ellipse.hpp"
#include "DBCMacros.hpp"

namespace GDev{

// Constructor
Ellipse::Ellipse( const int center_x_position,
		  const int center_y_position,
		  const int x_axis_size,
		  const int y_axis_size,
		  const unsigned edge_thickness )
  : d_center_x_position( center_x_position ),
    d_center_y_position( center_y_position ),
    d_x_axis_size( x_axis_size ),
    d_y_axis_size( y_axis_size ),
    d_edge_thickness( edge_thickness )
{
  // Make sure the x axis size is valid
  testPrecondition( x_axis_size > 0 );
  // Make sure the y axis size is valid
  testPrecondition( y_axis_size > 0 );
}

// Get the bounding box
void Ellipse::getBoundingBox( SDL_Rect& bounding_box ) const
{
  bounding_box.x = d_center_x_position - d_x_axis_size;
  bounding_box.y = d_center_y_position - d_y_axis_size;
  bounding_box.w = 2*d_x_axis_size;
  bounding_box.h = 2*d_y_axis_size;
}

// Get the bounding box x position
int Ellipse::getBoundingBoxXPosition() const
{
  return d_center_x_position - d_x_axis_size;
}

// Get the bounding box y position
int Ellipse::getBoundingBoxYPosition() const
{
  return d_center_y_position - d_y_axis_size;
}

// Get the bounding box width
int Ellipse::getBoundingBoxWidth() const
{
  return 2*d_x_axis_size;
}

// Get the bounding box height
int Ellipse::getBoundingBoxHeight() const
{
  return 2*d_y_axis_size;
}

// Get the center point
void Ellipse::getCenterPoint( SDL_Point& center ) const
{
  center.x = d_center_x_position;
  center.y = d_center_y_position;
}

// Get the center x position
int Ellipse::getCenterXPosition() const
{
  return d_center_x_position;
}

// Get the center y position
int Ellipse::getCenterYPosition() const
{
  return d_center_y_position;
}

// Check if a point is in (or on) the shape
bool Ellipse::isPointIn( const int x_position,
			 const int y_position ) const
{
  bool is_in = true;

  if( this->evaluateOuter( x_position, y_position ) > 0.0 )
    is_in = false;

  return is_in;
}

// Check if a point is on the shape boundary
bool Ellipse::isPointOn( const int x_position,
			 const int y_position ) const
{
  bool is_on = true;

  if( d_edge_thickness > 0u )
  {
    double outer_location = this->evaluateOuter( x_position, y_position );
    double inner_location = this->evaluateInner( x_position, y_position );
    
    if( outer_location > 0.0 || inner_location < 0.0 )
      is_on = false;
  }
  else
    is_on = false;

  return is_on;
}

// Evaluate the outer ellipse equation (== 0.0 on, > 0.0 out, < 0.0 in)
double Ellipse::evaluateOuter( const double x_position, 
			       const double y_position ) const
{
  double x_term = (x_position-d_center_x_position)/d_x_axis_size;
  x_term *= x_term;

  double y_term = (y_position-d_center_y_position)/d_y_axis_size;
  y_term *= y_term;
  
  return x_term + y_term - 1.0;    
}

// Evaluate the inner ellipse equation (== 0.0 on, > 0.0 out, < 0.0 in)
double Ellipse::evaluateInner( const double x_position, 
			       const double y_position ) const
{
  double x_term = (x_position-d_center_x_position)/
    (d_x_axis_size - d_edge_thickness);
  x_term *= x_term;

  double y_term = (y_position-d_center_y_position)/
    (d_y_axis_size - d_edge_thickness);
  y_term *= y_term;
  
  return x_term + y_term - 1.0;    
}

} // end GDev namespace

//---------------------------------------------------------------------------//
// end Ellipse.cpp
//---------------------------------------------------------------------------//
