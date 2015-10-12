//---------------------------------------------------------------------------//
//!
//! \file   tstWindowRenderer.cpp
//! \author Sean Robinson
//! \brief  Window renderer wrapper class unit tests.
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
#include "WindowRenderer.hpp"
#include "GlobalSDLSession.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<GDev::Window> test_window;

//---------------------------------------------------------------------------//
// Testing Structs
//---------------------------------------------------------------------------//

struct GlobalInitFixture
{
  GlobalInitFixture()
    : session()
  {
    if( !test_window )
    {
      test_window.reset( new GDev::Window( "test", 0, 0, 800, 600, SDL_WINDOW_OPENGL ) );
    }
  }

private:

  GDev::GlobalSDLSession session;
};

BOOST_GLOBAL_FIXTURE( GlobalInitFixture );

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that surface renderer can be constructed
BOOST_AUTO_TEST_CASE( constructor )
{
  BOOST_CHECK_NO_THROW( GDev::WindowRenderer dummy_renderer( test_window ));
}

//---------------------------------------------------------------------------//
// Check that the name of the renderer can be returned
BOOST_AUTO_TEST_CASE( getName )
{
  GDev::WindowRenderer renderer( test_window );
  
  BOOST_CHECK_EQUAL( renderer.getName(), "opengl" );
}

//---------------------------------------------------------------------------//
// Check that the supported flags can be returned
BOOST_AUTO_TEST_CASE( getSupportedFlags )
{
  GDev::WindowRenderer renderer( test_window );

  Uint32 flags = renderer.getSupportedFlags();
  BOOST_CHECK( flags & SDL_RENDERER_ACCELERATED );
  BOOST_CHECK( flags & SDL_RENDERER_TARGETTEXTURE );
  BOOST_CHECK_EQUAL( flags, SDL_RENDERER_ACCELERATED|SDL_RENDERER_TARGETTEXTURE );
}

//---------------------------------------------------------------------------//
// Check that the valid texture formats can be returned
BOOST_AUTO_TEST_CASE( getValidTextureFormats )
{
  GDev::WindowRenderer renderer( test_window );

  const std::vector<Uint32>& formats = renderer.getValidTextureFormats();
  
  BOOST_CHECK_EQUAL( formats.size(), 3 );
}

//---------------------------------------------------------------------------//
// Check if texture formats are valid
BOOST_AUTO_TEST_CASE( isValidTextureFormat )
{
  GDev::WindowRenderer renderer( test_window );

  BOOST_CHECK( renderer.isValidTextureFormat( SDL_PIXELFORMAT_ARGB8888 ));
  BOOST_CHECK( renderer.isValidTextureFormat( SDL_PIXELFORMAT_YV12 ));
  BOOST_CHECK( renderer.isValidTextureFormat( SDL_PIXELFORMAT_IYUV ));
}

//---------------------------------------------------------------------------//
// Check that the max texture width can be returned
BOOST_AUTO_TEST_CASE( getMaxTextureWidth )
{
  GDev::WindowRenderer renderer( test_window );

  BOOST_CHECK( renderer.getMaxTextureWidth() > 0 );
}

//---------------------------------------------------------------------------//
// Check that the max texture height can be returned
BOOST_AUTO_TEST_CASE( getMaxTextureHeight )
{
  GDev::WindowRenderer renderer( test_window );

  BOOST_CHECK( renderer.getMaxTextureHeight() > 0 );
}

//---------------------------------------------------------------------------//
// Check that the output size can be returned
BOOST_AUTO_TEST_CASE( getOutputSize )
{
  GDev::WindowRenderer renderer( test_window );
  
  int output_width, output_height;

  BOOST_CHECK_NO_THROW( renderer.getOutputSize( output_width, output_height ));
  BOOST_CHECK_EQUAL( output_width, 800 );
  BOOST_CHECK_EQUAL( output_height, 600 );
}

//---------------------------------------------------------------------------//
// Check that the logical size of the renderer can be returned
BOOST_AUTO_TEST_CASE( get_setLogicalSize )
{
  GDev::WindowRenderer renderer( test_window );

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
  GDev::WindowRenderer renderer( test_window );

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
  GDev::WindowRenderer renderer( test_window );

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
  GDev::WindowRenderer renderer( test_window );

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
  GDev::WindowRenderer renderer( test_window );

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
  GDev::WindowRenderer renderer( test_window );

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
  GDev::WindowRenderer renderer( test_window );

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
  // Using different window because of bug in window indicing
  std::shared_ptr<GDev::Window> window(new GDev::Window("test", 0, 0, 800, 600, SDL_WINDOW_OPENGL));

  GDev::WindowRenderer renderer( window );

  BOOST_CHECK( renderer.getRawRendererPtr() != NULL );

  const GDev::WindowRenderer const_renderer( test_window );

  BOOST_CHECK( const_renderer.getRawRendererPtr() != NULL );
}

//---------------------------------------------------------------------------//
// Check that the current rendering target is the default target
BOOST_AUTO_TEST_CASE( isCurrentTargetDefault )
{
  GDev::WindowRenderer renderer( test_window );

  BOOST_CHECK( renderer.isCurrentTargetDefault() );
}

//---------------------------------------------------------------------------//
// Check that non-default targets are supported
BOOST_AUTO_TEST_CASE( isNonDefaultTargetSupported )
{
  GDev::WindowRenderer renderer( test_window );
  
  BOOST_CHECK( renderer.isNonDefaultTargetSupported() );
}

//---------------------------------------------------------------------------//
// Check that the current target can be set to the default target
BOOST_AUTO_TEST_CASE( setCurrentTargetDefault )
{
  GDev::WindowRenderer renderer( test_window );

  BOOST_CHECK_NO_THROW( renderer.setCurrentTargetDefault() );
  BOOST_CHECK( renderer.isCurrentTargetDefault() );
}

//---------------------------------------------------------------------------//
// Check that the current target can be cleared
BOOST_AUTO_TEST_CASE( clearCurrentTarget )
{
  GDev::WindowRenderer renderer( test_window );

  SDL_Color red = {0xFF,0,0,0xFF};

  renderer.setDrawColor( red );

  BOOST_CHECK_NO_THROW( renderer.clear() );

  renderer.present();

  //test_window->updateWindowSurface();

  SDL_Delay(500);

  //test_window->getSurface().exportToBMP( "test_cleared_window_surface.bmp" );
}

//---------------------------------------------------------------------------//
// Check that a line can be drawn on the current target
BOOST_AUTO_TEST_CASE( drawLine )
{
  GDev::WindowRenderer renderer( test_window );
  
  SDL_Color white = {0xFF,0xFF,0xFF,0xFF};

  renderer.setDrawColor( white );

  renderer.clear();

  SDL_Color red = {0xFF,0,0,0xFF};

  renderer.setDrawColor( red );

  BOOST_CHECK_NO_THROW( renderer.drawLine( 0, 
					   test_window->getHeight()/2,
					   test_window->getWidth(),
					   test_window->getHeight()/2 ) );

  renderer.present();

  SDL_Delay(500);
}

//---------------------------------------------------------------------------//
// Check that lines can be drawn on the current target
BOOST_AUTO_TEST_CASE( drawLines )
{
  GDev::WindowRenderer renderer( test_window );

  SDL_Color white = {0xFF,0xFF,0xFF,0xFF};

  renderer.setDrawColor( white );

  renderer.clear();

  std::vector<SDL_Point> points( 4 );
  points[0].x = 0;
  points[0].y = test_window->getHeight()/2;
  
  points[1].x = test_window->getWidth();
  points[1].y = test_window->getHeight()/2;

  points[2].x = test_window->getWidth()/2;
  points[2].y = test_window->getHeight();

  points[3] = points[0];

  SDL_Color green = {0,0xFF,0,0xFF};

  renderer.setDrawColor( green );

  BOOST_CHECK_NO_THROW( renderer.drawLines( points ) );

  renderer.present();

  SDL_Delay(500);
}

//---------------------------------------------------------------------------//
// Check that rectangles can be drawn on the current target
BOOST_AUTO_TEST_CASE( drawRectangle )
{
  GDev::WindowRenderer renderer( test_window );

  SDL_Color white = {0xFF,0xFF,0xFF,0xFF};

  renderer.setDrawColor( white );

  renderer.clear();

  SDL_Rect rect = {0,0,test_window->getWidth()/2,test_window->getHeight()/2};

  SDL_Color blue = {0,0,0xFF,0xFF};

  renderer.setDrawColor( blue );

  BOOST_CHECK_NO_THROW( renderer.drawRectangle( rect, false ) );


  rect = {test_window->getWidth()/2,
	  test_window->getHeight()/2,
	  test_window->getWidth()/2,
	  test_window->getHeight()/2};
  
  SDL_Color green = {0,0xFF,0,0xFF};

  renderer.setDrawColor( green );

  BOOST_CHECK_NO_THROW( renderer.drawRectangle( rect, true ) );

  renderer.present();
  SDL_Delay(500);
}

//---------------------------------------------------------------------------//
// Check that rectangles can be drawn on the current target
BOOST_AUTO_TEST_CASE( drawRectangles )
{
  GDev::WindowRenderer renderer( test_window );

  SDL_Color white = {0xFF,0xFF,0xFF,0xFF};

  renderer.setDrawColor( white );

  renderer.clear();
  
  std::vector<SDL_Rect> rects( 3 );
  rects[0].x = 0;
  rects[0].y = 0;
  rects[0].w = test_window->getWidth()/3;
  rects[0].h = test_window->getHeight()/2;

  rects[1].x = 2*test_window->getWidth()/3;
  rects[1].y = 0;
  rects[1].w = test_window->getWidth()/3;
  rects[1].h = test_window->getHeight()/2;

  rects[2].x = test_window->getWidth()/3;
  rects[2].y = test_window->getHeight()/2;
  rects[2].w = test_window->getWidth()/3;
  rects[2].h = test_window->getHeight()/2;

  SDL_Color red = {0xFF,0,0,0xFF};

  renderer.setDrawColor( red );

  BOOST_CHECK_NO_THROW( renderer.drawRectangles( rects, true ) );

  rects[0].x = test_window->getWidth()/3;
  rects[0].y = 0;
  rects[0].w = test_window->getWidth()/3;
  rects[0].h = test_window->getHeight()/2;

  rects[1].x = 0;
  rects[1].y = test_window->getHeight()/2;
  rects[1].w = test_window->getWidth()/3;
  rects[1].h = test_window->getHeight()/2;

  rects[2].x = 2*test_window->getWidth()/3;
  rects[2].y = test_window->getHeight()/2;
  rects[2].w = test_window->getWidth()/3;
  rects[2].h = test_window->getHeight()/2;
  
  SDL_Color blue = {0,0,0xFF,0xFF};

  renderer.setDrawColor( blue );

  BOOST_CHECK_NO_THROW( renderer.drawRectangles( rects, false ) );

  renderer.present();
  SDL_Delay(500);
}



//---------------------------------------------------------------------------//
// end tstWindowRenderer.cpp
//---------------------------------------------------------------------------//
