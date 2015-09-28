//---------------------------------------------------------------------------//
//!
//! \file   Window.hpp
//! \author Alex Robinson
//! \brief  The window wrapper class definition
//!
//---------------------------------------------------------------------------//

#ifndef GDEV_WINDOW_HPP
#define GDEV_WINDOW_HPP

// Std Lib Includes
#include <string>
#include <stdexcept>
#include <memory>
#include <vector>

// Boost Includes
#include <boost/core/noncopyable.hpp>

// SDL Includes
#include <SDL2/SDL.h>

// GDev Includes
#include "Surface.hpp"
#include "Renderer.hpp"

namespace GDev{

//! The window exception class
class WindowException : public std::runtime_error
{
public:
  WindowException( const std::string& message )
    : std::runtime_error( message )
  { /* ... */ }

  ~WindowException() throw()
  { /* ... */ }
};

/*! The window wrapper class
 * \details The wrapper class does not allow copy construction or assignment.
 * If multiple "copies" are needed, use a smart pointer class.
 */
class Window : private boost::noncopyable
{

public:

  //! The exception class
  typedef WindowException ExceptionType;

  //! Constructor
  Window( const std::string& window_title,
	  const int x_position,
	  const int y_position,
	  const int width,
	  const int height,
	  const Uint32 window_flags = SDL_WINDOW_SHOWN );

  //! Destructor
  ~Window();

  //! Get the window id
  Uint32 getID() const;

  //! Get the window title
  std::string getTitle() const;

  //! Get the window surface
  const Surface& getSurface() const;

  //! Get the window surface
  Surface& getSurface();

  //! Get the width of the window
  int getWidth() const;

  //! Get the max width of the window
  int getMaxWidth() const;

  //! Get the min width of the window
  int getMinWidth() const;

  //! Get the height of the window
  int getHeight() const;

  //! Get the max height of the window
  int getMaxHeight() const;

  //! Get the min height of the window
  int getMinHeight() const;

  //! Set the size of the window
  void setSize( const int width, const int height );

  //! Get the window x position
  int getXPosition() const;

  //! Get the window y position
  int getYPosition() const;

  //! Set the window position
  void setPosition( const int x_position, const int y_position );

  //! Get the window brightness
  float getBrightness() const;

  //! Set the window brightness
  void setBrightness( const float brightness );

  //! Get the index of the display associated with a window
  int getDisplayIndex() const;

  //! Get the window display mode
  void getDisplayMode( SDL_DisplayMode& mode ) const;

  //! Set the window display mode
  void setDisplayMode( const SDL_DisplayMode& mode );

  //! Get the window flags
  Uint32 getFlags() const;

  //! Get the gamma ramp for the display that owns the window
  void getGammaRamp( Uint16& red, Uint16& green, Uint16& blue ) const;

  //! Set the gamma ramp for the display that owns the window
  void setGammaRamp( const Uint16 red,
		     const Uint16 green,
		     const Uint16 blue );

  //! Get the window pixel format
  Uint32 getPixelFormat() const;

  //! Get the raw window pointer (potentially dangerous)
  const SDL_Window* getRawWindowPtr() const;

  //! Get the raw window pointer (potentially dangerous
  SDL_Window* getRawWindowPtr();

  //! Set the window icon
  void setIcon( Surface& icon_surface );

  //! Hide the window
  void hide();

  //! Show the window
  void show();

  //! Raise the window above the other windows
  void raise();

  //! Maximize the window
  void maximize();

  //! Minimize the window
  void minimize();

  //! Restore the window (used after a maximize or a minimize)
  void restore();

  //! Set border
  void setBorder();

  //! Remove border
  void removeBorder();
  
  //! Confine mouse to window (grabbed input)
  void confineMouseToWindow();

  //! Free mouse from window (grabbed input)
  void freeMouseFromWindow();

  //! Check if the mouse is confined to a window (grabbed input)
  bool isMouseConfinedToWindow() const;

  //! Update the window surface (copy window surface to screen)
  void updateWindowSurface();

  //! Update the screen (copy areas of the window surface to the screen)
  void updateWindowSurface( const std::vector<SDL_Rect>& update_areas );

private:
 
  // Free the window
  void free();

  // Do not allow default construction
  Window();

  // The SDL window 
  SDL_Window* d_window;

  // The window surface wrapper
  std::shared_ptr<Surface> d_window_surface_wrapper;
};

} // end GDev namespace

#endif // end GDEV_WINDOW_HPP

//---------------------------------------------------------------------------//
// end Window.hpp
//---------------------------------------------------------------------------//
