//---------------------------------------------------------------------------//
//!
//! \file   WindowRenderer.hpp
//! \author Alex Robinson
//! \brief  The window renderer wrapper class declaration
//!
//---------------------------------------------------------------------------//

#ifndef GDEV_WINDOW_RENDERER_HPP
#define GDEV_WINDOW_RENDERER_HPP

// Std Lib Includes
#include <memory>

// Boost Includes
#include <boost/core/noncopyable.hpp>

// SDL Includes
#include <SDL2/SDL.h>

// GDev Includes
#include "Renderer.hpp"
#include "Window.hpp"

namespace GDev{

/*! The window renderer wrapper class
 * \details The wrapper class does not allow copy construction or assignment.
 * If multiple "copies" are needed, use a smart pointer class. This class
 * will store a copy of the window pointer to prevent the window from being
 * closed until the renderer is deleted.
 */
class WindowRenderer : public Renderer, private boost::noncopyable
{
  
public:

  //! Constructor
  WindowRenderer( const std::shared_ptr<Window>& window,
		  const int driver_index = -1,
		  const Uint32 renderer_flags = SDL_RENDERER_ACCELERATED );

  //! Destructor
  ~WindowRenderer()
  { /* ... */ }

private:

  // Do not allow default construction
  WindowRenderer();

  // The window to render to
  std::shared_ptr<Window> d_window;
};

} // end GDev namespace

#endif // end GDEV_WINDOW_RENDERER_HPP

//---------------------------------------------------------------------------//
// end WindowRenderer.hpp
//---------------------------------------------------------------------------//
