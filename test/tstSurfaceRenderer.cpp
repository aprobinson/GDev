//---------------------------------------------------------------------------//
//!
//! \file   tstSurfaceRenderer.cpp
//! \author Alex Robinson
//! \brief  Surface renderer wrapper class unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <string>
#include <memory>

// Boost Includes
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>

// GDev Includes
#include "SurfaceRenderer.hpp"
#include "GlobalSDLSession.hpp"

//---------------------------------------------------------------------------//
// Testing Structs
//---------------------------------------------------------------------------//

struct GlobalInitFixture
{
  GlobalInitFixture()
    : session()
  { /* ... */ }

private:

  GDev::GlobalSDLSession session;
};

struct SurfaceFixture
{
  SurfaceFixture()
    : test_surface( new GDev::Surface( 800, 600, SDL_PIXELFORMAT_ARGB8888 ) )
  { /* ... */ }

  // The test surface
  const std::shared_ptr<GDev::Surface> test_surface;
};

BOOST_GLOBAL_FIXTURE( GlobalInitFixture );

BOOST_FIXTURE_TEST_SUITE( SurfaceRenderer, SurfaceFixture );

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that surface renderer can be constructed
BOOST_AUTO_TEST_CASE( constructor )
{
  BOOST_CHECK_NO_THROW( GDev::SurfaceRenderer dummy_renderer( test_surface ) );
}

//---------------------------------------------------------------------------//
// Check that the name of the renderer can be returned
BOOST_AUTO_TEST_CASE( getName )
{
  GDev::SurfaceRenderer renderer( test_surface );
  
  BOOST_CHECK_EQUAL( renderer.getName(), "software" );
}

//---------------------------------------------------------------------------//
// Check that the supported flags can be returned
BOOST_AUTO_TEST_CASE( getSupportedFlags )
{
  GDev::SurfaceRenderer renderer( test_surface );

  Uint32 flags = renderer.getSupportedFlags();

  BOOST_CHECK( flags & SDL_RENDERER_SOFTWARE );
  BOOST_CHECK( flags & SDL_RENDERER_TARGETTEXTURE );
  BOOST_CHECK_EQUAL( flags, SDL_RENDERER_SOFTWARE|SDL_RENDERER_TARGETTEXTURE );
}

//---------------------------------------------------------------------------//
// Check that the valid texture formats can be returned
BOOST_AUTO_TEST_CASE( getValidTextureFormats )
{
  GDev::SurfaceRenderer renderer( test_surface );

  const std::vector<Uint32>& formats = renderer.getValidTextureFormats();
  
  BOOST_CHECK_EQUAL( formats.size(), 8 );
}

//---------------------------------------------------------------------------//
// Check if texture formats are valid
BOOST_AUTO_TEST_CASE( isValidTextureFormat )
{
  GDev::SurfaceRenderer renderer( test_surface );

  BOOST_CHECK( renderer.isValidTextureFormat( SDL_PIXELFORMAT_RGB555 ) );
  BOOST_CHECK( renderer.isValidTextureFormat( SDL_PIXELFORMAT_RGB565 ) );
  BOOST_CHECK( renderer.isValidTextureFormat( SDL_PIXELFORMAT_RGB888 ) );
  BOOST_CHECK( renderer.isValidTextureFormat( SDL_PIXELFORMAT_BGR888 ) );
  BOOST_CHECK( renderer.isValidTextureFormat( SDL_PIXELFORMAT_ARGB8888 ) );
  BOOST_CHECK( renderer.isValidTextureFormat( SDL_PIXELFORMAT_RGBA8888 ) );
  BOOST_CHECK( renderer.isValidTextureFormat( SDL_PIXELFORMAT_ABGR8888 ) );
  BOOST_CHECK( renderer.isValidTextureFormat( SDL_PIXELFORMAT_BGRA8888 ) );
}

//---------------------------------------------------------------------------//
// Check that the max texture width can be returned
BOOST_AUTO_TEST_CASE( getMaxTextureWidth )
{
  GDev::SurfaceRenderer renderer( test_surface );

  BOOST_CHECK_EQUAL( renderer.getMaxTextureWidth(), 800 );
}

//---------------------------------------------------------------------------//
// Check that the max texture height can be returned
BOOST_AUTO_TEST_CASE( getMaxTextureHeight )
{
  GDev::SurfaceRenderer renderer( test_surface );

  BOOST_CHECK_EQUAL( renderer.getMaxTextureHeight(), 600 );
}

//---------------------------------------------------------------------------//
// Check that the output size can be returned
BOOST_AUTO_TEST_CASE( getOutputSize )
{
  GDev::SurfaceRenderer renderer( test_surface );
  
  int output_width, output_height;

  BOOST_CHECK_NO_THROW( renderer.getOutputSize( output_width, output_height ));
  BOOST_CHECK_EQUAL( output_width, 800 );
  BOOST_CHECK_EQUAL( output_height, 600 );
}

//---------------------------------------------------------------------------//
// Check that the logical size of the renderer can be returned
BOOST_AUTO_TEST_CASE( get_setLogicalSize )
{
  GDev::SurfaceRenderer renderer( test_surface );

  int logical_width, logical_height;

  renderer.getLogicalSize( logical_width, logical_height );
  BOOST_CHECK_EQUAL( logical_width, 0 );
  BOOST_CHECK_EQUAL( logical_height, 0 );

  BOOST_CHECK_NO_THROW( renderer.setLogicalSize( 800, 600 ) );
  renderer.getLogicalSize( logical_width, logical_height );
  
  BOOST_CHECK_EQUAL( logical_width, 800 );
  BOOST_CHECK_EQUAL( logical_height, 600 );
}

//---------------------------------------------------------------------------//
// Check that the scale factor can be returned
BOOST_AUTO_TEST_CASE( get_setScale )
{
  GDev::SurfaceRenderer renderer( test_surface );

  float x_scale, y_scale;

  renderer.getScale( x_scale, y_scale );
  BOOST_CHECK_EQUAL( x_scale, 1.0f );
  BOOST_CHECK_EQUAL( y_scale, 1.0f );

  BOOST_CHECK_NO_THROW( renderer.setScale( 2.0, 3.0 ) );
  renderer.getScale( x_scale, y_scale );
  
  BOOST_CHECK_EQUAL( x_scale, 2.0 );
  BOOST_CHECK_EQUAL( y_scale, 3.0 );
}

//---------------------------------------------------------------------------//
// Check that the draw blend mode can be returned
BOOST_AUTO_TEST_CASE( get_setDrawBlendMode )
{
  GDev::SurfaceRenderer renderer( test_surface );

  SDL_BlendMode mode;
  BOOST_CHECK_NO_THROW( mode = renderer.getDrawBlendMode() );
  BOOST_CHECK_EQUAL( mode, SDL_BLENDMODE_NONE );

  BOOST_CHECK_NO_THROW( renderer.setDrawBlendMode( SDL_BLENDMODE_BLEND ) );
  BOOST_CHECK_NO_THROW( mode = renderer.getDrawBlendMode() );
  BOOST_CHECK_EQUAL( mode, SDL_BLENDMODE_BLEND );
}

//---------------------------------------------------------------------------//
// Check that the draw color can be returned
BOOST_AUTO_TEST_CASE( get_setDrawColor )
{
  GDev::SurfaceRenderer renderer( test_surface );

  SDL_Color color;
  BOOST_CHECK_NO_THROW( renderer.getDrawColor( color ) );
  BOOST_CHECK_EQUAL( color.r, 0 );
  BOOST_CHECK_EQUAL( color.g, 0 );
  BOOST_CHECK_EQUAL( color.b, 0 );
  BOOST_CHECK_EQUAL( color.a, 0 );

  color = {0xFF,0xFF,0xFF,0xFF};
  BOOST_CHECK_NO_THROW( renderer.setDrawColor( color ) );
  BOOST_CHECK_EQUAL( color.r, 0xFF );
  BOOST_CHECK_EQUAL( color.g, 0xFF );
  BOOST_CHECK_EQUAL( color.b, 0xFF );
  BOOST_CHECK_EQUAL( color.a, 0xFF );
}

//---------------------------------------------------------------------------//
// Check that the clip rectangle can be returned
BOOST_AUTO_TEST_CASE( get_setClipRectangle )
{
  GDev::SurfaceRenderer renderer( test_surface );

  SDL_Rect read_clip_rect;

  renderer.getClipRectangle( read_clip_rect );

  BOOST_CHECK_EQUAL( read_clip_rect.x, 0 );
  BOOST_CHECK_EQUAL( read_clip_rect.y, 0 );
  BOOST_CHECK_EQUAL( read_clip_rect.w, 0 );
  BOOST_CHECK_EQUAL( read_clip_rect.h, 0 );

  SDL_Rect clip_rect = {10, 20, 100, 200};

  BOOST_CHECK_NO_THROW( renderer.setClipRectangle( clip_rect ) );
  renderer.getClipRectangle( read_clip_rect );
  BOOST_CHECK_EQUAL( read_clip_rect.x, 10 );
  BOOST_CHECK_EQUAL( read_clip_rect.y, 20 );
  BOOST_CHECK_EQUAL( read_clip_rect.w, 100 );
  BOOST_CHECK_EQUAL( read_clip_rect.h, 200 );
}

//---------------------------------------------------------------------------//
// Check that the viewport can be returned
BOOST_AUTO_TEST_CASE( get_setViewport )
{
  GDev::SurfaceRenderer renderer( test_surface );

  SDL_Rect read_viewport;

  renderer.getViewport( read_viewport );

  BOOST_CHECK_EQUAL( read_viewport.x, 0 );
  BOOST_CHECK_EQUAL( read_viewport.y, 0 );
  BOOST_CHECK_EQUAL( read_viewport.w, 800 );
  BOOST_CHECK_EQUAL( read_viewport.h, 600 );
}

BOOST_AUTO_TEST_SUITE_END()

//---------------------------------------------------------------------------//
// end tstSurfaceRenderer.cpp
//---------------------------------------------------------------------------//
