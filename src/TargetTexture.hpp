//---------------------------------------------------------------------------//
//!
//! \file   TargetTexture.hpp
//! \author Alex Robinson
//! \brief  The target texture class declaration
//!
//---------------------------------------------------------------------------//

#ifndef GDEV_TARGET_TEXTURE_HPP
#define GDEV_TARGET_TEXTURE_HPP

// GDev Includes
#include "Texture.hpp"

namespace GDev{

//! The target texture wrapper class
class TargetTexture : public Texture
{

public:
  
  //! Basic blank constructor
  TargetTexture( const std::shared_ptr<Renderer>& renderer,
		 const Uint32 format = SDL_PIXELFORMAT_ARGB8888 );

  //! Blank constructor
  TargetTexture( const std::shared_ptr<Renderer>& renderer,
		 const int width,
		 const int height,
		 const Uint32 format = SDL_PIXELFORMAT_ARGB8888 );

  //! Destructor
  ~TargetTexture()
  { /* ... */ }

  //! Get the access pattern
  SDL_TextureAccess getAccessPattern() const;

  //! Check if this is the rendering target
  bool isRenderTarget() const;

  //! Set as the current rendering target
  void setAsRenderTarget();
  
  //! Unset as the current rendering target
  void unsetAsRenderTarget();

private:

  // Do not allow default constructor
  TargetTexture();
};

} // end GDev namespace

#endif // end GDEV_TARGET_TEXTURE_HPP

//---------------------------------------------------------------------------//
// end TargetTexture.hpp
//---------------------------------------------------------------------------//
