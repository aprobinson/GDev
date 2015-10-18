//---------------------------------------------------------------------------//
//!
//! \file   StaticTexture.hpp
//! \author Alex Robinson
//! \brief  The static texture class declaration
//!
//---------------------------------------------------------------------------//

#ifndef GDEV_STATIC_TEXTURE_HPP
#define GDEV_STATIC_TEXTURE_HPP

// GDev Includes
#include "Texture.hpp"

namespace GDev{

//! The static texture wrapper class
class StaticTexture : public Texture
{
  
public:

  //! Shape constructor
  StaticTexture( const std::shared_ptr<Renderer>& renderer,
		 const Shape& area,
		 const SDL_Color& inside_color,
		 const SDL_Color& edge_color,
		 const SDL_Color& outside_color );

  //! Surface constructor
  StaticTexture( const std::shared_ptr<Renderer>& renderer,
		 const Surface& surface );

  //! Image constructor
  StaticTexture( const std::shared_ptr<Renderer>& renderer,
		 const std::string& image_name );

  //! Text constructor
  StaticTexture( const std::shared_ptr<Renderer>& renderer,
		 const std::string& message,
		 const Font& font,
		 const SDL_Color& text_color,
		 const SDL_Color* background_color = NULL );
  
  //! Destructor
  ~StaticTexture()
  { /* ... */ }

  //! Get the access pattern
  SDL_TextureAccess getAccessPattern() const;

private:

  // Do not allow default construction
  StaticTexture();
};

} // end GDev namespace

#endif // end GDEV_STATIC_TEXTURE_HPP

//---------------------------------------------------------------------------//
// end StaticTexture.hpp
//---------------------------------------------------------------------------//
