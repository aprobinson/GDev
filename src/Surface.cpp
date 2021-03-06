//---------------------------------------------------------------------------//
//!
//! \file   Surface.cpp
//! \author Alex Robinson
//! \brief  The surface wrapper class definition
//!
//---------------------------------------------------------------------------//

// SDL Includes
#include <SDL2/SDL_image.h>

// GDev Includes
#include "Surface.hpp"
#include "ExceptionTestMacros.hpp"
#include "DBCMacros.hpp"

namespace GDev{

// Blank constructor
Surface::Surface( const int width,
		  const int height,
		  const Uint32 pixel_format )
  : d_surface( NULL ),
    d_owns_surface( true )
{
  // Make sure the dimensions are valid
  testPrecondition( width > 0 );
  testPrecondition( height > 0 );

  this->initializeRGBSurface( width, height, pixel_format );
}

// Shape constructor
Surface::Surface( const Shape& area,
		  const SDL_Color& inside_color,
		  const SDL_Color& edge_color,
		  const SDL_Color& outside_color )
  : d_surface( NULL ),
    d_owns_surface( true )
{
  // Make sure the dimensions are valid
  testPrecondition( area.getBoundingBoxWidth() > 0 );
  testPrecondition( area.getBoundingBoxHeight() > 0 );

  this->initializeRGBSurface( area.getBoundingBoxWidth(), 
			      area.getBoundingBoxHeight(), 
			      SDL_PIXELFORMAT_ARGB8888 );

  // Create the pixel types
  Uint32 in_pixel = SDL_MapRGBA( &this->getPixelFormat(),
				 inside_color.r,
				 inside_color.g,
				 inside_color.b,
				 inside_color.a );

  Uint32 edge_pixel = SDL_MapRGBA( &this->getPixelFormat(),
				   edge_color.r,
				   edge_color.g,
				   edge_color.b,
				   edge_color.a );

  Uint32 out_pixel = SDL_MapRGBA( &this->getPixelFormat(),
				  outside_color.r,
				  outside_color.g,
				  outside_color.b,
				  outside_color.a );

  try{
    // Get the surface pixels
    this->lock();
    
    Uint32* pixels = (Uint32*)this->getPixels();
    
    for( int i = 0; i < this->getNumberOfPixels(); ++i )
    {
      int row = i/this->getWidth();
      int pixel_x_pos = i - row*this->getWidth() + 
	area.getBoundingBoxXPosition();
      int pixel_y_pos = row + area.getBoundingBoxYPosition();
      
      if( area.isPointOn( pixel_x_pos, pixel_y_pos ) )
      	pixels[i] = edge_pixel;
      else if( area.isPointIn( pixel_x_pos, pixel_y_pos ) )
	pixels[i] = in_pixel;
      else
	pixels[i] = out_pixel;
    }

    this->unlock();
  }
  EXCEPTION_CATCH_RETHROW( ExceptionType, 
			   "Error: Unable to create the shape surface!" );
}

// Image constructor
/*! \details .png, .jpg and .bmp are all supported file formats. The wrapper
 * will own the constructed SDL_Surface (memory management will be handled
 * internally).
 */
Surface::Surface( const std::string& image_name )
  : d_surface( NULL ),
    d_owns_surface( true )
{
  // Make sure the image name is valid
  testPrecondition( image_name.size() > 0 );
  
  d_surface = IMG_Load( image_name.c_str() );

  // Make sure the image was successfully loaded
  TEST_FOR_EXCEPTION( d_surface == NULL,
		      ExceptionType,
		      "Error: Unable to load image " << image_name <<
		      "! SDL_image Error: " << IMG_GetError() );
}

// Text constructor
/*! \details The wrapper will own the constructed SDL_Surface 
 * (memory management will be handled internally).
 */
Surface::Surface( const std::string& message,
		  const Font& font,
		  const SDL_Color& text_color,
		  const SDL_Color* background_color )
  : d_surface( NULL ),
    d_owns_surface( true )
{
  // Make sure the message is valid
  testPrecondition( message.size() > 0 );

  if( background_color != NULL )
  {
    d_surface = 
      TTF_RenderText_Shaded( const_cast<TTF_Font*>( font.getRawFontPtr() ),
			     message.c_str(), 
			     text_color,
			     *background_color );
  }
  else
  {
    d_surface = 
      TTF_RenderText_Solid( const_cast<TTF_Font*>( font.getRawFontPtr() ),
			    message.c_str(), 
			    text_color );
  }

  TEST_FOR_EXCEPTION( d_surface == NULL,
		      ExceptionType,
		      "Error: Unable to render surface with text " 
		      << message << "! SDL_ttf Error: " << TTF_GetError() );
    
}

// Surface conversion constructor
/*! \details The wrapper will own the constructed SDL_Surface 
 * (memory management will be handled internally).
 */
Surface::Surface( const Surface& other_surface,
		  const Uint32 pixel_format )
  : d_surface( NULL ),
    d_owns_surface( true )
{
  d_surface = SDL_ConvertSurfaceFormat( 
		  const_cast<SDL_Surface*>( other_surface.getRawSurfacePtr() ),
		  pixel_format,
		  0 );

  TEST_FOR_EXCEPTION( d_surface == NULL,
		      ExceptionType,
		      "Error: Unable to convert the existing surface to the "
		      "requested format! SDL_Error: " << SDL_GetError() );
}

// Existing surface constructor (will not take ownership)
Surface::Surface( SDL_Surface* existing_surface )
  : d_surface( existing_surface ),
    d_owns_surface( false )
{
  // Make sure the existing surface is valid
  testPrecondition( existing_surface != NULL );
}

// Destructor
Surface::~Surface()
{
  this->free();
}

// Check if the surface has local ownership
bool Surface::isLocallyOwned() const
{
  return d_owns_surface;
}

// Get the width of the surface
int Surface::getWidth() const
{
  return d_surface->w;
}

// Get the height of the surface
int Surface::getHeight() const
{
  return d_surface->h;
}

// Get the length of a row of pixels in bytes (pitch)
int Surface::getPitch() const
{
  return d_surface->pitch;
}

// Get the format of the pixels stored in the surface
const SDL_PixelFormat& Surface::getPixelFormat() const
{
  return *d_surface->format;
}

// Get the pixel format enum
Uint32 Surface::getPixelFormatValue() const
{
  return d_surface->format->format;
}

// Get the SDL_Rect structure used to clip blits to the surface
const SDL_Rect& Surface::getClipRectangle() const
{
  return d_surface->clip_rect;
}

// Set the SDL_Rect structure used to clip blits to the surface
void Surface::setClipRectangle( const SDL_Rect& clip_rectangle )
{
  bool return_value =  SDL_SetClipRect( d_surface, &clip_rectangle );

  TEST_FOR_EXCEPTION( return_value != true,
		      ExceptionType,
		      "Error: Unable to set the clip rectangle! "
		      "SDL_Error: " << SDL_GetError() );
}

// Get the color key (transparent pixel) for the surface
Uint32 Surface::getColorKey() const
{
  // Make sure the color key is enabled
  testPrecondition( this->isColorKeySet() );
  
  Uint32 key;
  
  int return_value = 
    SDL_GetColorKey( const_cast<SDL_Surface*>( d_surface ), &key );

  TEST_FOR_EXCEPTION( return_value != 0,
		      ExceptionType,
		      "Error: Unable to get the surface color key! "
		      "SDL_Error: " << SDL_GetError() );

  return key;
}

// Set the color key (transparent pixel) for the surface
/* \details Use the SDL_MapRGB function to create the color key.
 */
void Surface::setColorKey( const Uint32 color_key )
{
  int return_value = SDL_SetColorKey( d_surface, SDL_TRUE, color_key );

  TEST_FOR_EXCEPTION( return_value != 0,
		      ExceptionType,
		      "Error: Unable to set the surface color key! "
		      "SDL_Error: " << SDL_GetError() );
}

// Check if the color key is set
bool Surface::isColorKeySet() const
{
  Uint32 dummy;
  
  int return_value = 
    SDL_GetColorKey( const_cast<SDL_Surface*>( d_surface ), &dummy );

  TEST_FOR_EXCEPTION( return_value < -1,
		      ExceptionType,
		      "Error: Unable to check if the surface color key is "
		      "enabled! SDL_Error: " << SDL_GetError() );
  
  return return_value == 0;
}

// Unset the color key (transparent pixel)
void Surface::unsetColorKey()
{
  int return_value = SDL_SetColorKey( d_surface, SDL_FALSE, 0 );

  TEST_FOR_EXCEPTION( return_value != 0,
		      ExceptionType,
		      "Error: Unable to disable the surface color key! "
		      "SDL_Error: " << SDL_GetError() );
}

// Get the alpha modulation
Uint8 Surface::getAlphaMod() const
{
  Uint8 alpha;

  int return_value = 
    SDL_GetSurfaceAlphaMod( const_cast<SDL_Surface*>( d_surface ), &alpha );

  TEST_FOR_EXCEPTION( return_value != 0,
		      ExceptionType,
		      "Error: Unable to get the surface alpha modulation! "
		      "SDL_Error: " << SDL_GetError() );

  return alpha;
}

// Set the alpha modulation
void Surface::setAlphaMod( const Uint8 alpha )
{
  int return_value = SDL_SetSurfaceAlphaMod( d_surface, alpha );

  TEST_FOR_EXCEPTION( return_value != 0,
		      ExceptionType,
		      "Error: Unable to set the surface alpha modulation! "
		      "SDL_Error: " << SDL_GetError() );
}

// Get the blend mode
SDL_BlendMode Surface::getBlendMode() const
{
  SDL_BlendMode mode;

  int return_value = 
    SDL_GetSurfaceBlendMode( const_cast<SDL_Surface*>( d_surface ), &mode );

  TEST_FOR_EXCEPTION( return_value != 0,
		      ExceptionType,
		      "Error: Unable to get the surface blend mode! "
		      "SDL_Error: " << SDL_GetError() );

  return mode;
}

// Set the blend mode
void Surface::setBlendMode( const SDL_BlendMode blend_mode )
{
  int return_value = SDL_SetSurfaceBlendMode( d_surface, blend_mode );

  TEST_FOR_EXCEPTION( return_value != 0,
		      ExceptionType,
		      "Error: Unable to set the surface blend mode! "
		      "SDL_Error: " << SDL_GetError() );
}

// Get the color modulation
void Surface::getColorMod( Uint8& red, Uint8& green, Uint8& blue ) const
{
  int return_value = 
    SDL_GetSurfaceColorMod( const_cast<SDL_Surface*>( d_surface ),
			    &red,
			    &green,
			    &blue );

  TEST_FOR_EXCEPTION( return_value != 0,
		      ExceptionType,
		      "Error: Unable to get the surface color modulation! "
		      "SDL_Error: " << SDL_GetError() );
}

// Set the color modulation
void Surface::setColorMod( const Uint8 red, 
			   const Uint8 green, 
			   const Uint8 blue )
{
  int return_value = SDL_SetSurfaceColorMod( d_surface, red, green, blue );

  TEST_FOR_EXCEPTION( return_value != 0,
		      ExceptionType,
		      "Error: Unable to set the surface color modulation! "
		      "SDL_Error: " << SDL_GetError() );
}

// Get the raw surface pointer (potentially dangerous)
/*! \details Use this with the SDL C interface when necessary.
 */
const SDL_Surface* Surface::getRawSurfacePtr() const
{
  return d_surface;
}
  
// Get the raw surface pointer (potentially dangerous)
/*! \details Use this with the SDL C interface when necessary.
 */
SDL_Surface* Surface::getRawSurfacePtr()
{
  return d_surface;
}

// Check if the surface is locked
bool Surface::isLocked() const
{
  return d_surface->locked;
}

// Check if the surface must be locked to access pixels
bool Surface::mustLock() const
{
  return SDL_MUSTLOCK( const_cast<SDL_Surface*>( d_surface ) );
}

// Lock the surface
void Surface::lock()
{
  // Make sure the surface is unlocked
  testPrecondition( !this->isLocked() );
  
  int return_value = SDL_LockSurface( d_surface );

  TEST_FOR_EXCEPTION( return_value != 0,
		      ExceptionType,
		      "Error: Unable to lock the surface! "
		      "SDL_Error: " << SDL_GetError() );
}

// Unlock the surface
void Surface::unlock()
{
  // Make sure the surface is already locked
  testPrecondition( this->isLocked() );
  
  SDL_UnlockSurface( d_surface );
}

// Get the surface pixels
const void* Surface::getPixels() const
{
  return d_surface->pixels;
}

// Get the number of surface pixels
unsigned Surface::getNumberOfPixels() const
{
  return this->getPitch()*this->getHeight()/
    this->getPixelFormat().BytesPerPixel;
}

// Perform a scaled surface copy to the destination surface
void Surface::blitScaled( Surface& destination_surface,
			  SDL_Rect* destination_rectangle,
			  const SDL_Rect* source_rectangle ) const
			  
{
  int return_value = SDL_BlitScaled( const_cast<SDL_Surface*>( d_surface ),
				     source_rectangle,
				     destination_surface.d_surface,
				     destination_rectangle );

  TEST_FOR_EXCEPTION( return_value != 0,
		      ExceptionType,
		      "Error: Unable to perfom a scaled surface blit! "
		      "SDL_Error: " << SDL_GetError() );
}
  
// Perform a fast surface copy to the destination surface
void Surface::blitSurface( Surface& destination_surface,
			   SDL_Rect* destination_rectangle,
			   const SDL_Rect* source_rectangle ) const
			   
{
  int return_value = SDL_BlitSurface( const_cast<SDL_Surface*>( d_surface ),
				      source_rectangle,
				      destination_surface.d_surface,
				      destination_rectangle );

  TEST_FOR_EXCEPTION( return_value != 0,
		      ExceptionType,
		      "Error: Unable to perform surface blit! "
		      "SDL_Error: " << SDL_GetError() );
}

// Export the surface to a bmp file
void Surface::exportToBMP( const std::string bmp_file_name ) const
{
  // Make sure the file name is valid
  testPrecondition( bmp_file_name.size() > 0 );
  
  int return_value = SDL_SaveBMP( const_cast<SDL_Surface*>( d_surface ),
				  bmp_file_name.c_str() );

  TEST_FOR_EXCEPTION( return_value != 0,
		      ExceptionType,
		      "Error: Unable to export the surface to a bitmap! "
		      "SDL_Error: " << SDL_GetError() );
}

// Initialize an RGB surface
void Surface::initializeRGBSurface( const int width,
				    const int height,
				    const Uint32 pixel_format )
{
  // Make sure the dimensions are valid
  testPrecondition( width > 0 );
  testPrecondition( height > 0 );

  int bits_per_pixel;
  Uint32 rmask, gmask, bmask, amask;

  SDL_bool return_value = SDL_PixelFormatEnumToMasks( pixel_format,
						      &bits_per_pixel,
						      &rmask,
						      &gmask,
						      &bmask,
						      &amask );

  TEST_FOR_EXCEPTION( return_value != SDL_TRUE,
		      ExceptionType,
		      "Error: The pixel format " << 
		      SDL_GetPixelFormatName( pixel_format ) <<
		      " could not be used to create a blank surface! "
		      "SDL_Error: " << SDL_GetError() );

  d_surface = SDL_CreateRGBSurface( 0, 
				    width,
				    height,
				    bits_per_pixel,
				    rmask,
				    gmask,
				    bmask,
				    amask );

  TEST_FOR_EXCEPTION( d_surface == NULL,
		      ExceptionType,
		      "Error: The blank surface could not be created! "
		      "SDL_Error: " << SDL_GetError() );
}

// Free the surface
void Surface::free()
{
  
  if( d_owns_surface )
    SDL_FreeSurface( d_surface );

  d_surface = NULL;
}

} // end GDev namespace

//---------------------------------------------------------------------------//
// end Surface.cpp
//---------------------------------------------------------------------------//
