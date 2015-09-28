//---------------------------------------------------------------------------//
//!
//! \file   SurfaceRenderer.hpp
//! \author Alex Robinson
//! \brief  The surface renderer wrapper class declaration
//!
//---------------------------------------------------------------------------//

#ifndef GDEV_SURFACE_RENDERER_HPP
#define GDEV_SURFACE_RENDERER_HPP

// Std Lib Includes
#include <memory>

// Boost Includes
#include <boost/core/noncopyable.hpp>

// SDL Includes
#include <SDL2/SDL.h>

// GDev Includes
#include "Renderer.hpp"
#include "Surface.hpp"

/*! The window renderer wrapper class
 * \details The wrapper class does not allow copy construction or assignment.
 * If multiple "copies" are needed, use a smart pointer class. This class
 * will store a copy of the surface pointer to prevent the surface from being
 * deleted until the renderer is deleted.
 */
class SurfaceRenderer : public Renderer, private boost::noncopyable
{

public:

  //! Constructor
  SurfaceRenderer( const std::shared_ptr<Surface>& surface );
		   
  //! Destructor
  ~SurfaceRenderer()
  { /* ... */ }

private:

  // Do not allow default construction
  SurfaceRenderer();

  // The surface to render to
  std::shared_ptr<Surface> d_surface;  
};

#endif // end GDEV_SURFACE_RENDERER_HPP

//---------------------------------------------------------------------------//
// end SurfaceRenderer.hpp
//---------------------------------------------------------------------------//
