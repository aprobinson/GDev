//---------------------------------------------------------------------------//
//!
//! \file   Texture.hpp
//! \author Alex Robinson, Sean Robinson
//! \brief  The texture base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef GDEV_TEXTURE_HPP
#define GDEV_TEXTURE_HPP

// Std Lib Includes
#include <string>
#include <stdexcept>
#include <memory>
#include <vector>

// Boost Includes
#include <boost/scoped_ptr.hpp>
#include <boost/core/noncopyable.hpp>

// SDL Includes
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

// GDev Includes
#include "Renderer.hpp"
#include "RenderableObject.hpp"
#include "Shape.hpp"

namespace GDev{

//! The texture exception class
class TextureException : public std::runtime_error
{
public:
  TextureException( const std::string& message )
    : std::runtime_error( message )
  { /* ... */ }

  ~TextureException() throw()
  { /* ... */ }
};

/*! The texture wrapper base class
 * \details The wrapper class does not allow copy construction or assignment.
 * If multiple "copies" are needed, use a smart pointer class.
 */
class Texture : public RenderableObject, private boost::noncopyable
{
  
public:

  //! The exception class
  typedef TextureException ExceptionType;

  //! Destructor
  virtual ~Texture();

  //! Get the width of the texture
  int getWidth() const;

  //! Get the height of the texture
  int getHeight() const;

  //! Get the alpha modulation
  Uint8 getAlphaMod() const;

  //! Set the alpha modulation
  void setAlphaMod( const Uint8 alpha );

  //! Get the color modulation
  void getColorMod( Uint8& red, Uint8& green, Uint8& blue ) const;

  //! Set the color modulation
  void setColorMod( const Uint8 red, const Uint8 green, const Uint8 blue );

  //! Get the blend mode
  SDL_BlendMode getBlendMode() const;

  //! Set the blend mode
  void setBlendMode( const SDL_BlendMode mode );

  //! Get the texture format
  Uint32 getFormat() const;

  //! Get the access pattern
  virtual SDL_TextureAccess getAccessPattern() const = 0;

  //! Get the raw texture pointer (potentially dangerous)
  const SDL_Texture* getRawTexturePtr() const;

  //! Get the raw texture pointer (potentially dangerous)
  SDL_Texture* getRawTexturePtr();

  //! Render the texture
  void render() const;

  //! Render the whole texture clip at the desired point
  void render( const int target_x_position, 
	       const int target_y_position, 
	       const SDL_Rect* texture_clip = NULL,
	       const double rotation_angle = 0.0,
	       const SDL_Point* rotation_center = NULL,
	       const SDL_RendererFlip flip = SDL_FLIP_NONE ) const;

  //! Render the texture
  void render( const SDL_Rect* target_clip,
	       const SDL_Rect* texture_clip = NULL,
	       const double rotation_angle = 0.0,
	       const SDL_Point* rotation_center = NULL,
	       const SDL_RendererFlip flip = SDL_FLIP_NONE ) const;

protected:

  //! Blank texture constructor
  Texture( const std::shared_ptr<Renderer>& renderer,
	   const SDL_TextureAccess access,
	   const Uint32 format,
	   const unsigned width,
	   const unsigned height );

  //! Shape constructor
  Texture( const std::shared_ptr<Renderer>& renderer,
	   const Shape& area,
	   const SDL_Color& inside_color,
	   const SDL_Color& edge_color,
	   const SDL_Color& outside_color );

  //! Surface constructor
  Texture( const std::shared_ptr<Renderer>& renderer,
	   const Surface& surface );

  //! Image constructor
  Texture( const std::shared_ptr<Renderer>& renderer,
	   const std::string& image_name );	   

  //! Text constructor
  Texture( const std::shared_ptr<Renderer>& renderer,
	   const std::string& message,
	   const Font& font,
	   const SDL_Color& text_color,
	   const SDL_Color* background_color );

  //! Get the renderer
  const Renderer& getRenderer() const;

  //! Get the renderer
  Renderer& getRenderer();

private:

  // Free the texture
  void free();

  // Load the texture format
  void loadTextureFormat();

  // The SDL texture
  SDL_Texture* d_texture;

  // The width of the texture
  int d_width;

  // The height of the texture
  int d_height;

  // The texture format
  Uint32 d_format;

  // The renderer used by the texture
  std::shared_ptr<Renderer> d_renderer;
};

} // end GDev namespace

#endif // end GDEV_TEXTURE_HPP

//---------------------------------------------------------------------------//
// end Texture.hpp
//---------------------------------------------------------------------------//
