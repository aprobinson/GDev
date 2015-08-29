//---------------------------------------------------------------------------//
//!
//! \file   sdl_test_1.cpp
//! \author Alex Robinson
//! \brief  SDL hello world test
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// SDL Includes
#include <SDL2/SDL.h>

// Screen dimensions
const int screen_width_height[2] = {640, 480};

//! SDL Window Test
int main( int argc, char** args )
{
  // The program return
  int return_value = 0;
  
  // Create a window pointer
  SDL_Window* window = NULL;

  // Create a screen surface pointer
  SDL_Surface* screen_surface = NULL;

  // Initialize SDL
  if( SDL_Init( SDL_INIT_VIDEO ) >= 0 )
  {
    // Initialize the SDL window
    window = SDL_CreateWindow( "SDL window test",
			       SDL_WINDOWPOS_UNDEFINED,
			       SDL_WINDOWPOS_UNDEFINED,
			       screen_width_height[0],
			       screen_width_height[1],
			       SDL_WINDOW_SHOWN );

    if( window )
    {
      // Initialize the window surface
      screen_surface = SDL_GetWindowSurface( window );

      // Make the surface white
      SDL_FillRect( screen_surface, 
		    NULL,
		    SDL_MapRGB( screen_surface->format, 0xFF, 0xFF, 0xFF ) );

      // Update the surface
      SDL_UpdateWindowSurface( window );

      // Wait for two seconds
      SDL_Delay( 2000 );
    }
    else
    {
      std::cout << "The window could not be created! SDL_Error: "
		<< SDL_GetError()
		<< std::endl;

      return_value = 1;
    }

    // Destroy the window
    SDL_DestroyWindow( window );

    // Close SDL
    SDL_Quit();
  }
  else
  {
    std::cout << "SDL could not initialize! SDL_Error: "
	      << SDL_GetError()
	      << std::endl;

    return_value = 1;
  }

  return return_value;
}
 
//---------------------------------------------------------------------------//
// end sdl_test_1.cpp
//---------------------------------------------------------------------------//
