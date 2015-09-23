//---------------------------------------------------------------------------//
//!
//! \file   StartButton_def.hpp
//! \author Alex Robinson, Sean Robinson
//! \brief  The start button class definition
//!
//---------------------------------------------------------------------------//

#ifndef START_BUTTON_DEF_HPP
#define START_BUTTON_DEF_HPP

// Std Lib Includes
#include <string>

// Constructor
template<typename Shape>
StartButton<Shape>::StartButton( const Shape& button_shape,
				 const TTF_Font& font,
				 const SDL_Color& text_color,
				 const SDL_Color& background_color,
				 const SDL_Color* scroll_over_backround_color,
				 const SDL_Color* press_background_color )
  : ShapeButton( button_shape ),
    d_default_texture(),
    d_button_scroll_over_texture(),
    d_button_press_texture(),
    d_current_texture( NULL ),
    d_game_started( false )
{
  std::string button_message( "START" );
  
  // Create the default texture
  d_default_texture.loadFromText( button_message,
				  font, 
				  text_color, 
				  &background_color );
  
  // Create the button scroll over texture
  if( scroll_over_background_color == NULL )
  {
    d_button_scroll_over_texture.loadFromText( button_message,
					       font,
					       text_color,
					       &background_color );
  }
  else
  {
    d_button_scroll_over_texture.loadFromText( button_message,
					       font,
					       text_color,
					       scroll_over_background_color );
  }

  // Create the press button texture
  if( press_background_color == NULL )
  {
    d_button_press_texture.loadFromText( button_message,
					 font,
					 text_color,
					 &background_color );
  }
  else
  {
    d_button_press_texture.loadFromText( button_message,
					 font,
					 text_color,
					 press_background_color );
  }

  d_current_texture = &d_default_texture;
}

// Render the start button
template<typename Shape>
void StartButton<Shape>::render() const
{
  d_current_texture->render( this->getUpperLeftXPos()
			     this->getUpperRightXPos() );
}

// Check if the game has started
template<typename Shape>
bool StartButton<Shape>::hasGameStarted() const
{
  return d_game_started;
}

// Handle default
template<typename Shape>
void StartButton<Shape>::handleDefault()
{
  d_current_texture = &d_default_texture;
}

// Handle button scroll over
template<typename Shape>
void StartButton<Shape>::handleButtonScrollOver()
{
  d_current_texture = d_button_scroll_over_texture;
}
  
// Handle button press
template<typename Shape>
void StartButton<Shape>::handleButtonPress()
{
  d_current_texture = d_button_press_texture;
}

// Handle button release
template<typename Shape>
void StartButton<Shape>::handleButtonRelease()
{
  d_current_texture = d_button_press_texture;

  // Indicate that the game has started
  d_game_started = true;
}

#endif // end START_BUTTON_DEF_HPP

//---------------------------------------------------------------------------//
// end StartButton_def.hpp
//---------------------------------------------------------------------------//
