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
	       const SDL_Color& background_color );

  //! Destructor
  ~StartButton()
  { /* ... */ }

  //! Render the start button
  void render() const;

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

  Texture d_texture;
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
