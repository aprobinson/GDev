//---------------------------------------------------------------------------//
//!
//! \file   ShapeButton_def.hpp
//! \author Alex Robinson
//! \brief  The shape button base class definition
//!
//---------------------------------------------------------------------------//

#ifndef SHAPE_BUTTON_DEF_HPP
#define SHAPE_BUTTON_DEF_HPP

// SDL Includes
#include <SDL2/SDL.h>

// Constructor
template<typename Shape>
ShapeButton<Shape>::ShapeButton( const Shape& button_shape )
  : d_shape( button_shape )
{ /* ... */ }

// Test if the mouse position is inside of the button
template<typename Shape>
bool ShapeButton<Shape>::isMouseInButton() const
{
  // Get the mouse position
  int mouse_x_pos, mouse_y_pos;

  SDL_GetMouseState( &mouse_x_pos, &mouse_y_pos );

  return d_shape.isPointInShape( mouse_x_pos, mouse_y_pos );
}

#endif // end SHAPE_BUTTON_DEF_HPP

//---------------------------------------------------------------------------//
// end ShapeButton_def.hpp
//---------------------------------------------------------------------------//
