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
#include "Rectangle.hpp"
#include "Ellipse.hpp"

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

  BOOST_CHECK( renderer.getMaxTextureWidth() > 0 );
}

//---------------------------------------------------------------------------//
// Check that the max texture height can be returned
BOOST_AUTO_TEST_CASE( getMaxTextureHeight )
{
  GDev::SurfaceRenderer renderer( test_surface );

  BOOST_CHECK( renderer.getMaxTextureHeight() > 0 );
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
// Check that the output width can be returned
BOOST_AUTO_TEST_CASE( getOutputWidth )
{
  GDev::SurfaceRenderer renderer( test_surface );
  
  int output_width;

  BOOST_CHECK_NO_THROW( output_width = renderer.getOutputWidth() );
  BOOST_CHECK_EQUAL( output_width, 800 );
}

//---------------------------------------------------------------------------//
// Check that the output height can be returned
BOOST_AUTO_TEST_CASE( getOutputHeight )
{
  GDev::SurfaceRenderer renderer( test_surface );
  
  int output_height;

  BOOST_CHECK_NO_THROW( output_height = renderer.getOutputHeight() );
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

  SDL_Rect viewport = {200,150,400,300};

  BOOST_CHECK_NO_THROW( renderer.setViewport( viewport ) );
  renderer.getViewport( read_viewport );

  BOOST_CHECK_EQUAL( read_viewport.x, 200 );
  BOOST_CHECK_EQUAL( read_viewport.y, 150 );
  BOOST_CHECK_EQUAL( read_viewport.w, 400 );
  BOOST_CHECK_EQUAL( read_viewport.h, 300 );
}

//---------------------------------------------------------------------------//
// Check that the viewport can be reset
BOOST_AUTO_TEST_CASE( resetViewport )
{
  GDev::SurfaceRenderer renderer( test_surface );

  SDL_Rect initial_viewport, read_viewport;

  renderer.getViewport( initial_viewport );

  SDL_Rect viewport = {200,150,400,300};

  BOOST_CHECK_NO_THROW( renderer.setViewport( viewport ) );
  renderer.getViewport( read_viewport );

  BOOST_CHECK( initial_viewport.x != read_viewport.x );
  BOOST_CHECK( initial_viewport.y != read_viewport.y );
  BOOST_CHECK( initial_viewport.w != read_viewport.w );
  BOOST_CHECK( initial_viewport.h != read_viewport.h );

  BOOST_CHECK_NO_THROW( renderer.resetViewport() );
  renderer.getViewport( read_viewport );

  BOOST_CHECK_EQUAL( initial_viewport.x, read_viewport.x );
  BOOST_CHECK_EQUAL( initial_viewport.y, read_viewport.y );
  BOOST_CHECK_EQUAL( initial_viewport.w, read_viewport.w );
  BOOST_CHECK_EQUAL( initial_viewport.h, read_viewport.h );
}

//---------------------------------------------------------------------------//
// Check that the raw renderer pointer can be returned
BOOST_AUTO_TEST_CASE( getRawRendererPtr )
{
  GDev::SurfaceRenderer renderer( test_surface );

  BOOST_CHECK( renderer.getRawRendererPtr() != NULL );

  const GDev::SurfaceRenderer const_renderer( test_surface );

  BOOST_CHECK( const_renderer.getRawRendererPtr() != NULL );
}

//---------------------------------------------------------------------------//
// Check that the current rendering target is the default target
BOOST_AUTO_TEST_CASE( isCurrentTargetDefault )
{
  GDev::SurfaceRenderer renderer( test_surface );

  BOOST_CHECK( renderer.isCurrentTargetDefault() );
}

//---------------------------------------------------------------------------//
// Check that non-default targets are supported
BOOST_AUTO_TEST_CASE( isNonDefaultTargetSupported )
{
  GDev::SurfaceRenderer renderer( test_surface );
  
  BOOST_CHECK( renderer.isNonDefaultTargetSupported() );
}

//---------------------------------------------------------------------------//
// Check that the current target can be set to the default target
BOOST_AUTO_TEST_CASE( setCurrentTargetDefault )
{
  GDev::SurfaceRenderer renderer( test_surface );

  BOOST_CHECK_NO_THROW( renderer.setCurrentTargetDefault() );
  BOOST_CHECK( renderer.isCurrentTargetDefault() );
}

//---------------------------------------------------------------------------//
// Check that the current target can be cleared
BOOST_AUTO_TEST_CASE( clearCurrentTarget )
{
  GDev::SurfaceRenderer renderer( test_surface );

  SDL_Color red = {0xFF,0,0,0xFF};

  renderer.setDrawColor( red );

  BOOST_CHECK_NO_THROW( renderer.clear() );

  renderer.present();

  test_surface->exportToBMP( "test_cleared_surface.bmp" );
}

//---------------------------------------------------------------------------//
// Check that a line can be drawn on the current target
BOOST_AUTO_TEST_CASE( drawLine )
{
  GDev::SurfaceRenderer renderer( test_surface );
  
  SDL_Color white = {0xFF,0xFF,0xFF,0xFF};

  renderer.setDrawColor( white );

  renderer.clear();

  SDL_Color red = {0xFF,0,0,0xFF};

  renderer.setDrawColor( red );

  BOOST_CHECK_NO_THROW( renderer.drawLine( 0, 
					   test_surface->getHeight()/2,
					   test_surface->getWidth(),
					   test_surface->getHeight()/2 ) );

  renderer.present();

  test_surface->exportToBMP( "test_line_surface.bmp" );
}

//---------------------------------------------------------------------------//
// Check that lines can be drawn on the current target
BOOST_AUTO_TEST_CASE( drawLines )
{
  GDev::SurfaceRenderer renderer( test_surface );

  SDL_Color white = {0xFF,0xFF,0xFF,0xFF};

  renderer.setDrawColor( white );

  renderer.clear();

  std::vector<SDL_Point> points( 4 );
  points[0].x = 0;
  points[0].y = test_surface->getHeight()/2;
  
  points[1].x = test_surface->getWidth();
  points[1].y = test_surface->getHeight()/2;

  points[2].x = test_surface->getWidth()/2;
  points[2].y = test_surface->getHeight();

  points[3] = points[0];

  SDL_Color green = {0,0xFF,0,0xFF};

  renderer.setDrawColor( green );

  BOOST_CHECK_NO_THROW( renderer.drawLines( points ) );

  renderer.present();

  test_surface->exportToBMP( "test_lines_surface.bmp" );
}

//---------------------------------------------------------------------------//
// Check that rectangles can be drawn on the current target
BOOST_AUTO_TEST_CASE( drawRectangle )
{
  GDev::SurfaceRenderer renderer( test_surface );

  SDL_Color white = {0xFF,0xFF,0xFF,0xFF};

  renderer.setDrawColor( white );

  renderer.clear();

  SDL_Rect rect = {0,0,test_surface->getWidth()/2,test_surface->getHeight()/2};

  SDL_Color blue = {0,0,0xFF,0xFF};

  renderer.setDrawColor( blue );

  BOOST_CHECK_NO_THROW( renderer.drawRectangle( rect, false ) );


  rect = {test_surface->getWidth()/2,
	  test_surface->getHeight()/2,
	  test_surface->getWidth()/2,
	  test_surface->getHeight()/2};
  
  SDL_Color green = {0,0xFF,0,0xFF};

  renderer.setDrawColor( green );

  BOOST_CHECK_NO_THROW( renderer.drawRectangle( rect, true ) );

  renderer.present();

  test_surface->exportToBMP( "test_rect_surface.bmp" );
}

//---------------------------------------------------------------------------//
// Check that rectangles can be drawn on the current target
BOOST_AUTO_TEST_CASE( drawRectangles )
{
  GDev::SurfaceRenderer renderer( test_surface );

  SDL_Color white = {0xFF,0xFF,0xFF,0xFF};

  renderer.setDrawColor( white );

  renderer.clear();
  
  std::vector<SDL_Rect> rects( 3 );
  rects[0].x = 0;
  rects[0].y = 0;
  rects[0].w = test_surface->getWidth()/3;
  rects[0].h = test_surface->getHeight()/2;

  rects[1].x = 2*test_surface->getWidth()/3;
  rects[1].y = 0;
  rects[1].w = test_surface->getWidth()/3;
  rects[1].h = test_surface->getHeight()/2;

  rects[2].x = test_surface->getWidth()/3;
  rects[2].y = test_surface->getHeight()/2;
  rects[2].w = test_surface->getWidth()/3;
  rects[2].h = test_surface->getHeight()/2;

  SDL_Color red = {0xFF,0,0,0xFF};

  renderer.setDrawColor( red );

  BOOST_CHECK_NO_THROW( renderer.drawRectangles( rects, true ) );

  rects[0].x = test_surface->getWidth()/3;
  rects[0].y = 0;
  rects[0].w = test_surface->getWidth()/3;
  rects[0].h = test_surface->getHeight()/2;

  rects[1].x = 0;
  rects[1].y = test_surface->getHeight()/2;
  rects[1].w = test_surface->getWidth()/3;
  rects[1].h = test_surface->getHeight()/2;

  rects[2].x = 2*test_surface->getWidth()/3;
  rects[2].y = test_surface->getHeight()/2;
  rects[2].w = test_surface->getWidth()/3;
  rects[2].h = test_surface->getHeight()/2;
  
  SDL_Color blue = {0,0,0xFF,0xFF};

  renderer.setDrawColor( blue );

  BOOST_CHECK_NO_THROW( renderer.drawRectangles( rects, false ) );

  renderer.present();

  test_surface->exportToBMP( "test_rects_surface.bmp" );
}

//---------------------------------------------------------------------------//
// Check that shapes can be drawn on the current target
BOOST_AUTO_TEST_CASE( drawShape )
{
  GDev::SurfaceRenderer renderer( test_surface );

  SDL_Color white = {0xFF,0xFF,0xFF,0xFF};

  renderer.setDrawColor( white );

  renderer.clear();

  std::shared_ptr<GDev::Shape> shape( new GDev::Rectangle(
					       0, 
					       0,
					       test_surface->getWidth()/2,
					       test_surface->getHeight()/2,
					       2 ) );

  SDL_Color blue = {0,0,0xFF,0xFF};

  renderer.setDrawColor( blue );

  BOOST_CHECK_NO_THROW( renderer.drawShape( *shape, false ) );


  shape.reset( new GDev::Rectangle( test_surface->getWidth()/2,
				    test_surface->getHeight()/2,
				    test_surface->getWidth()/2,
				    test_surface->getHeight()/2,
				    2 ) );
  
  SDL_Color green = {0,0xFF,0,0xFF};

  renderer.setDrawColor( green );

  BOOST_CHECK_NO_THROW( renderer.drawShape( *shape, true ) );

  shape.reset( new GDev::Ellipse( 3*test_surface->getWidth()/4,
				  test_surface->getHeight()/4,
				  test_surface->getWidth()/4,
				  test_surface->getHeight()/4,
				  2 ) );

  SDL_Color mixed = {0xFF,0xFF,0,0xFF};
  
  renderer.setDrawColor( mixed );

  BOOST_CHECK_NO_THROW( renderer.drawShape( *shape, false ) );

  shape.reset( new GDev::Ellipse( test_surface->getWidth()/4,
				  3*test_surface->getHeight()/4,
				  test_surface->getWidth()/4,
				  test_surface->getHeight()/4,
				  2 ) );

  mixed = {0,0xFF,0xFF,0xFF};

  renderer.setDrawColor( mixed );

  BOOST_CHECK_NO_THROW( renderer.drawShape( *shape, true ) );

  renderer.present();

  test_surface->exportToBMP( "test_shape_surface.bmp" );
}

//---------------------------------------------------------------------------//
// Check that shapes can be drawn on the current target
BOOST_AUTO_TEST_CASE( drawShapes )
{
  GDev::SurfaceRenderer renderer( test_surface );

  SDL_Color white = {0xFF,0xFF,0xFF,0xFF};

  renderer.setDrawColor( white );

  renderer.clear();

  std::vector<std::shared_ptr<const GDev::Shape> > shapes( 4 );
  shapes[0].reset( new GDev::Rectangle( 0, 
					0,
					test_surface->getWidth()/2,
					test_surface->getHeight()/2,
					1 ) );
  shapes[1].reset( new GDev::Rectangle( test_surface->getWidth()/2,
				       test_surface->getHeight()/2,
				       test_surface->getWidth()/2,
				       test_surface->getHeight()/2,
				       2 ) );
  shapes[2].reset( new GDev::Ellipse( 3*test_surface->getWidth()/4,
				      test_surface->getHeight()/4,
				      test_surface->getWidth()/4,
				      test_surface->getHeight()/4,
				      4 ) );
  shapes[3].reset( new GDev::Ellipse( test_surface->getWidth()/4,
				      3*test_surface->getHeight()/4,
				      test_surface->getWidth()/4,
				      test_surface->getHeight()/4,
				      10 ) );

  SDL_Color mixed = {0xFF,0,0xFF,0xFF};

  renderer.setDrawColor( mixed );

  BOOST_CHECK_NO_THROW( renderer.drawShapes( shapes, false ) );

  shapes[0].reset( new GDev::Rectangle( test_surface->getWidth()/8,
					test_surface->getHeight()/8,
					test_surface->getWidth()/8,
					test_surface->getHeight()/8,
					2 ) );
  shapes[1].reset( new GDev::Rectangle( 7*test_surface->getWidth()/8,
					test_surface->getHeight()/8,
					test_surface->getWidth()/8,
					test_surface->getHeight()/8,
					2 ) );
  shapes[2].reset( new GDev::Ellipse( test_surface->getWidth()/2,
				      test_surface->getHeight()/2,
				      test_surface->getWidth()/16,
				      test_surface->getWidth()/16,
				      2 ) );
  shapes[3].reset( new GDev::Ellipse( test_surface->getWidth()/2,
				      7*test_surface->getHeight()/8,
				      test_surface->getWidth()/2,
				      test_surface->getHeight()/16,
				      3 ) );

  mixed = {0x0F,0xFF,0x0F,0xFF};

  renderer.setDrawColor( mixed );

  BOOST_CHECK_NO_THROW( renderer.drawShapes( shapes, false ) );

  renderer.present();

  test_surface->exportToBMP( "test_shapes_surface.bmp" );
}

BOOST_AUTO_TEST_SUITE_END()

//---------------------------------------------------------------------------//
// end tstSurfaceRenderer.cpp
//---------------------------------------------------------------------------//
