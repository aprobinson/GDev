//---------------------------------------------------------------------------//
//!
//! \file   Button.cpp
//! \author Alex Robinson, Sean Robinson
//! \brief  The button base class definition
//!
//---------------------------------------------------------------------------//

// GDev Includes
#include "Button.hpp"

// Handle the action
void Button::handleAction( const SDL_Event& action )
{
  // Check if the action is a mouse action
  if( action.type == SDL_MOUSEMOTION ||
      action.type == SDL_MOUSEBUTTONDOWN ||
      action.type == SDL_MOUSEBUTTONUP )
  {
    if( this->isMouseInButton() )
    {
      switch( action->type )
      {
        case SDL_MOUSEMOTION:
	  this->handleButtonScrollOver();
	  break;
	  
        case SDL_MOUSEBUTTONDOWN:
	  this->handleButtonPress();
	  break;

        case SDL_MOUSEBUTTONUP:
	  this->handleButtonRelease();
	  break;
      }
    }    
    else
      this->handleDefault();
  }
}

//---------------------------------------------------------------------------//
// end Button.cpp
//---------------------------------------------------------------------------//
