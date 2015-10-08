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
unsigned Surface::getWidth() const
{
  return d_surface->w;
}

// Get the height of the surface
unsigned Surface::getHeight() const
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

// Get the SDL_Rect structure used to clip blits to the surface
const SDL_Rect& Surface::getClipRectangle() const
{
  return d_surface->clip_rect;
}

// Set the SDL_Rect structure used to clip blits to the surface
bool Surface::setClipRectangle( const SDL_Rect& clip_rectangle )
{
  if( SDL_SetClipRect( d_surface, &clip_rectangle ) == SDL_TRUE )
    return true;
  else
    return false;
}

// Get the color key (transparent pixel) for the surface
Uint32 Surface::getColorKey() const
{
  // Make sure the color key is enabled
  testPrecondition( this->isColorKeyEnabled() );
  
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

// Check if the color key is enabled
bool Surface::isColorKeyEnabled() const
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

// Disable the color key (transparent pixel)
void Surface::disableColorKey()
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
  int return_value = SDL_LockSurface( d_surface );

  TEST_FOR_EXCEPTION( return_value != 0,
		      ExceptionType,
		      "Error: Unable to lock the surface! "
		      "SDL_Error: " << SDL_GetError() );
}

// Unlock the surface
void Surface::unlock()
{
  SDL_UnlockSurface( d_surface );
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

// Free the surface
void Surface::free()
{
 
  SDL_FreeSurface( d_surface );

  d_surface = NULL;
}

} // end GDev namespace

//---------------------------------------------------------------------------//
// end Surface.cpp
//---------------------------------------------------------------------------//
