//---------------------------------------------------------------------------//
//!
//! \file   StreamingTexture.cpp
//! \author Alex Robinson
//! \brief  The streaming texture class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <cstring>

// GDev Includes
#include "StreamingTexture.hpp"
#include "ExceptionTestMacros.hpp"
#include "DBCMacros.hpp"

namespace GDev{

// Blank constructor 
StreamingTexture::StreamingTexture( const std::shared_ptr<Renderer>& renderer,
		  const int width,
		  const int height,
		  const Uint32 format = SDL_PIXELFORMAT_ARGB8888 ) 
  : Texture( renderer, SDL_TEXTUREACCESS_STREAMING, format, width, height )
{
  // Make sure the renderer is valid
  testPrecondition( d_renderer );
}

// Check if the texture is locked
bool StreamingTexture::isLocked()
{
  return d_is_locked;
}

// Copy the surface to the texture
void StreamingTexture::copy( const Surface& surface )
{
  // Make sure the surface is valid 
  testPrecondition( surface.getWidth() == this->getWidth() );
  testPrecondition( surface.getHeight() == this->getHeight() );
  
  if( surface.getPixelFormat().format == this->getFormat() )
    this->copy( surface.getPixels(), surface.getNumberOfPixels() );
  else
  {
    Surface converted_surface( surface, this->getFormat() );

    this->copy( surface.getPixels(), surface.getNumberOfPixels() );
  }
}

// Copy the pixels to the texture
void StreamingTexture::copy( const void* pixels, const unsigned num_pixels )
{
  // Make sure there is at least one pixel
  this->lock();

  // Determine the number of pixels to copy
  size_t num_pixels_to_copy;
  
  if( num_pixels < d_num_locke_pixels )
    num_pixels_to_copy = num_pixels;
  else
    num_pixels_to_copy = d_num_locked_pixels;

  // Copy the pixels from the destination to the texture
  memcpy( d_pixels, pixels, num_pixels_to_copy );
  
  this->unlock();
}

// Lock the texture
void StreamingTexture::lock()
{
  // Make sure the texture is unlocked
  testPrecondition( !d_is_locked );

  int return_value = SDL_LockTexture( this->getRawTexturePtr(),
				      NULL,
				      &d_pixels,
				      &d_pitch );

  d_num_locked_pixels = d_pitch*this->getHeight()/
    SDL_BYTESPERPIXEL(this->getFormat());

  TEST_FOR_EXCEPTION( return_value != 0,
		      ExceptionType,
		      "Error: The streaming texture could not be locked! "
		      "SDL_Error: " << SDL_GetError() );
}

// Unlock the texture
void StreamingTexture::unlock()
{
  // Make sure the texture is locked
  testPrecondition( d_is_locked );

  SDL_UnlockTexture( this->getRawTexturePtr() );
}

} // end GDev namespace

//---------------------------------------------------------------------------//
// end StreamingTexture.cpp
//---------------------------------------------------------------------------//
