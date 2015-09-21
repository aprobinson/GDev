//---------------------------------------------------------------------------//
//!
//! \file   ActionListener.hpp
//! \author Alex Robinson, Sean Robinson
//! \brief  The action listener base class declaration
//!
//---------------------------------------------------------------------------//

// SDL Include
#include <SDL2/SDL.h>

//! The action listener base class
class ActionListener
{
  
public:

  //! Default constructor
  ActionListener()
  { /* ... */ }

  //! Destructor
  virtual ~ActionListener()
  { /* ... */ }

  //! Handle the action
  virtual void handleAction( const SDL_Event& action ) = 0;
};

//---------------------------------------------------------------------------//
// end ActionListener.hpp
//---------------------------------------------------------------------------//
