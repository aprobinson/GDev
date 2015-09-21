//---------------------------------------------------------------------------//
//!
//! \file   sdl_test_17.cpp
//! \author Alex Robinson
//! \brief  Mouse events and buttons using sdl
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
#include <SDL2/SDL_ttf.h>

//! Button sprite enum
enum GDevButtonSprite
{
  BUTTON_SPRITE_MOUSE_OUT = 0,
  BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
  BUTTON_SPRITE_MOUSE_DOWN = 2,
  BUTTON_SPRITE_MOUSE_UP = 3,
  BUTTON_SPRITE_TOTAL = 4
};

//! The mouse button
class GDevButton
{
public:

  //! Constructor
  GDevButton();

  //! Set the top left position of the button
  void setPosition( const int x, const int y );

  //! Handle mouse event
  void handleEvent( const SDL_Event* event );

  //! Render the button
  void render();

private:

  // Top left position
  SDL_Point d_position;

  // The button sprite
  GDevButtonSprite d_current_sprite;
};

//! Texture wrapper class
class GDevTexture
{
  
public:
  
  //! Default Constructor
  GDevTexture();

  //! Destructor
  ~GDevTexture();

  //! Loads the image at the specified path
  bool loadFromFile( const std::string& filename,
		     const unsigned char color_key_red = 0xFF,
		     const unsigned char color_key_green = 0xFF,
		     const unsigned char color_key_blue = 0xFF );

  //! Loads image at specified path
  bool loadFromRenderedText( const std::string texture_text,
			     const SDL_Color text_color );

  //! Deallocates the texture
  void free();

  //! Set the color modulation
  void setColor( const unsigned char red, 
		 const unsigned char green,
		 const unsigned char blue );

  //! Set the blending
  void setBlendMode( SDL_BlendMode blending );

  //! Set the alpha modulation
  void setAlpha( const unsigned char alpha );

  //! Renders the texture at the given point
  void render( const int x, 
	       const int y, 
	       const SDL_Rect* clip = NULL,
	       const double angle = 0.0,
	       const SDL_Point* center = NULL,
	       const SDL_RendererFlip flip = SDL_FLIP_NONE );

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

// The rendered texture
SDL_Rect g_sprite_clips[BUTTON_SPRITE_TOTAL];
GDevTexture g_button_sprite_sheet_texture;

// The screen dimensions
const int screen_width_height[2] = {640,480};

// Button constants
const int button_width_height[2] = {300,200};
const int g_total_buttons = 4;

// The buttons objects
GDevButton g_buttons[g_total_buttons];

// Default constructor
GDevButton::GDevButton()
{
  d_position.x = 0;
  d_position.y = 0;

  d_current_sprite = BUTTON_SPRITE_MOUSE_OUT;
}

// Set the button position
void GDevButton::setPosition( const int x, const int y )
{
  d_position.x = x;
  d_position.y = y;
}

// Handle the event (action listener)
void GDevButton::handleEvent( const SDL_Event* event )
{
  // Check if it is a mouse event
  if( event->type == SDL_MOUSEMOTION ||
      event->type == SDL_MOUSEBUTTONDOWN ||
      event->type == SDL_MOUSEBUTTONUP )
  {
    // Get the mouse position
    int x, y;

    SDL_GetMouseState( &x, &y );

    // Check if the mouse is in the button
    bool inside = true;

    // Mouse is to the left of the button
    if( x < d_position.x )
      inside = false;
    
    // Mouse is right of the button
    else if( x > d_position.x + button_width_height[0] )
      inside = false;

    // Mouse is above the button
    else if( y < d_position.y )
      inside = false;

    // Mouse is below the button
    else if( y > d_position.y + button_width_height[1] )
      inside = false;

    // Mouse is outside the button
    if( !inside )
      d_current_sprite = BUTTON_SPRITE_MOUSE_OUT;
    else
    {
      // Set mouse over sprite
      switch( event->type )
      {
        case SDL_MOUSEMOTION:
	  d_current_sprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
	  break;

        case SDL_MOUSEBUTTONDOWN:
	  d_current_sprite = BUTTON_SPRITE_MOUSE_DOWN;
	  break;

        case SDL_MOUSEBUTTONUP:
	  d_current_sprite = BUTTON_SPRITE_MOUSE_UP;
	  break;
      }
    }
  }
}

// Render the button
void GDevButton::render()
{
  // Show the current button sprite
  g_button_sprite_sheet_texture.render( d_position.x,
					d_position.y,
					&g_sprite_clips[d_current_sprite] );
}

// Default constructor
GDevTexture::GDevTexture()
  : d_texture( NULL ),
    d_width( 0 ),
    d_height( 0 )
{ /* ... */ }

// Destructor
GDevTexture::~GDevTexture()
{
  this->free();
}

// Loads the image at the specified path
bool GDevTexture::loadFromFile( const std::string& filename,
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
      d_width = loaded_surface->w;
      d_height = loaded_surface->h;
    }
      
    // Free the old loaded surface
    SDL_FreeSurface( loaded_surface );
  }

  d_texture = new_texture;
  
  return d_texture != NULL;
}

// Render an image from text
bool GDevTexture::loadFromRenderedText( const std::string texture_text,
					const SDL_Color text_color )
{
  // Get rid of preexisting texture
  this->free();

  // Render text surface
  // SDL_Surface* text_surface = TTF_RenderText_Solid( g_font,
  // 						    texture_text.c_str(),
  // 						    text_color );
  SDL_Surface* text_surface = NULL;

  if( text_surface == NULL )
  {
    std::cerr << "Unable to render text surface! SDL_ttf Error: "
	      << TTF_GetError() << std::endl;
  }
  else
  {
    // Create texture from surface pixels
    d_texture = SDL_CreateTextureFromSurface( g_renderer, text_surface );

    if( d_texture == NULL )
    {
      std::cerr << "Unable to create texture from rendered text! SDL Error: "
		<< SDL_GetError() << std::endl;
    }
    else
    {
      // Get the image dimensions
      d_width = text_surface->w;
      d_height = text_surface->h;
    }
  }

  // Return success
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

// Set the color modulation
void GDevTexture::setColor( const unsigned char red, 
			    const unsigned char green,
			    const unsigned char blue )
{
  SDL_SetTextureColorMod( d_texture, red, green, blue );
}

// Set the blending
void GDevTexture::setBlendMode( SDL_BlendMode blending )
{
  SDL_SetTextureBlendMode( d_texture, blending );
}

// Set the alpha modulation
void GDevTexture::setAlpha( const unsigned char alpha )
{
  SDL_SetTextureAlphaMod( d_texture, alpha );
}

// Renders the texture at the given point
void GDevTexture::render( const int x, 
			  const int y, 
			  const SDL_Rect* clip,
			  const double angle,
			  const SDL_Point* center,
			  const SDL_RendererFlip flip )
{
  // Set the rendering space and render to screen
  SDL_Rect render_quad = { x, y, d_width, d_height };

  // Set clip rendering dimensions
  if( clip != NULL )
  {
    render_quad.w = clip->w;
    render_quad.h = clip->h;
  }
 
  SDL_RenderCopyEx( g_renderer, 
		    d_texture, 
		    clip, 
		    &render_quad, 
		    angle, 
		    center, 
		    flip  );
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

	if( TTF_Init() == -1 )
	{
	  std::cerr << "SDL_ttf could not initialize! SDL_ttf Error: "
		    << TTF_GetError() << std::endl;
	  success = false;
	}
      }
    }
  }
  
  return success;
}

//! Load the message and the font
bool loadMedia( const std::string& button_sprite_sheet )
{
  bool success = true;
  
  // Load the sprites
  if( !g_button_sprite_sheet_texture.loadFromFile( button_sprite_sheet.c_str() ) )
  {
    std::cout << "Failed to load button sprite texture "
	      << button_sprite_sheet << "! " << std::endl;
    success = false;
  }
  else
  {
    // Set the sprites
    for( int i = 0; i < BUTTON_SPRITE_TOTAL; ++i )
    {
      g_sprite_clips[i].x = 0;
      g_sprite_clips[i].y = i*200;
      g_sprite_clips[i].w = button_width_height[0];
      g_sprite_clips[i].h = button_width_height[1];
    }

    // Set the buttons in corners
    g_buttons[0].setPosition( 0, 0 );
    g_buttons[1].setPosition( screen_width_height[0] - button_width_height[0],
			      0 );
    g_buttons[2].setPosition( 0, 
			      screen_width_height[1] - button_width_height[1]);
    g_buttons[3].setPosition( screen_width_height[0] - button_width_height[0],
			      screen_width_height[1] - button_width_height[1]);
						  
  }

  return success;
}

//! Close SDL_Window
void close()
{
  // Free the texture
  g_button_sprite_sheet_texture.free();

  // Destroy the renderer
  SDL_DestroyRenderer( g_renderer );
  g_renderer = NULL;

  // Destroy window
  SDL_DestroyWindow( g_window );
  g_window = NULL;

  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
}

int main( int argc, char** argv )
{
  // Create the hidden program options (required args)
  boost::program_options::options_description hidden( "Hidden options" );
  hidden.add_options()
    ("button_sprite_sheet",
     boost::program_options::value<std::string>(),
     "the image (with path) that will be used\n");
        
  // Create the positional (required) args
  boost::program_options::positional_options_description pd;
  pd.add("button_sprite_sheet", 1 );
    
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
    
    return 0;
  }

  // Store the image name
  std::string sprite_sheet_filename;

  if( vm.count( "button_sprite_sheet" ) )
    sprite_sheet_filename = vm["button_sprite_sheet"].as<std::string>();
  else
  {
    std::cerr << "The button sprite sheet (with path) must be specified"
	      << std::endl;

    return 1;
  }

  // Initialize the window
  if( !initialize() )
    return 1;
  else
  {
    // Load the bitmap
    if( !loadMedia( sprite_sheet_filename ) )
      return 1;
    else
    {
      bool quit = false;

      // The event
      SDL_Event event;
      
      // Main application loop
      while( !quit )
      {
	while( SDL_PollEvent( &event ) != 0 )
	{
	  if( event.type == SDL_QUIT )
	    quit = true;

	  // Handle button events
	  for( int i = 0; i < g_total_buttons; ++i )
	    g_buttons[i].handleEvent( &event );
	}

	// Clear the screen
	SDL_SetRenderDrawColor( g_renderer, 0xFF, 0xFF, 0xFF, 0xFF );
	
	SDL_RenderClear( g_renderer );

	// Render the buttons
	for( int i = 0; i < g_total_buttons; ++i )
	  g_buttons[i].render();
	
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
// end sdl_test_16.cpp
//---------------------------------------------------------------------------//
