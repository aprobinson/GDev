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
    d_height(),
    d_x_position(),
    d_y_position(),
    d_clip(),
    d_rotation_angle( 0.0 ),
    d_center(),
    d_flip( SDL_FLIP_NONE )
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
			    const SDL_Color& text_color )
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

// Set the position to render the texture at
void Texture::setPosition( const int x_position, const int y_position )
{

}

// Set the clip rectangle
void Texture::setClipRectangle( const SDL_Rect& clip )
{

}

// Reset the clip rectangle
void Texture::resetClipRectangle()
{

}

// Set the rotation angle (degrees)
void Texture::setRotationAngle( const double angle )
{

}
  
// Reset the rotation angle and rotation point
void Texture::resetRotationAngle()
{

}

// Set the rotation center
void Texture::setRotationCenter( const SDL_Point& center )
{

}

// Reset the rotation center
void Texture::resetRotationCenter()
{

}

// Set the flip state
void Texture::setRendererFlip( const SDL_RendererFlip flip )
{

}

// Reset the renderer flip state
void Texture::resetRendererFlip()
{

}

// Render the texture
void Texture::render() const
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
