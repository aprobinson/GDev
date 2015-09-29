//---------------------------------------------------------------------------//
//!
//! \file   Window.cpp
//! \author Alex Robinson
//! \brief  The window wrapper class definition
//!
//---------------------------------------------------------------------------//

// GDev Includes
#include "Window.hpp"
#include "ExceptionTestMacros.hpp"
#include "DBCMacros.hpp"

namespace GDev{

// Constructor
Window::Window( const std::string& window_title,
		const int x_position,
		const int y_position,
		const int width,
		const int height,
		const Uint32 window_flags )
  : d_window( NULL ),
    d_window_surface_wrapper()
{
  // Make sure the title is valid
  testPrecondition( window_title.size() > 0 );

  d_window = SDL_CreateWindow( window_title.c_str(),
			       x_position,
			       y_position,
			       width,
			       height,
			       window_flags );

  TEST_FOR_EXCEPTION( d_window == NULL,
		      ExceptionType,
		      "Error: The window could not be created! "
		      " SDL_Error: " << SDL_GetError );

  // Create the non-owning window surface wrapper
  d_window_surface_wrapper.reset( 
			     new Surface( SDL_GetWindowSurface( d_window ) ) );
}

// Destructor
Window::~Window()
{
  this->free();
}

// Get the window id
Uint32 Window::getId() const
{
  return SDL_GetWindowID( const_cast<SDL_Window*>( d_window ) );
}

// Get the window title
std::string Window::getTitle() const
{
  return SDL_GetWindowTitle( const_cast<SDL_Window*>( d_window ) );
}

// Get the window surface
const Surface& Window::getSurface() const
{
  return *d_window_surface_wrapper;
}

// Get the window surface
Surface& Window::getSurface()
{
  return *d_window_surface_wrapper;
}

// Get the size of the window
void Window::getSize( int& width, int& height ) const
{
  SDL_GetWindowSize( const_cast<SDL_Window*>( d_window ),
		     &width,
		     &height );
}

// Get the max size of the window
void Window::getMaxSize( int& max_width, int& max_height ) const
{
  SDL_GetWindowMaximumSize( const_cast<SDL_Window*>( d_window ),
			    &max_width,
			    &max_height );
}

// Get the min size of the window
void Window::getMinSize( int& min_width, int& max_width ) const
{
  SDL_GetWindowMinimumSize( const_cast<SDL_Window*>( d_window ),
			    &min_width,
			    &max_width );
}

// Set the size of the window
void Window::setSize( const int width, const int height )
{
  SDL_SetWindowSize( d_window, width, height );
}

// Get the window position
void Window::getPosition( int& x_position, int& y_position ) const
{
  SDL_GetWindowPosition( const_cast<SDL_Window*>( d_window ),
			 &x_position,
			 &y_position );
}

// Set the window position
void Window::setPosition( const int x_position, const int y_position )
{
  SDL_SetWindowPosition( d_window, x_position, y_position );
}

// Get the window brightness
float Window::getBrightness() const
{
  return SDL_GetWindowBrightness( const_cast<SDL_Window*>( d_window ) );
}

// Set the window brightness
/*! \details The brightness must be a value between 0 and 1
 */
void Window::setBrightness( const float brightness )
{
  // Make sure the brightness is valid
  testPrecondition( brightness >= 0.0 );
  testPrecondition( brightness <= 1.0 );
  
  int return_value = SDL_SetWindowBrightness( d_window, brightness );

  TEST_FOR_EXCEPTION( return_value != 0,
		      ExceptionType,
		      "Error: The window brightness could not bet set! "
		      "SDL_Error: " << SDL_GetError() );
}

// Get the index of the display associated with a window
int Window::getDisplayIndex() const
{
  return SDL_GetWindowDisplayIndex( const_cast<SDL_Window*>( d_window ) );
}

// Get the window display mode
void Window::getDisplayMode( SDL_DisplayMode& mode ) const
{
  int return_value = 
    SDL_GetWindowDisplayMode( const_cast<SDL_Window*>( d_window ), &mode );

  TEST_FOR_EXCEPTION( return_value != 0,
		      ExceptionType,
		      "Error: The display mode could not be retrieved! "
		      "SDL_Error: " << SDL_GetError() );
}

// Set the window display mode
void Window::setDisplayMode( const SDL_DisplayMode& mode )
{
  int return_value = SDL_SetWindowDisplayMode( d_window, &mode );

  TEST_FOR_EXCEPTION( return_value != 0,
		      ExceptionType,
		      "Error: The display mode could not be set! "
		      "SDL_Error: " << SDL_GetError() );
}

// Get the window flags
Uint32 Window::getFlags() const
{
  return SDL_GetWindowFlags( const_cast<SDL_Window*>( d_window ) );
}

// Get the gamma ramp for the display that owns the window
void Window::getGammaRamp( Uint16& red, Uint16& green, Uint16& blue ) const
{
  int return_value = 
    SDL_GetWindowGammaRamp( const_cast<SDL_Window*>( d_window ),
			    &red,
			    &green,
			    &blue );

  TEST_FOR_EXCEPTION( return_value != 0,
		      ExceptionType,
		      "Error: The gamma ramp could not be retrieved! "
		      "SDL_Error: " << SDL_GetError() );
}

// Set the gamma ramp for the display that owns the window
void Window::setGammaRamp( const Uint16 red,
			   const Uint16 green,
			   const Uint16 blue )
{
  int return_value = SDL_SetWindowGammaRamp( d_window, &red, &green, &blue );

  TEST_FOR_EXCEPTION( return_value != 0,
		      ExceptionType,
		      "Error: The gamma ramp could not be set! "
		      "SDL_Error: " << SDL_GetError() );
}

// Get the window pixel format
Uint32 Window::getPixelFormat() const
{
  return SDL_GetWindowPixelFormat( const_cast<SDL_Window*>( d_window ) );
}

// Get the raw window pointer (potentially dangerous)
const SDL_Window* Window::getRawWindowPtr() const
{
  return d_window;
}

// Get the raw window pointer (potentially dangerous
SDL_Window* Window::getRawWindowPtr()
{
  return d_window;
}

// Set the window icon
void Window::setIcon( Surface& icon_surface )
{
  SDL_SetWindowIcon( d_window, icon_surface.getRawSurfacePtr() );
}

// Hide the window
void Window::hide()
{
  SDL_HideWindow( d_window );
}

// Show the window
void Window::show()
{
  SDL_ShowWindow( d_window );
}

// Raise the window above the other windows
void Window::raise()
{
  SDL_RaiseWindow( d_window );
}

// Maximize the window
void Window::maximize()
{
  SDL_MaximizeWindow( d_window );
}

// Minimize the window
void Window::minimize()
{
  SDL_MinimizeWindow( d_window );
}

// Restore the window (used after a maximize or a minimize)
void Window::restore()
{
  SDL_RestoreWindow( d_window );
}

// Set border
void Window::setBorder()
{
  SDL_SetWindowBordered( d_window, SDL_TRUE );
}

// Remove border
void Window::removeBorder()
{
  SDL_SetWindowBordered( d_window, SDL_FALSE );
}
  
// Confine mouse to window (grabbed input)
void Window::confineMouseToWindow()
{
  SDL_SetWindowGrab( d_window, SDL_TRUE );
}

// Free mouse from window (grabbed input)
void Window::freeMouseFromWindow()
{
  SDL_SetWindowGrab( d_window, SDL_FALSE );
}

// Check if the mouse is confined to a window (grabbed input)
bool Window::isMouseConfinedToWindow() const
{
  return SDL_TRUE == SDL_GetWindowGrab( const_cast<SDL_Window*>( d_window ) );
}

// Update the screen (copy window surface to screen)
void Window::updateWindowSurface()
{
  int return_value = SDL_UpdateWindowSurface( d_window );

  TEST_FOR_EXCEPTION( return_value != 0,
		      ExceptionType,
		      "Error: The window surface could not be updated! "
		      "SDL_Error: " << SDL_GetError() );
}

// Update the screen (copy areas of the window surface to the screen)
void Window::updateWindowSurface( const std::vector<SDL_Rect>& update_areas )
{
  int return_value = SDL_UpdateWindowSurfaceRects( d_window,
						   &update_areas[0],
						   update_areas.size() );

  TEST_FOR_EXCEPTION( return_value != 0,
		      ExceptionType,
		      "Error: The window surface areas could not be updated! "
		      "SDL_Error: " << SDL_GetError() );
}

// Free the window
void Window::free()
{
  d_window_surface_wrapper.reset();
  
  SDL_DestroyWindow( d_window );

  d_window = NULL;
}

} // end GDev namespace

//---------------------------------------------------------------------------//
// end Window.cpp
//---------------------------------------------------------------------------//
