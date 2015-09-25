//---------------------------------------------------------------------------//
//!
//! \file   Texture.cpp
//! \author Alex Robinson, Sean Robinson
//! \brief  The texture class definition
//!
//---------------------------------------------------------------------------//

// GDev Includes
#include "Texture.hpp"

// Default constructor
Texture::Texture()
  : d_texture( NULL ),
    g_renderer( NULL),
    d_width(),
    d_height()
{ /* ... */ }

// Load the image
void Texture::loadFromFile( const std::string& filename,
			    const unsigned char color_key_red = 0xFF,
			    const unsigned char color_key_green = 0xFF,
			    const unsigned char color_key_blue = 0xFF )
{
  // Deallocate preexisting texture
  this->freeTexture();

  // Load the image
  SDL_Surface* loaded_surface = IMG_LOAD( filename.c_str() );

  if( loaded_surface == NULL )
  {
    std::cerr << "Unable to load image "
	      << filename
	      << "! SDL_image Error: "
	      << IMG_GetError()
	      << std::endl;
  }
  else
  {
    // Color key image
    SDL_SetColorKey( loaded_surface,
		     SDL_TRUE,
		     SDL_MapRGB( loaded_surface->format,
				 color_key_red,
				 color_key_green,
				 color_key_blue ));
    // Create texture from surface pixels
    d_texture = SDL_CreateTextureFromSurface( g_renderer, loaded_surface );

    if( new_texture == NULL )
    {
      std::cerr << "Unable to create texture from "
		<< filename
		<< "! SDL Error: "
		<< SDL_GetError()
		<< std::endl;
    }
    else
    {
      d_width = loaded_surface->w;
      d_height = loaded_surface->h;
    }

    // Free the old loaded surface
    SDL_FreeSurface( loaded_surface );
  }

  return d_texture != NULL;
}

// Load the text
void Texture::loadFromText( const std::string& message,
			    const TTF_Font& font,
			    const SDL_Color& text_color,
			    const SDL_Color* background_color )
{
  // Free preexsting structure
  this->freeTexture();

  // Render text surface
  SDL_Surface* text_surface = TTF_RenderText_Shaded( font,
						     message,
						     text_color,
						     background_color ); 
  if ( text_surface = NULL )
  {
    std::cerr << "Unable to render text surface! SDL_ttf Error: "
	      << TTF_GetError()
	      << std::endl;
  }
  else
  {
    // Create texture from surface pixels
    d_texture = SDL_CreateTextureFromSurface( g_renderer, text_surface );

    if( d_texture == NULL )
    {
      std::cerr << "Unable to create texture from rendered text! SDL Error: "
		<< SDL_GetError()
		<< std:endl;
    }
    else
    {
      // Get image dimensions
      d_width = text_surface->w;
      d_height = text_surface->h;
    }
  }
    return d_texture != NULL;
}

// Set the color modulation
void Texture::setColorModulation( const SDL_Color& color_modulation )
{
  SDL_SetTextureColorMod( d_texture, color_modulation );
}

// Set the blending
void Texture::setBlendMode( const SDL_BlendMode blending )
{
  SDL_SetTextureBlendMode( d_texture, blending );
}

// Set the alpha modulation
void Texture::setAlpha( const unsigned char alpha )
{
  SDL_SetTextureAlpha( d_structure, alpha);
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
  // Set the rendering space and render to screen
  SDL_Rect render_quad = { x_position, y_position, d_width, d_height };

  // Set the clip rendering dimensions
  if( clip != NULL )
  {
    render_quad.w = clip->w;
    render_quad.h = clip->h;
  }

  SDL_RenderCopyEx( g_renderer,
		    d_texture,
		    clip,
		    &render_quad,
		    angle,
		    center,
		    flip );
}

// Get the image width
unsigned Texture::getWidth() const
{
  return d_width;
}

// Get the image height
unsigned Texture::getHeight() const
{
  return d_height;
}

// Free texture
void Texture::freeTexture()
{
  if( d_texture != NULL )
  {
    SDL_DestroyTexture( d_texture );
    d_texture = NULL;
    d_width = 0;
    d_height = 0;
  }
}

//---------------------------------------------------------------------------//
// end Texture.cpp
//---------------------------------------------------------------------------//
