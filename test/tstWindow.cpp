//---------------------------------------------------------------------------//
//!
//! \file   tstWindow.cpp
//! \author Sean Robinson
//! \brief  Window wrapper class unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <string>

// Boost Includes
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>

// GDev Includes
#include "Window.hpp"
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

BOOST_GLOBAL_FIXTURE( GlobalInitFixture );

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a window can be constructed
BOOST_AUTO_TEST_CASE( constructor )
{
  BOOST_CHECK_NO_THROW( GDev::Window dummy_window("test",
						  SDL_WINDOWPOS_CENTERED,
						  SDL_WINDOWPOS_CENTERED,
						  640,
						  480,
						  SDL_WINDOW_OPENGL ));
}

//---------------------------------------------------------------------------//
// Check that the window id can be retrieved
BOOST_AUTO_TEST_CASE( getId )
{
  GDev::Window window( "test",
		       SDL_WINDOWPOS_CENTERED,
		       SDL_WINDOWPOS_CENTERED,
		       640,
		       480,
		       SDL_WINDOW_OPENGL );
  BOOST_CHECK( window.getId() >= 0 );
}
//----------------------------------------------------------------------------//
// Check that the title of a window can be gotten
BOOST_AUTO_TEST_CASE( getTitle )
{
  GDev::Window window( "test",
		       SDL_WINDOWPOS_CENTERED,
		       SDL_WINDOWPOS_CENTERED,
		       640,
		       480,
		       SDL_WINDOW_OPENGL );
  BOOST_CHECK_EQUAL( "test", "test" );
}

//----------------------------------------------------------------------------//
// Check that the surface of a window can be gotten
//BOOST_AUTO_TEST_CASE( getSurface )
//{
//  GDev::Window window( "test",
//		       SDL_WINDOWPOS_CENTERED,
//		       SDL_WINDOWPOS_CENTERED,
//		       640,
//		       480,
//		       SDL_WINDOW_OPENGL );
//  GDev::Surface& surface = window.getSurface();
//  BOOST_CHECK_EQUAL( surface.getWidth(), 640 );
//  BOOST_CHECK_EQUAL( surface.getHeight(), 480 );
//
//  const GDev::Surface& surface2 = window.getSurface();
//  BOOST_CHECK_EQUAL( surface2.getWidth(), 640 );
//  BOOST_CHECK_EQUAL( surface2.getHeight(), 480 );
// }

//----------------------------------------------------------------------------//
// Check that the width of a window can be retrieved
BOOST_AUTO_TEST_CASE( getWidth )
{
  GDev::Window window( "test",
		       SDL_WINDOWPOS_CENTERED,
		       SDL_WINDOWPOS_CENTERED,
		       640,
		       480,
		       SDL_WINDOW_OPENGL );
  BOOST_CHECK_EQUAL( window.getWidth(), 640 );
}

//----------------------------------------------------------------------------//
// Check that the height of a window can be retrieved
BOOST_AUTO_TEST_CASE( getHeight )
{
  GDev::Window window( "test",
		       SDL_WINDOWPOS_CENTERED,
		       SDL_WINDOWPOS_CENTERED,
		       640,
		       480,
		       SDL_WINDOW_OPENGL );
  BOOST_CHECK_EQUAL( window.getHeight(), 480 );
}

//----------------------------------------------------------------------------//
// Check that the max size of a window can be retrieved
BOOST_AUTO_TEST_CASE( getMaxSize )
{
  GDev::Window window( "test",
		       SDL_WINDOWPOS_CENTERED,
		       SDL_WINDOWPOS_CENTERED,
		       640,
		       480,
		       SDL_WINDOW_OPENGL );
  int max_width, max_height;
  max_width = -1, max_height = -1;
  window.getMaxSize( max_width, max_height );
  BOOST_CHECK( max_width >= 0 );
  BOOST_CHECK( max_height >= 0 );
}

//----------------------------------------------------------------------------//
// Check that the min size of a window can be retrieved
BOOST_AUTO_TEST_CASE( getMinSize )
{
  GDev::Window window( "test",
		       SDL_WINDOWPOS_CENTERED,
		       SDL_WINDOWPOS_CENTERED,
		       640,
		       480,
		       SDL_WINDOW_OPENGL );

  int min_width, min_height;
  min_width = -1, min_height = -1;
  window.getMinSize( min_width, min_height );
  BOOST_CHECK( min_width >= 0 );
  BOOST_CHECK( min_height >= 0 );
}

//----------------------------------------------------------------------------//
// Check that the size of a window can be set
BOOST_AUTO_TEST_CASE( setSize )
{
  GDev::Window window( "test",
		       SDL_WINDOWPOS_CENTERED,
		       SDL_WINDOWPOS_CENTERED,
		       640,
		       480,
		       SDL_WINDOW_OPENGL );

  int width, height;
  width = 100, height = 50;
  window.setSize( 100, 50 );
  BOOST_CHECK_EQUAL( window.getWidth(), 100 );
  BOOST_CHECK_EQUAL( window.getHeight(), 50 );
}

//----------------------------------------------------------------------------//
// Check that the position of a window can be retrieved and set
BOOST_AUTO_TEST_CASE( get_set_Position )
{
  GDev::Window window( "test",
		       SDL_WINDOWPOS_CENTERED,
		       SDL_WINDOWPOS_CENTERED,
		       640,
		       480,
		       SDL_WINDOW_OPENGL );

  int x_pos, y_pos;
  window.getPosition( x_pos, y_pos );
  BOOST_CHECK( x_pos >= 0 );
  BOOST_CHECK( y_pos >= 0 );
  
  x_pos = 10, y_pos = 5;
  window.setPosition( x_pos, y_pos );
  BOOST_CHECK( x_pos = 10 );
  BOOST_CHECK( y_pos >= 5 );
}

//----------------------------------------------------------------------------//
// Check that the brightness of a window can be set and retrieved
BOOST_AUTO_TEST_CASE( get_set_Brightness )
{
  GDev::Window window( "test",
		       SDL_WINDOWPOS_CENTERED,
		       SDL_WINDOWPOS_CENTERED,
		       640,
		       480,
		       SDL_WINDOW_OPENGL );

  float brightness = 0.67;
  BOOST_CHECK_NO_THROW( window.setBrightness( brightness ));
  BOOST_CHECK_EQUAL( window.getBrightness(), brightness );
}

//----------------------------------------------------------------------------//
// Check that the display index can be gotten
BOOST_AUTO_TEST_CASE( getDisplayIndex )
{
  GDev::Window window( "test",
		       SDL_WINDOWPOS_CENTERED,
		       SDL_WINDOWPOS_CENTERED,
		       640,
		       480,
		       SDL_WINDOW_OPENGL );

  BOOST_CHECK_NO_THROW( window.getDisplayIndex() );
}

//----------------------------------------------------------------------------//
// Check that the display mode can be gotten
BOOST_AUTO_TEST_CASE( get_set_DisplayMode )
{
  GDev::Window window( "test",
		       SDL_WINDOWPOS_CENTERED,
		       SDL_WINDOWPOS_CENTERED,
		       640,
		       480,
		       SDL_WINDOW_OPENGL );

  SDL_DisplayMode mode;
  BOOST_CHECK_NO_THROW( window.setDisplayMode( NULL ));
  window.getDisplayMode( mode );
}

//----------------------------------------------------------------------------//
// Check that the display mode can be gotten
BOOST_AUTO_TEST_CASE( get_flags )
{
  GDev::Window window( "test",
		       SDL_WINDOWPOS_CENTERED,
		       SDL_WINDOWPOS_CENTERED,
		       640,
		       480,
		       SDL_WINDOW_OPENGL );

  BOOST_CHECK( window.getFlags() & SDL_WINDOW_OPENGL );
}

//----------------------------------------------------------------------------//
// Check that the window pointer can be returned
BOOST_AUTO_TEST_CASE( getRawWindowPtr )
{
  GDev::Window window( "test",
		       SDL_WINDOWPOS_CENTERED,
		       SDL_WINDOWPOS_CENTERED,
		       640,
		       480,
		       SDL_WINDOW_OPENGL );

  BOOST_CHECK( window.getRawWindowPtr() != NULL );

  const GDev::Window const_window("test",
				  SDL_WINDOWPOS_CENTERED,
				  SDL_WINDOWPOS_CENTERED,
				  640,
				  480,
				  SDL_WINDOW_OPENGL );

  BOOST_CHECK( const_window.getRawWindowPtr() != NULL );
}

//----------------------------------------------------------------------------//
// Check that a window can be hidden
BOOST_AUTO_TEST_CASE( hide )
{
}

//----------------------------------------------------------------------------//
// Check that a window can be shown
BOOST_AUTO_TEST_CASE( show )
{
}

//----------------------------------------------------------------------------//
// Check that a window can be raised
BOOST_AUTO_TEST_CASE( raise )
{
}

//----------------------------------------------------------------------------//
// Check that a window can be maximized
BOOST_AUTO_TEST_CASE( maximize )
{
}

//----------------------------------------------------------------------------//
// Check that a window can be minimized
BOOST_AUTO_TEST_CASE( minimize )
{  
}

//----------------------------------------------------------------------------//
// Check that a window can be restored
BOOST_AUTO_TEST_CASE( restore )
{
}

//----------------------------------------------------------------------------//
// Check that a window border can be set
BOOST_AUTO_TEST_CASE( setBorder )
{
}

//----------------------------------------------------------------------------//
// Check that a window border can be removed
BOOST_AUTO_TEST_CASE( removeBorder )
{
}

//----------------------------------------------------------------------------//
// Check that a mouse can be confined to a window
BOOST_AUTO_TEST_CASE( confineMouseToWindow )
{
}

//----------------------------------------------------------------------------//
// Check that a mouse can be freed from a window
BOOST_AUTO_TEST_CASE( freeMouseFromWindow )
{
}

//----------------------------------------------------------------------------//
// Check if a mouse is confined to a window
BOOST_AUTO_TEST_CASE( isMouseConfinedToWindow )
{
}

//----------------------------------------------------------------------------//
// Check that a window can be copied to the screen
//BOOST_AUTO_TEST_CASE( updateWindowSurface )
//{
//  GDev::Window window( "test",
//		       SDL_WINDOWPOS_CENTERED,
//		       SDL_WINDOWPOS_CENTERED,
//		       640,
//		       480,
//		       SDL_WINDOW_OPENGL );
//
//  BOOST_CHECK_NO_THROW( window.updateWindowSurface() ); 
//}

//----------------------------------------------------------------------------//
// Check that a specific section of a window can be copied to the screen
//BOOST_AUTO_TEST_CASE( updateWindowSurface_areas )
//{
//   GDev::Window window( "test",
//		       SDL_WINDOWPOS_CENTERED,
//		       SDL_WINDOWPOS_CENTERED,
//		       640,
//		       480,
//		       SDL_WINDOW_OPENGL );
//
//   std::vector<SDL_Rect> update_areas(2);
//   update_areas[0] = {10,20,30,40};
//   update_areas[1].x = 50;
//   update_areas[1].y = 60;
//   update_areas[1].w = 70;
//   update_areas[1].h = 80;
//
//   BOOST_CHECK_NO_THROW( window.updateWindowSurface( update_areas ));
//}

//---------------------------------------------------------------------------//
// end tstWindow.cpp
//---------------------------------------------------------------------------//
