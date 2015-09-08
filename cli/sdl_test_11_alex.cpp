//---------------------------------------------------------------------------//
//!
//! \file   sdl_test_11.cpp
//! \author Alex Robinson
//! \brief  Clip rendering and sprite sheets using sdk
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

//! Texture wrapper class
class GDevTexture
{
  
public:
  
  //! Default Constructor
  GDevTexture();

  //! Constructor
  GDevTexture( const std::string& filename );

  //! Destructor
  ~GDevTexture();

  //! Loads the image at the specified path
  bool loadFromFile( const std::string& filename );

  //! Deallocates the texture
  void free();

  //! Renders the texture at the given point
  void render( const int x, const int y, const SDL_Rect* clip = NULL );

  //! Gets the image width
  int getWidth() const;

  //! Gets the image height
  int getHeight() const;

private:

  // The SDL texture
  SDL_Texture* d_texture;

  // The image width
  int d_width;

  // The image height
  int d_height;
};

// The window we'll be rendering to
SDL_Window* g_window = NULL;
    
// The window renderer
SDL_Renderer* g_renderer = NULL;

// The scene sprites
SDL_Rect g_sprite_clips[4];
GDevTexture g_sprite_sheet_texture;

// The screen dimensions
const int screen_width_height[2] = {640,480};

// Default constructor
GDevTexture::GDevTexture()
  : d_texture( NULL ),
    d_width( 0 ),
    d_height( 0 )
{ /* ... */ }

// Constructor
GDevTexture::GDevTexture( const std::string& filename )
  : d_texture( NULL ),
    d_width( 0 ),
    d_height( 0 )
{
  this->loadFromFile( filename );
}

// Destructor
GDevTexture::~GDevTexture()
{
  this->free();
}

// Loads the image at the specified path
bool GDevTexture::loadFromFile( const std::string& filename )
{
  // Deallocate a preexisting texture
  this->free();

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
    // Color key image
    SDL_SetColorKey( loaded_surface, 
		     SDL_TRUE, 
		     SDL_MapRGB( loaded_surface->format, 0, 0xFF, 0xFF ) );
							   
    // Create the texture from surface pixels
    new_texture = SDL_CreateTextureFromSurface( g_renderer, loaded_surface );
    
    if( new_texture == NULL )
    {
      std::cerr << "Unable to create texture from " << filename 
		<< "! SDL Error: " << SDL_GetError()
		<< std::endl;
    }
    else
    {
      d_width = loaded_surface->w;
      d_height = loaded_surface->h;
    }
      
    // Free the old loaded surface
    SDL_FreeSurface( loaded_surface );
  }

  d_texture = new_texture;
  
  return d_texture != NULL;
}

// Deallocates the texture
void GDevTexture::free()
{
  // Free an existing texture
  if( d_texture != NULL )
  {
    SDL_DestroyTexture( d_texture );
    d_texture = NULL;
    d_width = 0;
    d_height = 0;
  }
}

// Renders the texture at the given point
void GDevTexture::render( const int x, const int y, const SDL_Rect* clip )
{
  // Set the rendering space and render to screen
  SDL_Rect render_quad = { x, y, d_width, d_height };

  // Set clip rendering dimensions
  if( clip != NULL )
  {
    render_quad.w = clip->w;
    render_quad.h = clip->h;
  }
 
  SDL_RenderCopy( g_renderer, d_texture, clip, &render_quad );
}

// Gets the image width
int GDevTexture::getWidth() const
{
  return d_width;
}

// Gets the image height
int GDevTexture::getHeight() const
{
  return d_height;
}

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

//! Load image file
bool loadMedia( const std::string& sprite_sheet_name )
{
  bool success = true;
  
  // Load the sprite image
  if( !g_sprite_sheet_texture.loadFromFile( sprite_sheet_name ) )
  {
    std::cerr << "Can't load sprite sheet " << sprite_sheet_name
	      << "! SDL_Error: " << SDL_GetError()
	      << std::endl;
    success = false;
  }   
  else
  {
    // Set the top left sprite
    g_sprite_clips[0].x = 0;
    g_sprite_clips[0].y = 0;
    g_sprite_clips[0].w = 100;
    g_sprite_clips[0].h = 100;
    
    // Set the top right sprite
    g_sprite_clips[1].x = 100;
    g_sprite_clips[1].y = 0;
    g_sprite_clips[1].w = 100;
    g_sprite_clips[1].h = 100;
    
    // Set the bottom left sprite
    g_sprite_clips[2].x = 0;
    g_sprite_clips[2].y = 100;
    g_sprite_clips[2].w = 100;
    g_sprite_clips[2].h = 100;
    
    // Set the bottom right sprite
    g_sprite_clips[3].x = 100;
    g_sprite_clips[3].y = 100;
    g_sprite_clips[3].w = 100;
    g_sprite_clips[3].h = 100;  
  }

  return success;
}

//! Close SDL_Window
void close()
{
  // Free the sprite sheet
  g_sprite_sheet_texture.free();
  
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
    ("sprite_sheet",
     boost::program_options::value<std::string>(),
     "the sprite sheet (with path) that will be used\n");
    
  // Create the positional (required) args
  boost::program_options::positional_options_description pd;
  pd.add("sprite_sheet", 1 );
  
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
    std::cerr << cmdline_options << std::endl;
    
    return 1;
  }

  // Store the image name
  std::string sprite_sheet_name;

  if( vm.count( "sprite_sheet" ) )
    sprite_sheet_name = vm["sprite_sheet"].as<std::string>();
  else
  {
    std::cerr << "The sprite sheet (with path) must be specified."
	      << std::endl;

    return 1;
  }
  
  // Initialize the window
  if( !initialize() )
    return 1;
  else
  {
    // Load the bitmap
    if( !loadMedia( sprite_sheet_name ) )
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

	// Render the top left sprite
	g_sprite_sheet_texture.render( 0, 0, &g_sprite_clips[0] );

	// Render the top right sprite
	g_sprite_sheet_texture.render( screen_width_height[0] -
				       g_sprite_clips[1].w,
				       0,
				       &g_sprite_clips[1] );

	// Render the bottom left sprite
	g_sprite_sheet_texture.render( 0,
				       screen_width_height[1] - 
				       g_sprite_clips[2].h,
				       &g_sprite_clips[2] );

	// Render the bottom right sprite
	g_sprite_sheet_texture.render( screen_width_height[0] - 
				       g_sprite_clips[3].w,
				       screen_width_height[1] -
				       g_sprite_clips[3].h,
				       &g_sprite_clips[3] );	
	
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
// end sdl_test_11.cpp
//---------------------------------------------------------------------------//
