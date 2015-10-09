//---------------------------------------------------------------------------//
//!
//! \file   TargetTexture.cpp
//! \author Alex Robinson
//! \brief  The target texture class declaration
//!
//---------------------------------------------------------------------------//

// GDev Includes
#include "TargetTexture.hpp"
#include "ExceptionTextMacros.hpp"
#include "DBCMacros.hpp"

namespace GDev{

// Blank constructor
TargetTexture::TargetTexture( const std::shared_ptr<Renderer>& renderer,
			      const int width,
			      const int height,
			      const Uint32 format )
  : Texture( renderer, SDL_TEXTUREACCESS_TARGET, format, width, height )
{
  // Make sure the renderer is valid
  testPrecondition( d_renderer );
  testPrecondition( d_renderer->isNonDefaultTargetSupported() );
}

// Check if this is the rendering target
bool TargetTexture::isRenderTarget() const
{
  return this->getRawTexturePtr() == SDL_GetRenderTarget( 
	const_cast<SDL_Renderer*>( this->getRenderer().getRawRendererPtr() ) );
}

// Set as the current rendering target
void TargetTexture::setAsRenderTarget()
{
  // Make sure this is not the rendering target
  testPrecondition( !this->isRenderTarget() );
  
  int return_value = 
    SDL_SetRenderTarget( this->getRenderer().getRawRendererPtr(),
			 this->getRawTexturePtr() );
  
  TEST_FOR_EXCEPTION( return_value != 0,
		      ExceptionType,
		      "Error: The texture could not be set as the rendering "
		      "target! SDL_Error: " << SDL_GetError() );
}
  
// Unset as the current rendering target
void TargetTexture::unsetAsRenderTarget()
{
  // Make sure this is the rendering target
  testPrecondition( this->isRenderTarget() );
  
  int return_value = 
    SDL_SetRenderTarget( this->getRenderer().getRawRendererPtr(), NULL );

  TEST_FOR_EXCEPTION( return_value != 0,
		      ExceptionType,
		      "Error: The default rendering target could not be set "
		      "as the rendering target! SDL_Error: " 
		      << SDL_GetError() );
}

} // end GDev namespace

//---------------------------------------------------------------------------//
// end TargetTexture.cpp
//---------------------------------------------------------------------------//
