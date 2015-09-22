//---------------------------------------------------------------------------//
//!
//! \file   Texture.hpp
//! \author Alex Robinson, Sean Robinson
//! \brief  The texture class declaration
//!
//---------------------------------------------------------------------------//

#ifndef TEXTURE_HPP
#define TEXTURE_HPP

// Boost Includes
#include <boost/scoped_ptr.hpp>

// SDL Includes
#include <SDL2/SDL.h>

// GDev Includes
#include "RenderableObject.hpp"

//! The texture class
class Texture : public RenderableObject
{

public:
  
  //! Default constructor
  Texture();

  //! Destructor
  ~Texture();

  //! Load the image
  void loadFromFile( const std::string& filename,
		     const SDL_Color* color_key = NULL )

  //! Load the text
  void loadFromText( const std::string& message,
		     const SDL_Color& text_color );

  //! Set the color modulation
  void setColorModulation( const SDL_Color& color_modulation );

  //! Get the color modulation
  SDL_Color getColorModulation() const;

  //! Set the blending
  void setBlendMode( const SDL_BlendMode blending );

  //! Get the blending
  SDL_BlendMode getBlendMode() const;

  //! Set the alpha modulation
  void setAlpha( const unsigned char alpha );

  //! Get the alpha modulation
  unsigned char getAlpha() const;

  //! Render the texture with default parameters
  void render() const;

  //! Render the texture will user parameters
  void render( const int x_position,
	       const int y_position,
	       const SDL_Rect* clip = NULL,
	       const double angle = 0.0,
	       const SDL_Point* center = NULL,
	       const SDL_RendererFlip flip = SDL_FLIP_NONE ) const;

  //! Get the image width
  unsigned getWidth() const;

  //! Get the image height
  unsigned getHeight() const;

private:

  // Free texture
  void freeTexture();

  // The SDL texture
  SDL_Texture* d_texture;

  // The image width
  unsigned d_width;

  // The image height
  unsigned d_height;
};

// end TEXTURE_HPP

//---------------------------------------------------------------------------//
// end Texture.hpp
//---------------------------------------------------------------------------//
