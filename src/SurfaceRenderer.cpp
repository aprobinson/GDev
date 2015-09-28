//---------------------------------------------------------------------------//
//!
//! \file   SurfaceRenderer.cpp
//! \author Alex Robinson
//! \brief  The surface renderer wrapper class definition
//!
//---------------------------------------------------------------------------//

// GDev Includes
#include "WindowRenderer.hpp"
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

} // end GDev namespace

//---------------------------------------------------------------------------//
// end SurfaceRenderer.cpp
//---------------------------------------------------------------------------//
