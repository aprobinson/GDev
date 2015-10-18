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

// Blank constructor
Texture::Texture( const std::shared_ptr<Renderer>& renderer,
		  const SDL_TextureAccess access,
		  const Uint32 format,
		  const unsigned width,
		  const unsigned height )
  : d_texture( SDL_CreateTexture( renderer->getRawRendererPtr(),
				  format,
				  access,
				  width,
				  height ) ),
    d_width( width ),
    d_height( height ),
    d_format(),
    d_renderer( renderer )	       
{
  // Make sure the renderer is valid
  testPrecondition( renderer );
  // Make sure the format is valid
  testPrecondition( renderer->isValidTextureFormat( format ) );
  // Make sure the access pattern is valid
  testPrecondition( access != SDL_TEXTUREACCESS_STATIC );
  // Make sure the texture size is valid
  testPrecondition( width <= renderer->getMaxTextureWidth() );
  testPrecondition( height <= renderer->getMaxTextureHeight() );

  // Make sure the texture was created successfully
  TEST_FOR_EXCEPTION( d_texture == NULL,
		      ExceptionType,
		      "Error: The texture could not be created! "
		      "SDL_Error: " << SDL_GetError() );

  this->loadTextureFormat();
}

// Shape constructor
Texture::Texture( const std::shared_ptr<Renderer>& renderer,
		  const Shape& area,
		  const SDL_Color& inside_color,
		  const SDL_Color& edge_color,
		  const SDL_Color& outside_color )
    : d_texture( NULL ),
      d_width( area.getBoundingBoxWidth() ),
      d_height( area.getBoundingBoxHeight() ),
      d_format(),
      d_renderer( renderer )
{
  // Make sure the renderer is valid
  testPrecondition( renderer );
  // Make sure the area is valid
  testPrecondition( area.getBoundingBoxWidth() > 0 ); 
  testPrecondition( area.getBoundingBoxHeight() > 0 ); 

  // Create a shape surface
  try{
    Surface shape_surface( area, inside_color, edge_color, outside_color );
    
    d_texture = SDL_CreateTextureFromSurface(renderer->getRawRendererPtr(),
					     shape_surface.getRawSurfacePtr());
  }
  EXCEPTION_CATCH_RETHROW( ExceptionType,
			   "Error: The texture could not be created!" );

  // Make sure the texture was created successfully
  TEST_FOR_EXCEPTION( d_texture == NULL,
		      ExceptionType,
		      "Error: The texture could not be created! "
		      "SDL_Error: " << SDL_GetError() );

  // Get the texture format
  this->loadTextureFormat();
}

// Surface constructor
Texture::Texture( const std::shared_ptr<Renderer>& renderer,
		  const Surface& surface )
  : d_texture( SDL_CreateTextureFromSurface( 
		    renderer->getRawRendererPtr(),
		    const_cast<SDL_Surface*>( surface.getRawSurfacePtr() ) ) ),
    d_width( surface.getWidth() ),
    d_height( surface.getHeight() ),
    d_format(),
    d_renderer( renderer )
{
  // Make sure the renderer is valid
  testPrecondition( renderer );

  // Make sure the texture was created successfully
  TEST_FOR_EXCEPTION( d_texture == NULL,
		      ExceptionType,
		      "Error: The texture could not be created! "
		      "SDL_Error: " << SDL_GetError() );

  // Get the texture format
  this->loadTextureFormat();
}

// Image constructor
Texture::Texture( const std::shared_ptr<Renderer>& renderer,
		  const std::string& image_name )
  : d_texture( NULL ),
    d_width( 0 ),
    d_height( 0 ),
    d_format(),
    d_renderer( renderer )
{
  // Make sure the renderer is valid
  testPrecondition( renderer );
  
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

  this->loadTextureFormat();
}

// Text constructor
Texture::Texture( const std::shared_ptr<Renderer>& renderer,
		  const std::string& message,
		  const Font& font,
		  const SDL_Color& text_color,
		  const SDL_Color* background_color )
  : d_texture( NULL ),
    d_width(),
    d_height(),
    d_format(),
    d_renderer( renderer )
{
  // Make sure the renderer is valid
  testPrecondition( renderer );

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

  this->loadTextureFormat();
}

// Destructor
Texture::~Texture()
{
  this->free();
}

// Get the width of the texture
int Texture::getWidth() const
{
  return d_width;
}

// Get the height of the texture
int Texture::getHeight() const
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

// Get the texture format
/*! \details This is the format that should be used with pixel transfers.
 */
Uint32 Texture::getFormat() const
{
  return d_format;
}

// Get the raw texture pointer (potentially dangerous)
const SDL_Texture* Texture::getRawTexturePtr() const
{
  return d_texture;
}

// Get the raw texture pointer (potentially dangerous)
SDL_Texture* Texture::getRawTexturePtr()
{
  return d_texture;
}

// Render the texture with default parameters
void Texture::render() const
{
  int return_value = 
    SDL_RenderCopy( const_cast<SDL_Renderer*>(d_renderer->getRawRendererPtr()),
		    const_cast<SDL_Texture*>(d_texture),
		    NULL,
		    NULL );

  TEST_FOR_EXCEPTION( return_value != 0,
		      ExceptionType,
		      "Error: The texture could not be rendered! "
		      "SDL_Error: " << SDL_GetError() );
}

// Render the whole texture clip at the desired point
/*! \details The rotation center is the point on the target around which
 * the target clip will be rotated. The default is the center of the target.
 */
void Texture::render( const int target_x_position,
		      const int target_y_position,
		      const SDL_Rect* texture_clip,
		      const double rotation_angle,
		      const SDL_Point* rotation_center,
		      const SDL_RendererFlip flip ) const
{
  // Set the target rectangle where the texture clip will be rendered
  SDL_Rect target_clip = {target_x_position, 
			  target_y_position, 
			  d_width, 
			  d_height};
			   

  // Set the clip rendering dimensions
  if( texture_clip != NULL )
  {
    target_clip.w = texture_clip->w;
    target_clip.h = texture_clip->h;
  }

  this->render( &target_clip, 
		texture_clip,
		rotation_angle, 
		rotation_center, 
		flip );
}

// Render the texture
/*! \details The rotation center is the point on the target around which
 * the target clip will be rotated. The default is the center of the target.
 */
void Texture::render( const SDL_Rect* target_clip,
		      const SDL_Rect* texture_clip,
		      const double rotation_angle,
		      const SDL_Point* rotation_center,
		      const SDL_RendererFlip flip ) const
{
  int return_value = SDL_RenderCopyEx(
		    const_cast<SDL_Renderer*>(d_renderer->getRawRendererPtr()),
		    const_cast<SDL_Texture*>(d_texture),
		    texture_clip,
		    target_clip,
		    rotation_angle,
		    rotation_center,
		    flip );

  TEST_FOR_EXCEPTION( return_value != 0,
		      ExceptionType,
		      "Error: The texture could not be rendered! "
		      "SDL_Error: " << SDL_GetError() );
}

// Get the renderer
const Renderer& Texture::getRenderer() const
{
  return *d_renderer;
}

// Get the renderer
Renderer& Texture::getRenderer()
{
  return *d_renderer;
}
  
// Free texture
void Texture::free()
{
  SDL_DestroyTexture( d_texture );
  
  d_texture = NULL;

  d_width = 0;
  d_height = 0;
}

// Load the texture format
void Texture::loadTextureFormat()
{
  // Get the texture format
  int return_value = SDL_QueryTexture( const_cast<SDL_Texture*>( d_texture ),
				       &d_format,
				       NULL,
				       NULL,
				       NULL );

  TEST_FOR_EXCEPTION( return_value != 0,
		      ExceptionType,
		      "Error: The texture format could not be retrieved! "
		      "SDL_Error: " << SDL_GetError() );
}

} // end GDev namespace

//---------------------------------------------------------------------------//
// end Texture.cpp
//---------------------------------------------------------------------------//
