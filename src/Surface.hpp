//---------------------------------------------------------------------------//
//!
//! \file   Surface.hpp
//! \author Alex Robinson
//! \brief  The surface wrapper class declaration
//!
//---------------------------------------------------------------------------//

#ifndef GDEV_SURFACE_HPP
#define GDEV_SURFACE_HPP

// Std Lib Includes
#include <string>
#include <stdexcept>

// Boost Includes
#include <boost/core/noncopyable.hpp>

// SDL Includes
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

// GDev Includes
#include "Font.hpp"

namespace GDev{

//! The surface exception class
class SurfaceException : public std::runtime_error
{
public:
  SurfaceException( const std::string& message )
    : std::runtime_error( message )
  { /* ... */ }

  ~SurfaceException() throw()
  { /* ... */ }
};

/*! The surface wrapper class
 * \details The wrapper class does not allow copy construction or assignment.
 * If multiple "copies" are needed, use a smart pointer class.
 */
class Surface : private boost::noncopyable
{

public:

  //! The exception class
  typedef SurfaceException ExceptionType;

  //! Image constructor
  Surface( const std::string& image_name );

  //! Text constructor
  Surface( const std::string& message,
	   const Font& font,
	   const SDL_Color& text_color,
	   const SDL_Color* background_color = NULL );

  //! Surface conversion constructor
  Surface( const Surface& other_surface,
	   const Uint32 pixel_format );

  //! Existing surface constructor (will not take ownership)
  Surface( SDL_Surface* existing_surface );

  //! Destructor
  ~Surface();

  //! Check if the surface has local ownership
  bool isLocallyOwned() const;

  //! Get the width of the surface
  unsigned getWidth() const;

  //! Get the height of the surface
  unsigned getHeight() const;

  //! Get the length of a row of pixels in bytes (pitch)
  int getPitch() const;

  //! Get the format of the pixels stored in the surface
  const SDL_PixelFormat& getPixelFormat() const;

  //! Get the number of surface pixels
  unsigned getNumberOfPixels() const;

  //! Get the SDL_Rect structure used to clip blits to the surface
  const SDL_Rect& getClipRectangle() const;

  //! Set the SDL_Rect structure used to clip blits to the surface
  void setClipRectangle( const SDL_Rect& clip_rectangle );

  //! Check if the color key is enabled
  bool isColorKeyEnabled() const;

  //! Get the color key (transparent pixel) for the surface
  Uint32 getColorKey() const;

  //! Set the color key (transparent pixel) for the surface
  void setColorKey( const Uint32 color_key );

  //! Disable the color key (transparent pixel)
  void disableColorKey();

  //! Get the alpha modulation
  Uint8 getAlphaMod() const;

  //! Set the alpha modulation
  void setAlphaMod( const Uint8 alpha );

  //! Get the blend mode
  SDL_BlendMode getBlendMode() const;

  //! Set the blend mode
  void setBlendMode( const SDL_BlendMode blend_mode );

  //! Get the color modulation
  void getColorMod( Uint8& red, Uint8& green, Uint8& blue ) const;

  //! Set the color modulation
  void setColorMod( const Uint8 red, const Uint8 green, const Uint8 blue );

  //! Get the raw surface pointer (potentially dangerous)
  const SDL_Surface* getRawSurfacePtr() const;
  
  //! Get the raw surface pointer (potentially dangerous)
  SDL_Surface* getRawSurfacePtr();

  //! Check if the surface is locked
  bool isLocked() const;

  //! Check if the surface must be locked to access pixels
  bool mustLock() const;

  //! Lock the surface (to access pixels)
  void lock();

  //! Unlock the surface (to acces pixels)
  void unlock();

  //! Get the surface pixels
  const void* getPixels() const;

  //! Perform a scaled surface copy to the destination surface
  void blitScaled( Surface& destination_surface,
		   SDL_Rect* destination_rectangle = NULL,
		   const SDL_Rect* source_rectangle = NULL ) const; 
		   
  
  //! Perform a fast surface copy to the destination surface
  void blitSurface( Surface& destination_surface,
		    SDL_Rect* destination_rectangle = NULL,
		    const SDL_Rect* source_rectangle = NULL ) const;
  
  //! Export the surface to a bmp file
  void exportToBMP( const std::string bmp_file_name ) const;

private:

  // Free the surface
  void free();

  //! Do not allow default construction
  Surface();

  // The SDL surface
  SDL_Surface* d_surface;

  // Flag that indicates if the wrapper owns the surface
  bool d_owns_surface;		    
};

} // end GDev namespace

#endif // end GDEV_SURFACE_HPP

//---------------------------------------------------------------------------//
// end Surface.hpp
//---------------------------------------------------------------------------//
