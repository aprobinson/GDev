//---------------------------------------------------------------------------//
//!
//! \file   GeneralButton.cpp
//! \author Alex Robinson
//! \brief  The general button class declaration
//!
//---------------------------------------------------------------------------//

// GDev Includes
#include "GeneralButton.hpp"
#include "Surface.hpp"
#include "StaticTexture.hpp"
#include "TargetTexture.hpp"
#include "ExceptionTestMacros.hpp"
#include "ExceptionCatchMacros.hpp"
#include "DBCMacros.hpp"

namespace GDev{

// Constructor
/*! \details A NULL background color will result in the button area being
 * transparent.
 */
GeneralButton::GeneralButton( const std::shared_ptr<WindowRenderer>& renderer,
			      const std::shared_ptr<const Shape>& button_area,
			      const std::string& message,
			      const Font& font,
			      const SDL_Color& text_color,
			      const SDL_Color& edge_color,
			      const SDL_Color& default_background_color,
			      const SDL_Color& press_background_color,
			      const SDL_Color& scroll_over_background_color,
			      const SDL_Color& release_background_color )
  : d_area( button_area )
{
  // Make sure the window renderer is valid
  testPrecondition( renderer );
  // Make sure the area is valid
  testPrecondition( button_area );
  // Make sure the message is valid
  testPrecondition( message.size() > 0 );

  // Create the default texture
  this->initializeTexture( d_default_texture,
			   renderer,
			   button_area,
			   message,
			   font,
			   text_color,
			   edge_color,
			   default_background_color );

  // Create the scroll over texture
  this->initializeTexture( d_scroll_over_texture,
			   renderer,
			   button_area,
			   message,
			   font,
			   text_color,
			   edge_color,
			   scroll_over_background_color );

  // Create the press texture
  this->initializeTexture( d_press_texture,
			   renderer,
			   button_area,
			   message,
			   font,
			   text_color,
			   edge_color,
			   press_background_color );

  // Create the release texture
  this->initializeTexture( d_release_texture,
			   renderer,
			   button_area,
			   message,
			   font,
			   text_color,
			   edge_color,
			   release_background_color );
  
  // Set the active texture to the default texture
  d_active_texture = d_default_texture;
}

// Render the button
void GeneralButton::render() const
{
  d_active_texture->render( d_area->getBoundingBoxXPosition(),
			    d_area->getBoundingBoxYPosition() );
}

// Handle default
void GeneralButton::handleDefault()
{
  d_active_texture = d_default_texture;
}
  
//! Handle button scroll over 
void GeneralButton::handleButtonScrollOver()
{
  d_active_texture = d_scroll_over_texture;
}

// Handle button press
void GeneralButton::handleButtonPress()
{
  d_active_texture = d_press_texture;
}

// Handle button release
void GeneralButton::handleButtonRelease()
{
  d_active_texture = d_release_texture;
}

// Test if the mouse position is inside of the button
bool GeneralButton::isMouseInButton() const
{
  // Get the mouse position
  int x, y;

  SDL_GetMouseState( &x, &y );

  return d_area->isPointIn( x, y );
}

// Initialize the texture
void GeneralButton::initializeTexture( 
			       std::shared_ptr<Texture>& texture,
			       const std::shared_ptr<WindowRenderer>& renderer,
			       const std::shared_ptr<const Shape>& button_area,
			       const std::string& message,
			       const Font& font,
			       const SDL_Color& text_color,
			       const SDL_Color& edge_color,
			       const SDL_Color& background_color )
{
  std::shared_ptr<TargetTexture> target_texture( new TargetTexture( 
					 renderer,
					 button_area->getBoundingBoxWidth(),
  					 button_area->getBoundingBoxHeight(),
  					 SDL_PIXELFORMAT_ARGB8888 ) );

  target_texture->setAsRenderTarget();

  // Create the message texture
  StaticTexture message_texture( renderer,
				 message,
				 font,
				 text_color,
				 &background_color );
  
  // Create the area texture
  SDL_Color outside_color = {0xFF,0xFF,0xFF,0};
  
  StaticTexture area_texture( renderer, 
			      *button_area,
			      background_color,
			      edge_color,
			      outside_color );
  
  // Render the textures to the target texture
  message_texture.render();
  area_texture.render();
  
  target_texture->unsetAsRenderTarget();

  // Assign the input texture
  texture = target_texture;
}
  

} // end GDev namespace

//---------------------------------------------------------------------------//
// end GeneralButton.cpp
//---------------------------------------------------------------------------//
