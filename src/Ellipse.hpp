//---------------------------------------------------------------------------//
//!
//! \file   Ellipse.hpp
//! \author Alex Robinson
//! \brief  The ellipse class declaration
//! 
//---------------------------------------------------------------------------//

#ifndef GDEV_ELLIPSE_HPP
#define GDEV_ELLIPSE_HPP

// GDev Includes
#include "Shape.hpp"

namespace GDev{

/*! The ellipse class 
 * \details \f$\left(\frac{x-x_0}{a}\right^2 +\left(\frac{y-y_0}{b}\right)^2\f$
 */
class Ellipse : public Shape
{
  
public:

  //! Constructor
  Ellipse( const int center_x_position,
	   const int center_y_position,
	   const int x_axis_size,
	   const int y_axis_size,
	   const unsigned edge_thickness = 0u );

  //! Destructor
  ~Ellipse()
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

  // Evaluate the outer ellipse equation (== 0.0 on, > 0.0 out, < 0.0 in)
  double evaluateOuter( const double x_position, 
			const double y_position ) const;

  // Evaluate the inner ellipse equation
  double evaluateInner( const double x_position,
			const double y_position ) const;

  // The center x position
  int d_center_x_position;

  // The center y position
  int d_center_y_position;
  
  // The x axis size (a)
  int d_x_axis_size;

  // The y axis size (b)
  int d_y_axis_size;

  // The edge thickness
  unsigned d_edge_thickness;
};

} // end GDev namespace

#endif // end GDEV_ELLIPSE_HPP

//---------------------------------------------------------------------------//
// end Ellipse.hpp
//---------------------------------------------------------------------------//
