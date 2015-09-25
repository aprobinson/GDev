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
#include <memory>

// SDL Includes
#include <SDL2/SDL.h>

namespace GDev{

/*! The surface wrapper class
 * \details The wrapper class does not allow copy construction or assignment.
 * If multiple "copies" are needed, use a smart pointer class.
 */
class Surface
{

public:

  //! Image Constructor
  Surface( const std::string& image_name );

  //! Existing surface constructor (will not take ownership)
  Surface( const SDL_Surface* existing_surface );

  //! Destructor
  ~Surface();

  //! Check if the surface has local ownership
  bool isLocallyOwned() const;

  //! Check if the surface is locked
  bool isLocked() const;

  //! Lock the surface
  void lock();

  //! Unlock the surface
  void unlock();

  //! Get the width of the surface
  int getWidth() const;

  //! Get the height of the surface
  int getHeight() const;

  //! Get the length of a row of pixels in bytes (pitch)
  int getPitch() const;

  //! Get the format of the pixels stored in the surface
  SDL_PixelFormat getPixelFormat() const;

  //! Get the SDL_Rect structure used to clip blits to the surface
  const SDL_Rect& getClipRectangle() const;

  //! Set the SDL_Rect structure used to clip blits to the surface
  void setClipRectangle( const SDL_Rect& clip_rectangle );

  //! Get the color key (transparent pixel) for the surface
  Uint32 getColorKey() const;

  //! Set the color key (transparent pixel) for the surface
  Uint32 setColorKey( const Uint32 color_key );

  //! Disable the color key (transparent pixel)
  void disableColorKey();

  //! Enable the color key (transparent pixel )
  void enableColorKey();

  //! Get the alpha modulation
  Unit8 getAlphaMod() const;

  //! Set the alpha modulation
  void setAlphaMod( const Unit8 alpha ) const;

  //! Get the blend mode
  SDL_BlendMode getBlendMode() const;

  //! Set the blend mode
  void setBlendMode( const SDL_BlendMode blendMode );

  //! Get the color modulation
  void getColorMod( Uint8& red, Uint8& green, Uint8& blue ) const;

  //! Set the color modulation
  void setColorMod( const Uint8 red, const Uint8 green, const Uint8 blue );

  //! Get the raw surface pointer (potentially dangerous)
  const SDL_Surface* getRawSurfacePtr() const;
  
  //! Get the raw surface pointer (potentially dangerous)
  SDL_Surface* getRawSurfacePtr();

  //! Perform a scaled surface copy to the destination surface
  void blitScaled( Surface& destination_surface,
		   const SDL_Rect* source_rectangle = NULL,
		   const SDL_Rect* destination_rectangle = NULL ) const;
  
  //! Perform a fast surface copy to the destination surface
  void blitSurface( Surface& destination_surface,
		    const SDL_Rect* source_rectangle = NULL,
		    const SDL_Rect* destination_rectangle = NULL ) const;

  //! Export the surface to a bmp file
  void exportToBMP( const std::string bmp_file_name ) const;

private:

  //! Free the surface
  void free();

  //! Do not allow default construction
  Surface();

  //! Do not allow copy construction 
  Surface( const Surface& other_surface );
  
  //! Do not allow assignment
  Surface& operator=( const Surface& other_surface );

  // The SDL surface
  SDL_Surface* d_surface;

  // Flag that indicates if the wrapper owns the surface
  bool d_owns_surface;		    
};

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

} // end GDev namespace

#endif // end GDEV_SURFACE_HPP

//---------------------------------------------------------------------------//
// end Surface.hpp
//---------------------------------------------------------------------------//
