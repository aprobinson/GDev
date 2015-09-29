//---------------------------------------------------------------------------//
//!
//! \file   Texture.cpp
//! \author Alex Robinson, Sean Robinson
//! \brief  The texture class definition
//!
//---------------------------------------------------------------------------//

// GDev Includes
#include "Texture.hpp"
#include "ExceptionTestMacros.hpp"
#include "DBCMacros.hpp"

namespace GDev{

// Renderer constructor
Texture::Texture( const std::shared_ptr<Renderer>& renderer,
	 const Uint32 pixel_format,
	 const int texture_access,
	 const unsigned width,
	 const unsigned height )
  : d_texture( SDL_CreateTexture( renderer->getRawRendererPtr(),
				  pixel_format,
				  texture_access,
				  width,
				  height ) ),
    d_width( width ),
    d_height( height ),
    d_renderer( renderer )	       
{
  // Make sure the renderer is valid
  testPrecondition( d_renderer );

  // Make sure the texture was created successfully
  TEST_FOR_EXCEPTION( d_texture == NULL,
		      ExceptionType,
		      "Error: The texture could not be created! "
		      "SDL_Error: " << SDL_GetError() );
}

// Surface constructor
Texture::Texture( const std::shared_ptr<Renderer>& renderer,
		  Surface& surface )
  : d_texture( SDL_CreateTextureFromSurface( renderer->getRawRendererPtr(),
					     surface.getRawSurfacePtr() ) ),
    d_width( surface.getWidth() ),
    d_height( surface.getHeight() ),
    d_renderer( renderer )
{
  // Make sure the renderer is valid
  testPrecondition( d_renderer );

  // Make sure the texture was created successfully
  TEST_FOR_EXCEPTION( d_texture == NULL,
		      ExceptionType,
		      "Error: The texture could not be created! "
		      "SDL_Error: " << SDL_GetError() );
}

// Image constructor
Texture::Texture( const std::shared_ptr<Renderer>& renderer,
		  const std::string& image_name )
  : d_texture( NULL ),
    d_width( 0 ),
    d_height( 0 ),
    d_renderer( renderer )
{
  // Make sure the renderer is valid
  testPrecondition( d_renderer );
  
  // Create a surface for the image
  Surface tmp_surface( image_name );

  // Create the texture from the surface
  d_texture = SDL_CreateTextureFromSurface( renderer->getRawRendererPtr(),
					    tmp_surface.getRawSurfacePtr() );

  d_width = tmp_surface.getWidth();
  d_height = tmp_surface.getHeight();

  // Make sure the texture was created successfully
  TEST_FOR_EXCEPTION( d_texture == NULL,
		      ExceptionType,
		      "Error: The texture could not be created! "
		      "SDL_Error: " << SDL_GetError() );
}

// Text constructor
Texture::Texture( const std::shared_ptr<Renderer>& renderer,
		  const std::string& message,
		  const Font& font,
		  const SDL_Color& text_color,
		  const SDL_Color* background_color )
  : d_texture( NULL ),
    d_renderer( renderer )
{
  // Make sure the renderer is valid
  testPrecondition( d_renderer );

  // Create a surface for the image
  Surface tmp_surface( message, font, text_color, background_color );

  // Create the texture from the surface
  d_texture = SDL_CreateTextureFromSurface( renderer->getRawRendererPtr(),
					    tmp_surface.getRawSurfacePtr() );

  d_width = tmp_surface.getWidth();
  d_height = tmp_surface.getHeight();

  // Make sure the texture was created successfully
  TEST_FOR_EXCEPTION( d_texture == NULL,
		      ExceptionType,
		      "Error: The texture could not be created! "
		      "SDL_Error: " << SDL_GetError() );
}

// Destructor
Texture::~Texture()
{
  this->free();
}

// Get the width of the texture
unsigned Texture::getWidth() const
{
  return d_width;
}

// Get the height of the texture
unsigned Texture::getHeight() const
{
  return d_height;
}

// Get the alpha modulation
Uint8 Texture::getAlphaMod() const
{
  Uint8 alpha;
  
  int return_value = 
    SDL_GetTextureAlphaMod( const_cast<SDL_Texture*>( d_texture ), &alpha );

  TEST_FOR_EXCEPTION( return_value != 0,
		      ExceptionType,
		      "Error: The alpha modulation could not be retrieved "
		      "from the texture! SDL_Error: " << SDL_GetError() );

  return alpha;
}

// Set the alpha modulation
void Texture::setAlphaMod( const Uint8 alpha )
{
  int return_value = SDL_SetTextureAlphaMod( d_texture, alpha );

  TEST_FOR_EXCEPTION( return_value != 0,
		      ExceptionType,
		      "Error: The alpha modulation could not be set for the "
		      "texture! SDL_Error: " << SDL_GetError() );
}

// Get the color modulation
void Texture::getColorMod( Uint8& red, Uint8& green, Uint8& blue ) const
{
  int return_value = 
    SDL_GetTextureColorMod( const_cast<SDL_Texture*>( d_texture ),
			    &red,
			    &green,
			    &blue );

  TEST_FOR_EXCEPTION( return_value != 0,
		      ExceptionType,
		      "Error: The color modulation could not be retrieved "
		      "from the texture! SDL_Error: " << SDL_GetError() );
}

// Set the color modulation
void Texture::setColorMod( const Uint8 red, 
			   const Uint8 green,
			   const Uint8 blue )
{
  int return_value = SDL_SetTextureColorMod( d_texture, 
					     red,
					     green,
					     blue );

  TEST_FOR_EXCEPTION( return_value != 0,
		      ExceptionType,
		      "Error: The color modulation could not be set for the "
		      "texture! SDL_Error: " << SDL_GetError() );
}

// Get the blend mode
SDL_BlendMode Texture::getBlendMode() const
{
  SDL_BlendMode mode;

  int return_value = 
    SDL_GetTextureBlendMode( const_cast<SDL_Texture*>( d_texture ), &mode );

  TEST_FOR_EXCEPTION( return_value != 0,
		      ExceptionType,
		      "Error: The blend mode could not be retrieved from the "
		      "texture! SDL_Error: " << SDL_GetError() );

  return mode;
}

// Set the blending
void Texture::setBlendMode( const SDL_BlendMode mode )
{
  int return_value = SDL_SetTextureBlendMode( d_texture, mode );

  TEST_FOR_EXCEPTION( return_value != 0,
		      ExceptionType,
		      "Error: The blend mode could not be set for the "
		      "texture! SDL_Error: " << SDL_GetError() );
}

// Render the texture with default parameters
void Texture::render()
{
  int return_value = SDL_RenderCopy( d_renderer->getRawRendererPtr(),
				     d_texture,
				     NULL,
				     NULL );

  TEST_FOR_EXCEPTION( return_value != 0,
		      ExceptionType,
		      "Error: The texture could not be rendered! "
		      "SDL_Error: " << SDL_GetError() );
}

// Render the texture will user parameters
void Texture::render( const int x_position,
		      const int y_position,
		      const SDL_Rect* texture_clip,
		      const double rotation_angle,
		      const SDL_Point* rotation_center,
		      const SDL_RendererFlip flip )
{
  // Set the target rectangle where the texture clip will be rendered
  SDL_Rect target_rect = { x_position, y_position, d_width, d_height };
			   

  // Set the clip rendering dimensions
  if( texture_clip != NULL )
  {
    target_rect.w = texture_clip->w;
    target_rect.h = texture_clip->h;
  }

  this->render( texture_clip, 
		&target_rect, 
		rotation_angle, 
		rotation_center, 
		flip );
}

// Render the texture
void Texture::render( const SDL_Rect* texture_rect,
		      const SDL_Rect* target_rect,
		      const double rotation_angle,
		      const SDL_Point* rotation_center,
		      const SDL_RendererFlip flip )
{
  int return_value = SDL_RenderCopyEx( d_renderer->getRawRendererPtr(),
				       d_texture,
				       texture_rect,
				       target_rect,
				       rotation_angle,
				       rotation_center,
				       flip );

  TEST_FOR_EXCEPTION( return_value != 0,
		      ExceptionType,
		      "Error: The texture could not be rendered! "
		      "SDL_Error: " << SDL_GetError() );
}
  
// Free texture
void Texture::free()
{
  SDL_DestroyTexture( d_texture );
  
  d_texture = NULL;

  d_width = 0;
  d_height = 0;
}

} // end GDev namespace

//---------------------------------------------------------------------------//
// end Texture.cpp
//---------------------------------------------------------------------------//
