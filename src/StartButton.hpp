//---------------------------------------------------------------------------//
//!
//! \file   StartButton.hpp
//! \author Alex Robinson, Sean Robinson
//! \brief  The start button declaration
//!
//---------------------------------------------------------------------------//

#ifndef START_BUTTON_HPP
#define START_BUTTON_HPP

// SDL Includes
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

// GDev Includes
#include "ShapeButton.hpp"
#include "Texture.hpp"

//! The start button class
template<typename Shape>
class StartButton : public ShapeButton<Shape>
{

public:

  //! Constructor
  StartButton( const Shape& button_shape,
	       const TTF_Font& font,
	       const SDL_Color& text_color,
	       const SDL_Color& background_color,
	       const SDL_Color* scroll_over_backround_color = NULL,
	       const SDL_Color* press_background_color = NULL );

  //! Destructor
  ~StartButton()
  { /* ... */ }

  //! Render the start button
  void render() const;

  //! Check if the game has started
  bool hasGameStarted() const;

protected:

  //! Handle default
  void handleDefault();

  //! Handle button scroll over
  void handleButtonScrollOver();
  
  //! Handle button press
  void handleButtonPress();

  //! Handle button release
  void handleButtonRelease();

private:

  // The default texture
  Texture d_default_texture;

  // The button scroll over texture
  Texture d_button_scroll_over_texture;

  // The button press texture
  Texture d_button_press_texture;

  // The current texture
  Texture* d_current_texture;

  // The bool that stores whether the game has started
  bool d_game_started;
};

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "StartButton_def.hpp"

//---------------------------------------------------------------------------//

#endif // end START_BUTTON_HPP

//---------------------------------------------------------------------------//
// end StartButton.hpp
//---------------------------------------------------------------------------//
