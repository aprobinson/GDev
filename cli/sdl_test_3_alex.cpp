//---------------------------------------------------------------------------//
//!
//! \file   sdl_test_3_alex.cpp
//! \author Alex Robinson
//! \brief  using event queue to display bitmap with sdk
//! 
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <string>

// SDL Includes
#include <SDL2/SDL.h>

// The window we'll be rendering to
SDL_Window* g_window = NULL;
    
// The surface contained by the window
SDL_Surface* g_screen_surface = NULL;

// The image we will load and show on the screen
SDL_Surface* g_bitmap = NULL;

//! initialize sdl window
bool initialize()
{
  // Initialization flag
  bool success = true;

  // Initialize SDL
  if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
  {
    std::cout << "SDL could not initialize. SDL_Error: "
	      << SDL_GetError()
	      << std::endl;
    success = false;
  }
  else
  {
    // Create window
    g_window = SDL_CreateWindow( "SDL Tutorial",
				 SDL_WINDOWPOS_UNDEFINED,
				 SDL_WINDOWPOS_UNDEFINED,
				 640,
				 480,
				 SDL_WINDOW_SHOWN );
    if( g_window == NULL )
    {
      std::cout << "Window could not be created. SDL_Error: "
		<< SDL_GetError()
		<< std::endl;
      success = false;
    }
    else
    {
      // Get window surfacce
      g_screen_surface = SDL_GetWindowSurface( g_window );
    }
  }
  return success;
}

//! Load image file
bool loadMedia( const std::string& filename )
{
  bool success = true;
  
  // Load desired bitmap
  g_bitmap = SDL_LoadBMP( filename.c_str() );
  
  if( g_bitmap == NULL )
  {
    std::cout << "Can't load image " << filename
	      << " SDL_Error: " << SDL_GetError()
	      << std::endl;
    success = false;
  }
  return success;
}

//! Close SDL_Window
void close()
{
  // Free surface
  SDL_FreeSurface( g_bitmap );
  g_bitmap = NULL;

  // Destroy window
  SDL_DestroyWindow( g_window );
  g_window = NULL;

  SDL_Quit();
}

int main( int argc, char** args )
{
  std::string bitmap_name;

  // Verify a bitmap has been passed
  if( argc != 2 )
  {
    std::cerr << "User must supply single argument!" << std::endl;
   
    return 1;
  }
  else
  {
    bitmap_name = args[1];
  }
  
  if( !initialize() )
  {
    return 1;
  }
  else
  {
    // Load the bitmap
    if( !loadMedia( bitmap_name ))
    {
      return 1;
    }
    else
    {
      // The main loop flag
      bool quit = false;
      
      // SDL event handler
      SDL_Event event;

      // "Game" loop
      while( !quit )
      {
	// Handle events on the queue
	while( SDL_PollEvent( &event ) != 0 )
	{
	  // User requests quit
	  if( event.type == SDL_QUIT )
	    quit = true;
	}

	// Print image
	SDL_BlitSurface( g_bitmap, NULL, g_screen_surface, NULL);
	SDL_UpdateWindowSurface( g_window );
      }
    }
  }
  
  // Close program
  close();

  return 0;
}

  

//---------------------------------------------------------------------------//
// end sdl_test_2.cpp
//---------------------------------------------------------------------------//
