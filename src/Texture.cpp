//---------------------------------------------------------------------------//
//!
//! \file   Texture.cpp
//! \author Alex Robinson
//! \brief  The texture class definition
//!
//---------------------------------------------------------------------------//

// GDev Includes
#include "Texture.hpp"

// Default constructor
Texture::Texture()
  : d_texture( NULL ),
    d_width(),
    d_height()
{ /* ... */ }

// Load the image
void Texture::loadFromFile( const std::string& filename,
			    const unsigned char color_key_red = 0xFF,
			    const unsigned char color_key_green = 0xFF,
			    const unsigned char color_key_blue = 0xFF )
{

}

// Load the text
void Texture::loadFromText( const std::string& message,
			    const TTF_Font& font,
			    const SDL_Color& text_color,
			    const SDL_Color* background_color )
{
  
}

// Set the color modulation
void Texture::setColorModulation( const SDL_Color& color_modulation )
{

}

// Set the blending
void Texture::setBlendMode( const SDL_BlendMode blending )
{

}

// Set the alpha modulation
void Texture::setAlpha( const unsigned char alpha )
{

}

// Render the texture with default parameters
void Texture::render() const
{
  this->render( 0, 0 );
}

// Render the texture will user parameters
void render( const int x_position,
	     const int y_position,
	     const SDL_Rect* clip,
	     const double angle,
	     const SDL_Point* center,
	     const SDL_RendererFlip flip ) const
{

}


// Get the image width
unsigned Texture::getWidth() const
{

}

// Get the image height
unsigned Texture::getHeight() const
{

}

// Free texture
void Texture::freeTexture()
{

}

//---------------------------------------------------------------------------//
// end Texture.cpp
//---------------------------------------------------------------------------//
