//---------------------------------------------------------------------------//
//!
//! \file   WindowRenderer.cpp
//! \author Alex Robinson
//! \brief  The window renderer wrapper class definition
//!
//---------------------------------------------------------------------------//

// GDev Includes
#include "WindowRenderer.hpp"
#include "ExceptionTestMacros.hpp"
#include "DBCMacros.hpp"

namespace GDev{

// Constructor
WindowRenderer::WindowRenderer( const std::shared_ptr<Window>& window,
				const int driver_index,
				const Uint32 renderer_flags )
  : Renderer( *window, driver_index, renderer_flags ),
    d_window( window )
{
  // Make sure the window is valid
  testPrecondition( window );
}

} // end GDev namespace

//---------------------------------------------------------------------------//
// end WindowRenderer.cpp
//---------------------------------------------------------------------------//
