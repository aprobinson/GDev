//---------------------------------------------------------------------------//
//!
//! \file   sdl_test_12_sean.cpp
//! \author Sean Robinson
//! \brief  Color modulation
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
class SDLTexture
{
  
public:
  
  //! Default Constructor
  SDLTexture();

  //! Destructor
  ~SDLTexture();

  //! Loads the image at the specified path
  bool loadFromFile( const std::string& filename,
		     const unsigned char color_key_red = 0xFF,
		     const unsigned char color_key_green = 0xFF,
		     const unsigned char color_key_blue = 0xFF );

  //! Deallocates the texture
  void free();

  //! Set the color modulation
  void setColor( const unsigned char red, 
		 const unsigned char green,
		 const unsigned char blue );

  //! Renders the texture at the given point
  void render( const int x, const int y, const SDL_Rect* clip = NULL );

  //! Gets the image width
  int getWidth() const;

  //! Gets the image height
  int getHeight() const;

private:

  // The SDL texture
  SDL_Texture* s_texture;

  // The image width
  int s_width;

  // The image height
  int s_height;
};

// The window we'll be rendering to
SDL_Window* g_window = NULL;
    
// The window renderer
SDL_Renderer* g_renderer = NULL;

// The modulated texture
SDLTexture g_modulated_texture;

// The screen dimensions
const int screen_width_height[2] = {640,480};

SDLTexture::SDLTexture()
{
	//Initialize
	s_texture = NULL;
	s_width = 0;
	s_height = 0;
}

// Destructor
SDLTexture::~SDLTexture()
{
  this->free();
}

// Loads the image at the specified path
bool SDLTexture::loadFromFile( const std::string& filename,
				const unsigned char color_key_red,
				const unsigned char color_key_green,
				const unsigned char color_key_blue )
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
		     SDL_MapRGB( loaded_surface->format, 
				 color_key_red,
				 color_key_green,
				 color_key_blue ) );
							   
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
      s_width = loaded_surface->w;
      s_height = loaded_surface->h;
    }
      
    // Free the old loaded surface
    SDL_FreeSurface( loaded_surface );
  }

  s_texture = new_texture;
  
  return s_texture != NULL;
}

// Deallocates the texture
void SDLTexture::free()
{
  // Free an existing texture
  if( s_texture != NULL )
  {
    SDL_DestroyTexture( s_texture );
    s_texture = NULL;
    s_width = 0;
    s_height = 0;
  }
}

// Set the color modulation
void SDLTexture::setColor( const unsigned char red, 
			    const unsigned char green,
			    const unsigned char blue )
{
  SDL_SetTextureColorMod( s_texture, red, green, blue );
}

// Renders the texture at the given point
void SDLTexture::render( const int x, const int y, const SDL_Rect* clip )
{
  // Set the rendering space and render to screen
  SDL_Rect render_quad = { x, y, s_width, s_height };

  // Set clip rendering dimensions
  if( clip != NULL )
  {
    render_quad.w = clip->w;
    render_quad.h = clip->h;
  }
 
  SDL_RenderCopy( g_renderer, s_texture, clip, &render_quad );
}

// Gets the image width
int SDLTexture::getWidth() const
{
  return s_width;
}

// Gets the image height
int SDLTexture::getHeight() const
{
  return s_height;
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
bool loadMedia( const std::string& filename,
		const unsigned char color_key_red,
		const unsigned char color_key_green,
		const unsigned char color_key_blue )
{
  bool success = true;
  
  // Load the image file
  bool file_loaded = 
    g_modulated_texture.loadFromFile( filename, 
				      color_key_red,
				      color_key_green,
				      color_key_blue );
  if( !file_loaded )
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
  // Free the sprite sheet
  g_modulated_texture.free();
  
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
    ("help,h", "produce help message")
    ("color_key_red,r",
     boost::program_options::value<unsigned>(),
     "the color key red value (0-255)\n")
    ("color_key_green,g",
     boost::program_options::value<unsigned>(),
     "the color key green value (0-255)\n")
    ("color_key_blue,b",
     boost::program_options::value<unsigned>(),
     "the color key blue value (0-255)\n");

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
  std::string image_name;

  if( vm.count( "image" ) )
    image_name = vm["image"].as<std::string>();
  else
  {
    std::cerr << "The image (with path) must be specified."
	      << std::endl;

    return 1;
  }

  // Store the color key rgb values
  unsigned char color_key_r = 255, color_key_g = 255, color_key_b = 255;

  if( vm.count( "color_key_red" ) )
    color_key_r = vm["color_key_red"].as<unsigned>();

  if( vm.count( "color_key_green" ) )
    color_key_g = vm["color_key_green"].as<unsigned>();

  if( vm.count( "color_key_blue" ) )
    color_key_b = vm["color_key_blue"].as<unsigned>();
  
  // Initialize the window
  if( !initialize() )
    return 1;
  else
  {
    // Load the bitmap
    if( !loadMedia( image_name, color_key_r, color_key_g, color_key_b ) )
      return 1;
    else
    {
      bool quit = false;

      // The event
      SDL_Event event;

      // The modulation components
      unsigned char r = 255, g = 255, b = 255;
      
      // Main application loop
      while( !quit )
      {
	while( SDL_PollEvent( &event ) != 0 )
	{
	  if( event.type == SDL_QUIT )
	    quit = true;

	  // On keypress, change rgb values
	  else if( event.type == SDL_KEYDOWN )
	  {
	    switch( event.key.keysym.sym )
	    {
	      // Increase red
	      case SDLK_q:
		r += 32;
		break;

	      // Increase green
	      case SDLK_w:
		g += 32;
		break;

	      // Increase blue
	      case SDLK_e:
		b += 32;
		break;
		
	      // Decrease red
	      case SDLK_a:
		r -= 32;
		break;

	      // Decrease green
	      case SDLK_s:
		g -= 32;
		break;

	      // Decrease blue
	      case SDLK_d:
		b -= 32;
		break;
	    }
	  }
	}

	// Clear the screen
	SDL_SetRenderDrawColor( g_renderer, 0xFF, 0xFF, 0xFF, 0xFF );
	
	SDL_RenderClear( g_renderer );

	// Modulate the render texture
	g_modulated_texture.setColor( r, g, b );
	g_modulated_texture.render( 0, 0 );
	
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
// end sdl_test_12_sean.cpp
//---------------------------------------------------------------------------//
