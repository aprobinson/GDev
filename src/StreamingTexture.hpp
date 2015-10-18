//---------------------------------------------------------------------------//
//!
//! \file   StreamingTexture.hpp
//! \author Alex Robinson
//! \brief  The streaming texture class declaration
//!
//---------------------------------------------------------------------------//

#ifndef GDEV_STREAMING_TEXTURE_HPP
#define GDEV_STREAMING_TEXTURE_HPP

// GDev Includes
#include "StreamingTexture.hpp"
#include "Texture.hpp"

namespace GDev{

//! The streaming texture wrapper class
class StreamingTexture : public Texture
{

public:

  //! Blank constructor 
  StreamingTexture( const std::shared_ptr<Renderer>& renderer,
		    const int width,
		    const int height,
		    const Uint32 format = SDL_PIXELFORMAT_ARGB8888 );

  //! Surface constructor
  StreamingTexture( const std::shared_ptr<Renderer>& renderer,
		    const Surface& surface );

  //! Destructor
  ~StreamingTexture()
  { /* ... */ }

  //! Get the access pattern
  SDL_TextureAccess getAccessPattern() const;

  //! Check if the texture is locked
  bool isLocked();

  //! Copy the surface to the texture
  void copy( const Surface& surface );
	     
private:

  //! Copy the pixels to the texture
  void copy( const void* pixels, const unsigned num_pixels );

  //! Lock the texture
  void lock();

  //! Lock a section of the texture
  void lockSection( const SDL_Rect& section );
  
  //! Unlock the texture
  void unlock();

  //! Do not allow default construction
  StreamingTexture();

  // Records if the texture is locked
  bool d_is_locked;

  // The pixel pointer
  void* d_pixels;

  // The pixel pitch
  int d_pitch;

  // The number of pixels
  unsigned d_num_locked_pixels;
};

} // end GDev namespace

#endif // end GDEV_STREAMING_TEXTURE_HPP

//---------------------------------------------------------------------------//
// end StreamingTexture.hpp
//---------------------------------------------------------------------------//
