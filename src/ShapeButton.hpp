//---------------------------------------------------------------------------//
//!
//! \file   ShapeButton.hpp
//! \author Alex Robinson, Sean Robinson
//! \brief  The shape button base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef SHAPE_BUTTON_HPP
#define SHAPE_BUTTON_HPP

// GDev Includes
#include "Button.hpp"

//! The shape button base class
template<typename Shape>
class ShapeButton : public Button
{
  
public:

  //! Constructor
  ShapeButton( const Shape& button_shape );

  //! Destructor
  virtual ~ShapeButton()
  { /* ... */ }

protected:

  //! Test if the mouse position is inside of the button
  bool isMouseInButton() const;

  //! Get the upper left (start) x position
  unsigned getUpperLeftXPos();

  //! Get the upper left (start) y position
  unsigned getUpperRightXPos();

private:

  // The shape of the button
  Shape d_shape;
};

//---------------------------------------------------------------------------//
// Template includes
//---------------------------------------------------------------------------//

#include "ShapeButton_def.hpp"

//---------------------------------------------------------------------------//

#endif //end SHAPE_BUTTON_HPP

//---------------------------------------------------------------------------//
// end ShapeButton.hpp
//---------------------------------------------------------------------------//
