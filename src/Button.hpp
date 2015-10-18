//---------------------------------------------------------------------------//
//!
//! \file   Button.hpp
//! \author Alex Robinson, Sean Robinson
//! \brief  The button base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef GDEV_BUTTON_HPP
#define GDEV_BUTTON_HPP

// SDL Include
#include <SDL2/SDL.h>

// GDev Includes
#include "ActionListener.hpp"
#include "RenderableObject.hpp"

namespace GDev{

//! The button base class
class Button : public ActionListener, public RenderableObject
{
  
public:

  //! Default constructor
  Button()
  { /* ... */ }

  //! Destructor
  virtual ~Button()
  { /* ... */ }

  //! Handle the action
  void handleAction( const SDL_Event& action );

protected:

  //! Handle default
  virtual void handleDefault() = 0;

  //! Handle button scroll over 
  virtual void handleButtonScrollOver() = 0;

  //! Handle button press
  virtual void handleButtonPress() = 0;

  //! Handle button release
  virtual void handleButtonRelease() = 0;

  // Test if the mouse position is inside of the button
  virtual bool isMouseInButton() const = 0;
};

} // end GDev namespace

#endif // end BUTTON_HPP

//---------------------------------------------------------------------------//
// end Button.hpp
//---------------------------------------------------------------------------//
