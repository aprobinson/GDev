//---------------------------------------------------------------------------//
//!
//! \file   sdl_test_5.cpp
//! \author Alex Robinson
//! \brief  Display stretched bitmap with sdk
//! 
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <string>

// Boost Includes
#include <boost/program_options/variables_map.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/cmdline.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/positional_options.hpp>

// SDL Includes
#include <SDL2/SDL.h>

// The window we'll be rendering to
SDL_Window* g_window = NULL;
    
// The surface contained by the window
SDL_Surface* g_screen_surface = NULL;

// The image we will load and show on the screen
SDL_Surface* g_stretched_surface = NULL;

// The screen dimensions
const int screen_width_height[2] = {640,480};

//! initialize sdl window
bool initialize()
{
  // Initialization flag
  bool success = true;

  // Initialize SDL
  if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
  {
    std::cerr << "SDL could not initialize. SDL_Error: "
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
				 screen_width_height[0],
				 screen_width_height[1],
				 SDL_WINDOW_SHOWN );
    if( g_window == NULL )
    {
      std::cerr << "Window could not be created. SDL_Error: "
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

//! Load the image file and allocate the surface
SDL_Surface* loadSurface( const std::string& filename )
{
  // The final optimized image
  SDL_Surface* optimized_surface = NULL;

  // Load the image
  SDL_Surface* loaded_surface = SDL_LoadBMP( filename.c_str() );

  if( loaded_surface == NULL )
  {
    std::cerr << "Unable to load image " << filename << "! SDL Error: "
	      << SDL_GetError() << std::endl;
  }
  else
  {
    // Convert surface to screen format
    optimized_surface = SDL_ConvertSurface( loaded_surface, 
					    g_screen_surface->format,
					    NULL );

    if( optimized_surface == NULL )
    {
      std::cerr << "Unable to optimize image " << filename << "! SDL Error: "
		<< SDL_GetError()
		<< std::endl;
    }

    // Free the old loaded surface
    SDL_FreeSurface( loaded_surface );
  }

  return optimized_surface;
}

//! Load image file
bool loadMedia( const std::string& filename )
{
  bool success = true;
  
  // Load desired bitmap
  g_stretched_surface = loadSurface( filename );
  
  if( g_stretched_surface == NULL )
  {
    std::cerr << "Can't load image "
	      << filename
	      << " SDL_Error: "
	      << SDL_GetError()
	      << std::endl;
    success = false;
  }
  return success;
}

//! Close SDL_Window
void close()
{
  // Free surface
  SDL_FreeSurface( g_stretched_surface );
  g_stretched_surface = NULL;

  // Destroy window
  SDL_DestroyWindow( g_window );
  g_window = NULL;

  SDL_Quit();
}

int main( int argc, char** argv )
{
  // Create the hidden program options (required args)
  boost::program_options::options_description hidden( "Hidden options" );
  hidden.add_options()
    ("image",
     boost::program_options::value<std::string>(),
     "the image (with path) that will be used\n");

  // Create the positional (required) args
  boost::program_options::positional_options_description pd;
  pd.add("image", 1 );

  // Create the optional arguments
  boost::program_options::options_description generic( "Allowed options" );
  generic.add_options()
    ("help,h", "produce help message");

  // Create the command-line argument parser
  boost::program_options::options_description
    cmdline_options( "Allowed options" );
  cmdline_options.add(generic).add(hidden);

  boost::program_options::variables_map vm;
  boost::program_options::store( boost::program_options::command_line_parser(argc, argv).options(cmdline_options).positional(pd).run(), vm );
  boost::program_options::notify( vm );

  // Check if the help message was requested
  if( vm.count( "help" ) )
  {
    std::cerr << generic << std::endl;
    
    return 1;
  }

  // Store the image name
  std::string image_name;

  if( vm.count( "image" ) )
    image_name = vm["image"].as<std::string>();
  else
  {
    std::cerr << "The default image (with path) must be specified."
	      << std::endl;
    
    return 1;
  }
  
  // Initialize the window
  if( !initialize() )
  {
    return 1;
  }
  else
  {
    // Load the bitmap
    if( !loadMedia( image_name ))
    {
      return 1;
    }
    else
    {
      bool quit = false;

      // Event
      SDL_Event event;

      // Main application loop
      while( !quit )
      {
	while( SDL_PollEvent( &event ) != 0 )
	{
	  if( event.type == SDL_QUIT )
	    quit = true;
	}

	// Apply the image stretch
	SDL_Rect stretch_rect;
	stretch_rect.x = 0;
	stretch_rect.y = 0;
	stretch_rect.w = screen_width_height[0];
	stretch_rect.h = screen_width_height[1];
	
	SDL_BlitScaled( g_stretched_surface, 
			NULL, 
			g_screen_surface, 
			&stretch_rect );

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
