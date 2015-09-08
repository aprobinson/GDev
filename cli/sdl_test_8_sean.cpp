//---------------------------------------------------------------------------//
//!
//! \file   sdl_test_8_sean.cpp
//! \author Sean Robinson
//! \brief  Geometry rendering
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
#include <SDL2/SDL_image.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// The window we'll be rendering to
SDL_Window* g_window = NULL;
    
// The surface contained by the window
SDL_Surface* g_screen_surface = NULL;

// The image we will load and show on the screen
SDL_Surface* g_stretched_surface = NULL;

// The screen dimensions
const int screen_width_height[2] = {640,480};

// Window Renderer
SDL_Renderer* g_renderer = NULL;

// Current displayed texture
SDL_Texture* g_texture = NULL;


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
      // Create window renderer
      g_renderer = SDL_CreateRenderer( g_window, -1, SDL_RENDERER_ACCELERATED );
      if( g_renderer == NULL )
      {
        std::cerr << "Renderer could not be created: "
	       <<SDL_GetError()
		 <<std::endl;
	success = false;
      }
      else
      {
	// Initialize renderer color
	SDL_SetRenderDrawColor( g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	// Initialize PNG image
	int image_flags = IMG_INIT_PNG;
	if( !( IMG_Init( image_flags ) & image_flags ) )
	{
	  std::cerr << "SDL image could not initialize: "
		    << IMG_GetError()
		    <<std::endl;
	  success = false;
	}
      }
    }
  }
  return success;
}

//! Load the image file and allocate the surface
SDL_Texture* loadTexture( const std::string& filename )
{
  // The final texture
  SDL_Texture* new_texture = NULL;

  // Load the image
  SDL_Surface* loaded_surface = IMG_Load( filename.c_str() );

  if( loaded_surface == NULL )
  {
    std::cerr << "Unable to load image " << filename << "! SDL Error: "
	      << IMG_GetError() << std::endl;
  }
  else
  {
    // Create texture from surface
    new_texture = SDL_CreateTextureFromSurface( g_renderer, loaded_surface );

    if( new_texture == NULL )
    {
      std::cerr << "Unable to create texture from: " << filename << "! SDL Error: "
		<< IMG_GetError()
		<< std::endl;
    }

    // Free the old loaded surface
    SDL_FreeSurface( loaded_surface );
  }

  return new_texture;
}

//! Load texture
bool loadMedia( const std::string& filename )
{
  bool success = true;
  //no textures or images to load
  return success;
}

//! Close SDL_Window
void close()
{
  // Free surface
  SDL_DestroyTexture( g_texture );
  g_texture = NULL;

  // Destroy window
  SDL_DestroyRenderer( g_renderer );
  SDL_DestroyWindow( g_window );
  g_window = NULL;
  g_renderer = NULL;

  IMG_Quit();
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
  
  // Initialize the window
  if( !initialize() )
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
	  {
	    quit = true;
	  }
	}
	// Clear the screen
	SDL_SetRenderDrawColor( g_renderer,
				0xFF,
				0xFF,
				0xFF,
				0xFF );
	SDL_RenderClear( g_renderer );

	// Render the red filled quadrant
	SDL_Rect fill_rect = { SCREEN_WIDTH / 4,
			       SCREEN_HEIGHT / 4,
			       SCREEN_WIDTH / 2,
			       SCREEN_HEIGHT / 2 };
	SDL_SetRenderDrawColor( g_renderer,
				0xFF,
				0x00,
				0x00,
				0xFF );
	SDL_RenderFillRect( g_renderer, &fill_rect );

	// Render green outlined quadrant
	SDL_Rect outline_rect = { SCREEN_WIDTH / 6,
				  SCREEN_HEIGHT / 6,
				  SCREEN_WIDTH * 2 / 3,
				  SCREEN_HEIGHT * 2 / 3 };
	SDL_SetRenderDrawColor( g_renderer,
				0x00,
				0xFF,
				0x00,
				0xFF );
	SDL_RenderDrawRect( g_renderer, &outline_rect );

	// Draws a blue horizontal line
	SDL_SetRenderDrawColor( g_renderer,
				0x00,
				0x00,
				0xFF,
				0xFF );
	SDL_RenderDrawLine( g_renderer,
			    0,
			    SCREEN_HEIGHT / 2,
			    SCREEN_WIDTH,
			    SCREEN_HEIGHT / 2 );

	// Draw a vertical line of yellow dots
	SDL_SetRenderDrawColor( g_renderer,
			        0xFF,
			        0xFF,
			        0x00,
			        0xFF );
	for( int i = 0; i < SCREEN_HEIGHT; i += 4 )
	  {
	    SDL_RenderDrawPoint( g_renderer, SCREEN_WIDTH / 2, i );
	  }

	// Update the screen
	SDL_RenderPresent( g_renderer );
      }
    }
  
  // Close program
  close();

  return 0;
}

  

//---------------------------------------------------------------------------//
// end sdl_test_8_sean.cpp
//---------------------------------------------------------------------------//
