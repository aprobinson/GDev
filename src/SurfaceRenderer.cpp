//---------------------------------------------------------------------------//
//!
//! \file   SurfaceRenderer.cpp
//! \author Alex Robinson
//! \brief  The surface renderer wrapper class definition
//!
//---------------------------------------------------------------------------//

// GDev Includes
#include "SurfaceRenderer.hpp"
#include "ExceptionTestMacros.hpp"
#include "DBCMacros.hpp"

namespace GDev{

/*! Constructor
 * \details Do not use the window surface wrapper as it does not own the 
 * surface.
 */
SurfaceRenderer::SurfaceRenderer( const std::shared_ptr<Surface>& surface )
  : Renderer( *surface ),
    d_surface( surface )
{
  // Make sure the surface is valid
  testPrecondition( surface );
  // Make sure the surface wrapper owns the surface
  testPrecondition( surface->isLocallyOwned() );
}

// Reset the viewport to the entire target
void SurfaceRenderer::resetViewport()
{
  SDL_Rect viewport = {0, 0, d_surface->getWidth(), d_surface->getHeight()};

  this->setViewport( viewport );
}

} // end GDev namespace

//---------------------------------------------------------------------------//
// end SurfaceRenderer.cpp
//---------------------------------------------------------------------------//
