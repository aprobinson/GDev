//---------------------------------------------------------------------------//
//!
//! \file   sdl_test_9.cpp
//! \author Alex Robinson
//! \brief  Render texture in multiple viewports with sdk
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

// The window we'll be rendering to
SDL_Window* g_window = NULL;
    
// The window renderer
SDL_Renderer* g_renderer = NULL;

// The current displayed texture
SDL_Texture* g_texture = NULL;

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
    // Set texture filtering to linear
    if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
    {
      std::cerr << "Warning: Linear texture filtering not enabled!" 
		<< std::endl;
    }
    
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
      // Create the renderer for the window
      g_renderer = SDL_CreateRenderer( g_window, -1, SDL_RENDERER_ACCELERATED);
      
      if( g_renderer == NULL )
      {
	std::cerr << "Renderer could not be created! SDL_Error: "
		  << SDL_GetError()
		  << std::endl;
	success = false;
      }
      else
      {
	// Initialize renderer color
	SDL_SetRenderDrawColor( g_renderer, 0xFF, 0xFF, 0xFF, 0xFF );

	// Initialize PNG loading
	int img_flags = IMG_INIT_PNG;

	if( !( IMG_Init( img_flags ) & img_flags ) )
	{
	  std::cerr << "SDL_image extension could not initialize! "
		    << "SDL_image Error: " << IMG_GetError()
		    << std::endl;
	  success = false;
	}
      }
    }
  }
  
  return success;
}

//! Load the image file and allocate the texture
SDL_Texture* loadTexture( const std::string& filename )
{
  // The final texture
  SDL_Texture* new_texture = NULL;

  // Load the image
  SDL_Surface* loaded_surface = IMG_Load( filename.c_str() );

  if( loaded_surface == NULL )
  {
    std::cerr << "Unable to load image " << filename << "! SDL_image Error: "
	      << IMG_GetError() << std::endl;
  }
  else
  {
    // Create the texture from surface pixels
    new_texture = SDL_CreateTextureFromSurface( g_renderer, loaded_surface );
    
    if( new_texture == NULL )
    {
      std::cerr << "Unable to create texture from " << filename 
		<< "! SDL Error: " << SDL_GetError()
		<< std::endl;
    }

    // Free the old loaded surface
    SDL_FreeSurface( loaded_surface );
  }

  return new_texture;
}

//! Load image file
bool loadMedia( const std::string& filename )
{
  bool success = true;
  
  // Load desired bitmap
  g_texture = loadTexture( filename );
  
  if( g_texture == NULL )
  {
    std::cerr << "Can't load image " << filename
	      << "! SDL_Error: " << SDL_GetError()
	      << std::endl;
    success = false;
  }   
    
  return success;
}

//! Close SDL_Window
void close()
{
  // Free the texture
  SDL_DestroyTexture( g_texture );
  g_texture = NULL;

  // Destroy the renderer
  SDL_DestroyRenderer( g_renderer );
  g_renderer = NULL;

  // Destroy window
  SDL_DestroyWindow( g_window );
  g_window = NULL;

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

  // Store the image name
  std::string image_name;

  if( vm.count( "image" ) )
    image_name = vm["image"].as<std::string>();
  
  // Initialize the window
  if( !initialize() )
    return 1;
  else
  {
    // Load the bitmap
    if( !loadMedia( image_name ))
      return 1;
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

	// Clear the screen
	SDL_SetRenderDrawColor( g_renderer, 0xFF, 0xFF, 0xFF, 0xFF );
	
	SDL_RenderClear( g_renderer );

	// Set the viewport to the top left corner
	SDL_Rect top_left_viewport;
	top_left_viewport.x = 0;
	top_left_viewport.y = 0;
	top_left_viewport.w = screen_width_height[0]/2;
	top_left_viewport.h = screen_width_height[1]/2;

	SDL_RenderSetViewport( g_renderer, &top_left_viewport );
	
	// Render texture to the screen
	SDL_RenderCopy( g_renderer, g_texture, NULL, NULL );
	
	// Set the viewport to the top right corner
	SDL_Rect top_right_viewport;
	top_right_viewport.x = screen_width_height[0]/2;
	top_right_viewport.y = 0;
	top_right_viewport.w = screen_width_height[0]/2;
	top_right_viewport.h = screen_width_height[1]/2;
	
	SDL_RenderSetViewport( g_renderer, &top_right_viewport );

	// Render texture to screen
	SDL_RenderCopy( g_renderer, g_texture, NULL, NULL );
	
	// Set the viewport to the bottom
	SDL_Rect bottom_viewport;
	bottom_viewport.x = 0;
	bottom_viewport.y = screen_width_height[0]/2;
	bottom_viewport.w = screen_width_height[0];
	bottom_viewport.h = screen_width_height[1]/2;

	SDL_RenderSetViewport( g_renderer, &bottom_viewport );

	// Render texture to screen
	SDL_RenderCopy( g_renderer, g_texture, NULL, NULL );

	// Update the screen
	SDL_RenderPresent( g_renderer );
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
