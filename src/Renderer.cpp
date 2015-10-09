//---------------------------------------------------------------------------//
//!
//! \file   Renderer.cpp
//! \author Alex Robinson
//! \brief  The renderer wrapper class declaration
//!
//---------------------------------------------------------------------------//

// GDev Includes
#include "Renderer.hpp"
#include "ExceptionTestMacros.hpp"
#include "DBCMacros.hpp"

namespace GDev{

// Window constructor
Renderer::Renderer( Window& window,
		    const int driver_index,
		    const Uint32 renderer_flags )
  : d_renderer( SDL_CreateRenderer( window.getRawWindowPtr(), 
				    driver_index, 
				    renderer_flags ) )
{
  // Make sure the renderer was created successfully
  TEST_FOR_EXCEPTION( d_renderer == NULL,
		      ExceptionType,
		      "Error: The renderer could not be created for window "
		      << window.getId() << "! SDL_Error: " 
		      << SDL_GetError() );
}

// Surface constructor
Renderer::Renderer( Surface& surface )
  : d_renderer( SDL_CreateSoftwareRenderer( surface.getRawSurfacePtr() ) )
{
  // Make sure the renderer was created successfully
  TEST_FOR_EXCEPTION( d_renderer == NULL,
		      ExceptionType,
		      "Error: The renderer could not be created for the "
		      "surface! SDL_Error: " << SDL_GetError() );
}

// Destructor
Renderer::~Renderer()
{
  this->free();
}
  
// Get the output size of the renderer
void Renderer::getOutputSize( int& output_width, int& output_height ) const
{
  int return_value = 
    SDL_GetRendererOutputSize( const_cast<SDL_Renderer*>( d_renderer ),
			       &output_width,
			       &output_height );

  TEST_FOR_EXCEPTION( return_value != 0,
		      ExceptionType,
		      "Error: The renderer output size could not be "
		      "retrieved! SDL_Error: " << SDL_GetError() );
}

// Get the logical size of the renderer
void Renderer::getLogicalSize( int& logical_width, int& logical_height ) const
{
  SDL_RenderGetLogicalSize( const_cast<SDL_Renderer*>( d_renderer ),
			    &logical_width,
			    &logical_height );
}

// Set the logical size of the renderer
void Renderer::setLogicalSize( const unsigned logical_width,
			       const unsigned logical_height )
{
  int return_value = 
    SDL_RenderSetLogicalSize( d_renderer, logical_width, logical_height );

  TEST_FOR_EXCEPTION( return_value != 0,
		      ExceptionType,
		      "Error: The renderer logical size could not be "
		      "retrieved! SDL_Error: " << SDL_GetError() );
}

// Get the drawing scale for the current target
void Renderer::getScale( float& x_scale, float& y_scale ) const
{
  SDL_RenderGetScale( const_cast<SDL_Renderer*>( d_renderer ),
		      &x_scale,
		      &y_scale );
}

// Set the drawing scale for the current target
void Renderer::setScale( const float x_scale, const float y_scale ) const
{
  // Make sure the scale is valid
  testPrecondition( x_scale > 0.0 );
  testPrecondition( y_scale > 0.0 );

  int return_value = SDL_RenderSetScale( d_renderer, x_scale, y_scale );

  TEST_FOR_EXCEPTION( return_value != 0,
		      ExceptionType,
		      "Error: The renderer scale could not be set! "
		      "SDL_Error: " << SDL_GetError() );
}

// Get the draw blend mode
SDL_BlendMode Renderer::getDrawBlendMode() const
{
  SDL_BlendMode mode;
  
  int return_value = 
    SDL_GetRenderDrawBlendMode( const_cast<SDL_Renderer*>( d_renderer ),
				&mode );

  TEST_FOR_EXCEPTION( return_value != 0,
		      ExceptionType,
		      "Error: The renderer blend mode could not be retrieved! "
		      "SDL_Error: " << SDL_GetError() );

  return mode;
}

// Set the draw blend mode
void Renderer::setDrawBlendMode( const SDL_BlendMode blend_mode )
{
  int return_value = SDL_SetRenderDrawBlendMode( d_renderer, blend_mode );

  TEST_FOR_EXCEPTION( return_value != 0,
		      ExceptionType,
		      "Error: The renderer blend mode could not be set! "
		      "SDL_Error: " << SDL_GetError() );
}

// Get the color used for drawing operations (Rect, Line, Clear)
void Renderer::getDrawColor( SDL_Color& draw_color ) const
{
  int return_value = 
    SDL_GetRenderDrawColor( const_cast<SDL_Renderer*>( d_renderer ),
			    &draw_color.r,
			    &draw_color.g,
			    &draw_color.b,
			    &draw_color.a );

  TEST_FOR_EXCEPTION( return_value != 0,
		      ExceptionType,
		      "Error: The renderer draw color could not be retrieved! "
		      "SDL_Error: " << SDL_GetError() );
}

// Set the color used for drawing operations (Rect, Line, Clear)
void Renderer::setDrawColor( const SDL_Color& draw_color )
{
  int return_value = 
    SDL_SetRenderDrawColor( d_renderer, 
			    draw_color.r,
			    draw_color.g,
			    draw_color.b,
			    draw_color.a );

  TEST_FOR_EXCEPTION( return_value != 0,
		      ExceptionType,
		      "Error: The renderer draw color could not be set! "
		      "SDL_Error: " << SDL_GetError() );
}

// Check if clipping is enabled
// bool Renderer::isClippingEnabled() const
// {
//   return 
//     SDL_TRUE == SDL_RenderIsClipEnabled(const_cast<SDL_Renderer*>(d_renderer));
// }

// Get the clip rectangle for the current target
void Renderer::getClipRectangle( SDL_Rect& clip_rectangle ) const
{
  SDL_RenderGetClipRect( const_cast<SDL_Renderer*>( d_renderer ),
			 &clip_rectangle );
}

// Set the clip rectangle for the current target
void Renderer::setClipRectangle( const SDL_Rect& clip_rectangle )
{
  int return_value = SDL_RenderSetClipRect( d_renderer, &clip_rectangle );

  TEST_FOR_EXCEPTION( return_value != 0,
		      ExceptionType,
		      "Error: The renderer clip rectangle could not be set! "
		      "SDL_Error: " << SDL_GetError() );
}

// Get the drawing area for the current target
void Renderer::getViewport( SDL_Rect& viewport_rectangle ) const
{
  SDL_RenderGetViewport( const_cast<SDL_Renderer*>( d_renderer ),
			 &viewport_rectangle );
}

// Set the drawing area for the current target
void Renderer::setViewport( const SDL_Rect& viewport_rectangle )
{
  int return_value = SDL_RenderSetViewport( d_renderer, &viewport_rectangle );

  TEST_FOR_EXCEPTION( return_value != 0,
		      ExceptionType,
		      "Error: The renderer viewport could not be set! "
		      "SDL_Error: " << SDL_GetError() );
}

// Get the raw renderer pointer
const SDL_Renderer* Renderer::getRawRendererPtr() const
{
  return d_renderer;
}

// Get the raw renderer pointer
SDL_Renderer* Renderer::getRawRendererPtr()
{
  return d_renderer;
}

// Clear the current rendering target with the drawing color
void Renderer::clearCurrentTarget()
{
  int return_value = SDL_RenderClear( d_renderer );

  TEST_FOR_EXCEPTION( return_value != 0,
		      ExceptionType,
		      "Error: The renderer target could not be cleared! "
		      "SDL_Error: " << SDL_GetError() );
}

// Draw a line on the current rendering target
void Renderer::drawLine( const int start_x_position,
			 const int start_y_position,
			 const int end_x_position,
			 const int end_y_position )
{
  int return_value = SDL_RenderDrawLine( d_renderer,
					 start_x_position,
					 start_y_position,
					 end_x_position,
					 end_y_position );

  TEST_FOR_EXCEPTION( return_value != 0,
		      ExceptionType,
		      "Error: The line could not be drawn on the target! "
		      "SDL_Error: " << SDL_GetError() );
}

// Draw lines on the current rendering target
void Renderer::drawLines( const std::vector<SDL_Point>& end_points )
{
  // Make sure there is at least one line
  testPrecondition( end_points.size() > 1 );
  
  int return_value = SDL_RenderDrawLines( d_renderer,
					  &end_points[0],
					  end_points.size() );

  TEST_FOR_EXCEPTION( return_value != 0,
		      ExceptionType,
		      "Error: The lines could not be drawn on the target! "
		      "SDL_Error: " << SDL_GetError() );
}

// Draw a point on the current rendering target
void Renderer::drawPoint( const int x_position, const int y_position )
{
  int return_value = SDL_RenderDrawPoint( d_renderer,
					  x_position,
					  y_position );

  TEST_FOR_EXCEPTION( return_value != 0,
		      ExceptionType,
		      "Error: The point could not be drawn on the target! "
		      "SDL_Error: " << SDL_GetError() );
}

// Draw points on the current rendering target
void Renderer::drawPoints( const std::vector<SDL_Point>& points )
{
  // Make sure there is at least one point
  testPrecondition( points.size() > 0 );

  int return_value = SDL_RenderDrawPoints( d_renderer,
					   &points[0],
					   points.size() );

  TEST_FOR_EXCEPTION( return_value != 0,
		      ExceptionType,
		      "Error: The points could not be drawn on the target! "
		      "SDL_Error: " << SDL_GetError() );
}

// Draw a rectangle on the current rendering target
void Renderer::drawRectangle( const SDL_Rect& rectangle, 
			      const bool fill )
{
  int return_value;
  
  if( fill )
    return_value = SDL_RenderFillRect( d_renderer, &rectangle );
  else
    return_value = SDL_RenderDrawRect( d_renderer, &rectangle );

  TEST_FOR_EXCEPTION( return_value != 0,
		      ExceptionType,
		      "Error: The rectangle could not be drawn on the "
		      "target! SDL_Error: " << SDL_GetError() );
}

// Draw rectangles on the current rendering target
void Renderer::drawRectangles( const std::vector<SDL_Rect>& rectangles,
			       const bool fill )
{
  // Make sure there is at least one rectangle
  testPrecondition( rectangles.size() > 0 );

  int return_value;

  if( fill )
  {
    return_value = SDL_RenderFillRects( d_renderer,
					&rectangles[0],
					rectangles.size() );
  }
  else
  {
    return_value = SDL_RenderDrawRects( d_renderer,
					&rectangles[0],
					rectangles.size() );
  }

  TEST_FOR_EXCEPTION( return_value != 0,
		      ExceptionType,
		      "Error: The rectangles could not be drawn on the "
		      "target! SDL_Error: " << SDL_GetError() );
}

// Free the renderer
void Renderer::free()
{
  SDL_DestroyRenderer( d_renderer );

  d_renderer = NULL;
}

} // end GDev namespace

//---------------------------------------------------------------------------//
// end Renderer.cpp
//---------------------------------------------------------------------------//