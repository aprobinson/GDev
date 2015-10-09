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
class StaticTexture : public Texture, private boost::noncopyable
{
  
public:

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

private:

  // Do not allow default construction
  StaticTexture();
};

} // end GDev namespace

#endif // end GDEV_STATIC_TEXTURE_HPP

//---------------------------------------------------------------------------//
// end StaticTexture.hpp
//---------------------------------------------------------------------------//
