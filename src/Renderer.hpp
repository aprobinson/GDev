//---------------------------------------------------------------------------//
//!
//! \file   Renderer.hpp
//! \author Alex Robinson
//! \brief  The renderer wrapper class declaration
//! 
//---------------------------------------------------------------------------//

#ifndef GDEV_RENDERER_HPP
#define GDEV_RENDERER_HPP

// Std Lib Includes
#include <string>
#include <stdexcept>

// SDL Includes
#include <SDL2/SDL.h>

// GDev Includes
#include "Surface.hpp"
#include "Window.hpp"

namespace GDev{

//! The renderer exception class
class RendererException : public std::runtime_error
{
public:
  RendererException( const std::string& message )
    : std::runtime_error( message )
  { /* ... */ }

  ~RendererException() throw()
  { /* ... */ }
};

/*! The renderer wrapper class
 * \details The wrapper class does not allow copy construction or assignment.
 * If multiple "copies" are needed, use a smart pointer class.
 */
class Renderer 
{

public:

  //! The exception class
  typedef RendererException ExceptionType;

  //! Destructor
  virtual ~Renderer();
  
  //! Get the output size of the renderer
  void getOutputSize( int& output_width, int& output_height ) const;

  //! Get the logical size of the renderer
  void getLogicalSize( int& logical_width, int& logical_height ) const;

  //! Set the logical size of the renderer
  void setLogicalSize( const unsigned logical_width, 
		       const unsigned logical_height );

  //! Get the drawing scale for the current target
  void getScale( float& x_scale, float& y_scale ) const;

  //! Set the drawing scale for the current target
  void setScale( const float x_scale, const float y_scale ) const;

  //! Get the draw blend mode
  SDL_BlendMode getDrawBlendMode() const;

  //! Set the draw blend mode
  void setDrawBlendMode( const SDL_BlendMode blend_mode );

  //! Get the color used for drawing operations (Rect, Line, Clear)
  void getDrawColor( SDL_Color& draw_color ) const;

  //! Set the color used for drawing operations (Rect, Line, Clear)
  void setDrawColor( const SDL_Color& draw_color );

  //! Check if clipping is enabled
  //bool isClippingEnabled() const;

  //! Get the clip rectangle for the current target
  void getClipRectangle( SDL_Rect& clip_rectangle ) const;

  //! Set the clip rectangle for the current target
  void setClipRectangle( const SDL_Rect& clip_rectangle );

  //! Get the drawing area for the current target
  void getViewport( SDL_Rect& viewport_rectangle ) const;

  //! Set the drawing area for the current target
  void setViewport( const SDL_Rect& viewport_rectangle );

  //! Get the raw renderer pointer
  const SDL_Renderer* getRawRendererPtr() const;

  //! Get the raw renderer pointer
  SDL_Renderer* getRawRendererPtr();

  //! Clear the current rendering target with the drawing color
  void clearCurrentTarget();

  //! Draw a line on the current rendering target
  void drawLine( const int start_x_position,
		 const int start_y_position,
		 const int end_x_position,
		 const int end_y_position );

  //! Draw lines on the current rendering target
  void drawLines( const std::vector<SDL_Point>& end_points );

  //! Draw a point on the current rendering target
  void drawPoint( const int x_position, const int y_position );

  //! Draw points on the current rendering target
  void drawPoints( const std::vector<SDL_Point>& points );

  //! Draw a rectangle on the current rendering target
  void drawRectangle( const SDL_Rect& rectangle, 
		      const bool fill );

  //! Draw rectangles on the current rendering target
  void drawRectangles( const std::vector<SDL_Rect>& rectangles,
		       const bool fill );

protected:

  //! Window constructor
  Renderer( Window& window,
	    const int driver_index,
	    const Uint32 renderer_flags );

  //! Surface constructor
  Renderer( Surface& surface );

private:

  //! Free the renderer
  void free();

  //! Do not allow default construction
  Renderer();

  // The SDL renderer
  SDL_Renderer* d_renderer;
};

} // end GDev

#endif // end GDEV_RENDERER_HPP

//---------------------------------------------------------------------------//
// end Renderer.hpp
//---------------------------------------------------------------------------//