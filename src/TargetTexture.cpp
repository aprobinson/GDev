//---------------------------------------------------------------------------//
//!
//! \file   TargetTexture.cpp
//! \author Alex Robinson
//! \brief  The target texture class declaration
//!
//---------------------------------------------------------------------------//

// GDev Includes
#include "TargetTexture.hpp"
#include "ExceptionTestMacros.hpp"
#include "DBCMacros.hpp"

namespace GDev{

// Basic blank constructor
/*! \details The size of the texture will be the size of the rendering
 * target.
 */ 
TargetTexture::TargetTexture( const std::shared_ptr<WindowRenderer>& renderer,
			      const Uint32 format )
  : Texture( renderer, 
	     SDL_TEXTUREACCESS_TARGET, 
	     format,
	     renderer->getOutputWidth(),
	     renderer->getOutputHeight() )
{
  // Make sure the renderer is valid
  testPrecondition( renderer );
  testPrecondition( renderer->isNonDefaultTargetSupported() );
}

// Blank constructor
TargetTexture::TargetTexture( const std::shared_ptr<WindowRenderer>& renderer,
			      const int width,
			      const int height,
			      const Uint32 format )
  : Texture( renderer, SDL_TEXTUREACCESS_TARGET, format, width, height )
{
  // Make sure the renderer is valid
  testPrecondition( renderer );
  testPrecondition( renderer->isNonDefaultTargetSupported() );
}

// Get the access pattern
SDL_TextureAccess TargetTexture::getAccessPattern() const
{
  return SDL_TEXTUREACCESS_TARGET;
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
