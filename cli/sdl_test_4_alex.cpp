//---------------------------------------------------------------------------//
//!
//! \file   sdl_test_3_alex.cpp
//! \author Alex Robinson
//! \brief  using event queue to display bitmap with sdk
//! 
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <stdlib.h>
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

// Key press surface constants
enum KeyPressSurfaceTypes
{
  KEY_PRESS_SURFACE_DEFAULT = 0,
  KEY_PRESS_SURFACE_UP,
  KEY_PRESS_SURFACE_DOWN,
  KEY_PRESS_SURFACE_LEFT,
  KEY_PRESS_SURFACE_RIGHT,
  KEY_PRESS_SURFACE_TOTAL
};

// The window we'll be rendering to
SDL_Window* g_window = NULL;
    
// The surface contained by the window
SDL_Surface* g_screen_surface = NULL;

// The images we will load and show on the screen for a keypress
SDL_Surface* g_key_press_surfaces[KEY_PRESS_SURFACE_TOTAL];

// The currenty displayed image
SDL_Surface* g_current_surface = NULL;

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
				 640,
				 480,
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

//! Load image onto surface
SDL_Surface* loadSurface( const std::string& filename )
{
  // Load the desired image
  SDL_Surface* loaded_surface = SDL_LoadBMP( filename.c_str() );

  if( loaded_surface == NULL )
  {
    std::cerr << "Unable to load image " << filename
	      << "! SDL Error: " << SDL_GetError()
	      << std::endl;
  }

  return loaded_surface;
}

//! Load image files
bool loadMedia( const std::string& press_filename,
		const std::string& up_filename,
		const std::string& down_filename,
		const std::string& left_filename,
		const std::string& right_filename )
{
  bool success = true;
  
  // Load default surface
  g_key_press_surfaces[KEY_PRESS_SURFACE_DEFAULT] =
    loadSurface( press_filename );
  
  if( !g_key_press_surfaces[KEY_PRESS_SURFACE_DEFAULT] )
  {
    std::cerr << "Can't load default image " << press_filename
	      << " SDL_Error: " << SDL_GetError()
	      << std::endl;
    success = false;
  }

  // Load the up surface
  g_key_press_surfaces[KEY_PRESS_SURFACE_UP] = 
    loadSurface( up_filename );
  
  if( !g_key_press_surfaces[KEY_PRESS_SURFACE_UP] )
  {
    std::cerr << "Can't load up image " << up_filename
	      << " SDL_Error: " << SDL_GetError()
	      << std::endl;
    success = false;
  }

  // Load the down surface
  g_key_press_surfaces[KEY_PRESS_SURFACE_DOWN] = 
    loadSurface( down_filename );

  if( !g_key_press_surfaces[KEY_PRESS_SURFACE_DOWN] )
  {
    std::cerr << "Can't load down image " << down_filename
	      << " SDL_Error: " << SDL_GetError()
	      << std::endl;
    success = false;
  }
  
  // Load the left surface
  g_key_press_surfaces[KEY_PRESS_SURFACE_LEFT] = 
    loadSurface( left_filename );

  if( !g_key_press_surfaces[KEY_PRESS_SURFACE_LEFT] )
  {
    std::cerr << "Can't load left image " << left_filename
	      << " SDL_Error: " << SDL_GetError()
	      << std::endl;
    success = false;
  }

  // Load the right surface
  g_key_press_surfaces[KEY_PRESS_SURFACE_RIGHT] = 
    loadSurface( right_filename );

  if( !g_key_press_surfaces[KEY_PRESS_SURFACE_RIGHT] )
  {
    std::cerr << "Can't load right image " << right_filename
	      << " SDL_Error: " << SDL_GetError()
	      << std::endl;
    success = false;
  }

  return success;
}

//! Close SDL_Window
void close()
{
  // Free the surfaces
  for( unsigned key_press_id = KEY_PRESS_SURFACE_DEFAULT;
       key_press_id < KEY_PRESS_SURFACE_TOTAL;
       ++key_press_id )
  {
    SDL_FreeSurface( g_key_press_surfaces[key_press_id] );
    
    g_key_press_surfaces[key_press_id] = NULL;
  }

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
    ("default_image",
     boost::program_options::value<std::string>(),
     "the default image (with path) that will be used with undefined key "
     "presses\n");
  
  // Create the positional (required args) 
  boost::program_options::positional_options_description pd;
  pd.add("default_image", 1);

  // Create the optional arguments
  boost::program_options::options_description generic( "Allowed options" );
  generic.add_options()
    ("help,h", "produce help message")
    ("up_image,u",
     boost::program_options::value<std::string>(),
     "Set the optional up image (with path)\n")
    ("down_image,d",
     boost::program_options::value<std::string>(),
     "Set the optional down image (with path)\n")
    ("left_image,l",
     boost::program_options::value<std::string>(),
     "Set the optional left image (with path)\n")
    ("right_image,r",
     boost::program_options::value<std::string>(),
     "Set the optional right image (with path)\n");

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
    exit( 1 );
  }

  // Store the default image name
  std::string default_image_name;
  
  if( vm.count( "default_image" ) )
    default_image_name = vm["default_image"].as<std::string>();
  else
  {
    std::cerr << "The default image (with path) must be specified." 
	      << std::endl;
    exit( 1 );
  }
  
  // Store the up image name
  std::string up_image_name;
  
  if( vm.count( "up_image" ) )
    up_image_name = vm["up_image"].as<std::string>();
  else
  {
    std::cout << "Note: The default image will be used for the up key."
	      << std::endl;
    up_image_name = default_image_name;
  }

  // Store the down image name
  std::string down_image_name;

  if( vm.count( "down_image" ) )
    down_image_name = vm["down_image"].as<std::string>();
  else
  {
    std::cout << "Note: The default image will be used for the down key."
	      << std::endl;
    down_image_name = default_image_name;
  }

  // Store the left image name
  std::string left_image_name;

  if( vm.count( "left_image" ) )
    left_image_name = vm["left_image"].as<std::string>();
  else
  {
    std::cout << "Note: The default image will be used for the left key."
	      << std::endl;
    left_image_name = default_image_name;
  }

  // Store the right image name
  std::string right_image_name;

  if( vm.count( "right_image" ) )
    right_image_name = vm["right_image"].as<std::string>();
  else
  {
    std::cout << "Note: The default image will be used for the right key."
	      << std::endl;
    right_image_name = default_image_name;
  }
  
  // Initialize the window
  if( !initialize() )
    exit( 1 );
  else
  {
    // Load the bitmap
    bool image_load_success = loadMedia( default_image_name,
					 up_image_name,
					 down_image_name,
					 left_image_name,
					 right_image_name );

    if( !image_load_success )
      exit( 1 );
    else
    {
      // The main loop flag
      bool quit = false;
      
      // SDL event handler
      SDL_Event event;

      // Set the current surface as the default surface
      g_current_surface = g_key_press_surfaces[KEY_PRESS_SURFACE_DEFAULT];

      // "Game" loop
      while( !quit )
      {
	// Handle events on the queue
	while( SDL_PollEvent( &event ) != 0 )
	{
	  // User requests quit
	  if( event.type == SDL_QUIT )
	    quit = true;

	  // User presses a key
	  else if( event.type == SDL_KEYDOWN )
	  {
	    // Select surfaces based on key press
	    switch( event.key.keysym.sym )
	    {
	      case SDLK_UP:
		g_current_surface = 
		  g_key_press_surfaces[KEY_PRESS_SURFACE_UP];
		break;
		
	      case SDLK_DOWN:
		g_current_surface = 
		  g_key_press_surfaces[KEY_PRESS_SURFACE_DOWN];
		break;
		
	      case SDLK_LEFT:
		g_current_surface = 
		  g_key_press_surfaces[KEY_PRESS_SURFACE_LEFT];
		break;
		
	     case SDLK_RIGHT:
	       g_current_surface = 
		 g_key_press_surfaces[KEY_PRESS_SURFACE_RIGHT];
	       break;
	       
	      default:
		g_current_surface = 
		  g_key_press_surfaces[KEY_PRESS_SURFACE_DEFAULT];
		break;
	    }
	  }
	}

	// Print image
	SDL_BlitSurface( g_current_surface, NULL, g_screen_surface, NULL);
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
