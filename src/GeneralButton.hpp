//---------------------------------------------------------------------------//
//!
//! \file   GeneralButtion.hpp
//! \author Alex Robinson
//! \brief  The general button class declaration
//!
//---------------------------------------------------------------------------//

#ifndef GDEV_GENERAL_BUTTON_HPP
#define GDEV_GENERAL_BUTTON_HPP

// Std Lib Includes
#include <string>
#include <memory>

// GDev Includes
#include "Button.hpp"
#include "Font.hpp"
#include "WindowRenderer.hpp"
#include "Texture.hpp"

namespace GDev{

//! The general button class
class GeneralButton : public Button
{
  
public:

  //! Constructor
  GeneralButton( const std::shared_ptr<WindowRenderer>& renderer,
		 const std::shared_ptr<const Shape>& button_area,
		 const std::string& message,
		 const Font& font,
		 const SDL_Color& text_color,
		 const SDL_Color& edge_color,
		 const SDL_Color& default_background_color,
		 const SDL_Color& press_background_color,
		 const SDL_Color& scroll_over_background_color,
		 const SDL_Color& release_background_color );
		 

  //! Destructor
  ~GeneralButton()
  { /* ... */ }

  //! Render the button
  virtual void render() const;

protected:

  // Handle default
  virtual void handleDefault();
  
  //! Handle button scroll over 
  virtual void handleButtonScrollOver();

  //! Handle button press
  virtual void handleButtonPress();

  //! Handle button release
  virtual void handleButtonRelease();

  // Test if the mouse position is inside of the button
  bool isMouseInButton() const;

private:

  // Initialize texture
  static void initializeTexture( 
			       std::shared_ptr<Texture>& texture,
			       const std::shared_ptr<WindowRenderer>& renderer,
			       const std::shared_ptr<const Shape>& button_area,
			       const std::string& message,
			       const Font& font,
			       const SDL_Color& text_color,
			       const SDL_Color& edge_color,
			       const SDL_Color& background_color );

  // The button area
  std::shared_ptr<const Shape> d_area;

  // The default button texture
  std::shared_ptr<Texture> d_default_texture;

  // The scroll over button texture
  std::shared_ptr<Texture> d_scroll_over_texture;

  // The press button texture
  std::shared_ptr<Texture> d_press_texture;

  // The release button texture
  std::shared_ptr<Texture> d_release_texture;

  // The active texture
  std::shared_ptr<Texture> d_active_texture;
};

} // end GDev namespace

#endif // end GDEV_GENERAL_BUTTON_HPP

//---------------------------------------------------------------------------//
// end GeneralButton.hpp
//---------------------------------------------------------------------------//
