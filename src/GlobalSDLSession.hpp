//---------------------------------------------------------------------------//
//!
//! \file   GlobalSDLSession.hpp
//! \author Alex Robinson
//! \brief  The global SDL session class declaration
//!
//---------------------------------------------------------------------------//

#ifndef GDEV_GLOBAL_SDL_SESSION_HPP
#define GDEV_GLOBAL_SDL_SESSION_HPP

// Std Lib Includes
#include <iostream>

// SDL Includes
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

namespace GDev{

//! Initialize, finalize, and query the global SDL session
class GlobalSDLSession
{

public:
  
  //! Default constructor
  GlobalSDLSession( std::ostream* out = &std::cout );
  
  //! Destructor
  ~GlobalSDLSession();
  
  //! Check if SDL is initialized
  static bool isSDLInitialized();

  //! Check if SDL is finalized
  static bool isSDLFinalized();

private:

  // Initialize SDL
  static void initialize( std::ostream* out );

  // Records if SDL has been initialized 
  static bool s_sdl_initialized;

  // Records if SDL has been finalized
  static bool s_sdl_finalized;
};

} // end GDev namespace

#endif // end GDEV_GLOBAL_SDL_SESSION_HPP

//---------------------------------------------------------------------------//
// end GlobalSDLSession.hpp
//---------------------------------------------------------------------------//
