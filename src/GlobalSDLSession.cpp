//---------------------------------------------------------------------------//
//!
//! \file   GlobalSDLSession.cpp
//! \author Alex Robinson
//! \brief  The global sdl session class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <exception>

// GDev Includes
#include "GlobalSDLSession.hpp"
#include "ExceptionTestMacros.hpp"
#include "DBCMacros.hpp"

namespace GDev{

bool GlobalSDLSession::s_sdl_initialized = false;
bool GlobalSDLSession::s_sdl_finalized = false;

// Default constructor
GlobalSDLSession::GlobalSDLSession( std::ostream* out )
{
  // Make sure the output stream is valid
  testPrecondition( out );
  
  Uint32 sdl_subsystem_init = 
    SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER | SDL_INIT_EVENTS;

  if( SDL_WasInit( sdl_subsystem_init ) & sdl_subsystem_init )
  {
    *out << "GlobalSDLSession(): Error, SDL_WasInit() returned true, "
	 << "calling std::terminate()!"
	 << std::endl;

    std::terminate();
  }

  if( TTF_WasInit() == 1 )
  {
    *out << "GlobalSDLSession(): Error, TTF_WasInit() returned true, "
	 << "calling std::terminate()!"
	 << std::endl;

    std::terminate();
  }

  // Initialize SDL
  SDL_Init( sdl_subsystem_init );

  // Initialize the text extension library
  if( TTF_Init() != 0 )
  {
    *out << "GlobalSDLSession(): Error, TTF_Init() failed, "
	 << "calling std::terminate()!"
	 << std::endl;
  }

  // Initialize the image extension library
  int image_file_flags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF;

  if( IMG_Init(image_file_flags) != image_file_flags )
  {
    *out << "GlobalSDLSession(): Error, IMG_Init() failed, "
	 << "calling std::terminate()!"
	 << std::endl;
  }

  initialize(out);
}
  
// Destructor
GlobalSDLSession::~GlobalSDLSession()
{
  // Finalize SDL
  SDL_Quit();

  // Finalize TTF
  TTF_Quit();

  // Finalize IMG
  IMG_Quit();
  
  s_sdl_initialized = false;
  s_sdl_finalized = true;
}
  
// Check if SDL is initialized
bool GlobalSDLSession::isSDLInitialized()
{
  return s_sdl_initialized;
}

// Check if SDL is finalized
bool GlobalSDLSession::isSDLFinalized()
{
  return s_sdl_finalized;
}

// Initialize SDL
void GlobalSDLSession::initialize( std::ostream* out )
{
  // SDL has already been finalized - don't do anything
  if( s_sdl_finalized )
    return;

  s_sdl_finalized = false;

  // SDL has already been initialized - don't do anything
  if( s_sdl_initialized )
    return;

  s_sdl_initialized = true;
}

} // end GDev namespace

//---------------------------------------------------------------------------//
// end GlobalSDLSession.cpp
//---------------------------------------------------------------------------//
