//---------------------------------------------------------------------------//
//!
//! \file   StaticTexture.cpp
//! \author Alex Robinson
//! \brief  The static texture class definition
//!
//---------------------------------------------------------------------------//

// GDev Includes
#include "StaticTexture.hpp"
#include "ExceptionTestMacros.hpp"
#include "DBCMacros.hpp"

namespace GDev{

// Surface constructor
StaticTexture::StaticTexture( const std::shared_ptr<Renderer>& renderer,
			      const Surface& surface )
  : Texture( renderer, surface )
{ 
  // Make sure the renderer is valid
  testPrecondition( renderer );
}

// Image constructor
StaticTexture::StaticTexture( const std::shared_ptr<Renderer>& renderer,
			      const std::string& image_name )
  : Texture( renderer, image_name )
{
  // Make sure the renderer is valid
  testPrecondition( renderer );
}

// Text constructor
StaticTexture::StaticTexture( const std::shared_ptr<Renderer>& renderer,
			      const std::string& message,
			      const Font& font,
			      const SDL_Color& text_color,
			      const SDL_Color* background_color )
  : Texture( renderer, message, font, text_color, background_color )
{
  // Make sure the renderer is valid
  testPrecondition( renderer );
}

} // end GDev namespace

//---------------------------------------------------------------------------//
// end StaticTexture.cpp
//---------------------------------------------------------------------------//
