//---------------------------------------------------------------------------//
//!
//! \file   tstGeneralButton.hpp
//! \author Alex Robinson
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
#include "GeneralButton.hpp"
#include "WindowRenderer.hpp"
#include "GlobalSDLSession.hpp"
#include "Rectangle.hpp"
#include "Ellipse.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

// The test window
std::shared_ptr<GDev::Window> test_window;

// The test window renderer
std::shared_ptr<GDev::WindowRenderer> test_window_renderer;

// The test font filename
std::string test_font_filename;

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
      test_window.reset( new GDev::Window( "test", 
					     SDL_WINDOWPOS_CENTERED, 
					     SDL_WINDOWPOS_CENTERED, 
					     800, 
					     600, 
					     SDL_WINDOW_OPENGL ) );
      
      test_window_renderer.reset( new GDev::WindowRenderer( test_window ) );
      
      SDL_Color white = {0xFF,0xFF,0xFF,0xFF};
      test_window_renderer->setDrawColor( white );
      test_window_renderer->clear();
      test_window_renderer->present();
    }

    if( boost::unit_test::framework::master_test_suite().argc > 1 )
    {
      test_font_filename = 
	boost::unit_test::framework::master_test_suite().argv[1];
    }
    else
    {
      std::cerr << "Error: The image and font filename must be specified (arg 1)"
		<< std::endl;

      exit(1);
    }
  }

private:

  GDev::GlobalSDLSession session;
};

BOOST_GLOBAL_FIXTURE( GlobalInitFixture );

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the general button can be constructed
BOOST_AUTO_TEST_CASE( constructor )
{
  std::string message( "Test Button" );
  GDev::Font test_font( test_font_filename, 16 );
  SDL_Color text_color = {0,0,0,0xFF};
  SDL_Color edge_color = text_color;
  SDL_Color default_background_color = {0x77,0x77,0x77,0x0F};
  SDL_Color press_background_color = {0xFF,0,0,0xFF};
  SDL_Color scroll_over_background_color = {0x80,0x80,0x90,0xFF};
  SDL_Color release_background_color = {0,0xFF,0,0xFF};

  std::shared_ptr<const GDev::Shape> button_area( new GDev::Ellipse( 20, 10, 20, 10, 2 ) );

  BOOST_CHECK_NO_THROW( GDev::GeneralButton dummy_button( 
						 test_window_renderer,
						 button_area,
						 message,
						 test_font,
						 text_color,
						 edge_color,
						 default_background_color,
						 press_background_color,
						 scroll_over_background_color,
						 release_background_color ) );
}

//---------------------------------------------------------------------------//
// Check that the general button can be rendered
BOOST_AUTO_TEST_CASE( render )
{
  SDL_Color white = {0xFF,0xFF,0xFF,0xFF};
  test_window_renderer->setDrawColor( white );
  test_window_renderer->clear();
  test_window_renderer->present();
      
  std::string message( "Test Button" );
  GDev::Font test_font( test_font_filename, 16 );
  SDL_Color text_color = {0,0,0,0xFF};
  SDL_Color edge_color = text_color;
  SDL_Color default_background_color = {0x77,0x77,0x77,0x0F};
  SDL_Color press_background_color = {0xFF,0,0,0xFF};
  SDL_Color scroll_over_background_color = {0x80,0x80,0x90,0xFF};
  SDL_Color release_background_color = {0,0xFF,0,0xFF};

  std::shared_ptr<const GDev::Shape> 
    button_area( new GDev::Ellipse( test_window->getWidth()/2, 
				    test_window->getHeight()/2,
				    100,
				    30,
				    2 ) );

  GDev::GeneralButton test_button( test_window_renderer,
				   button_area,
				   message,
				   test_font,
				   text_color,
				   edge_color,
				   default_background_color,
				   press_background_color,
				   scroll_over_background_color,
				   release_background_color );

  BOOST_CHECK_NO_THROW( test_button.render() );

  test_window_renderer->present();

  SDL_Delay(500);

  SDL_Event dummy_event;
  dummy_event.type = SDL_MOUSEMOTION;

  test_button.handleAction( dummy_event );

  BOOST_CHECK_NO_THROW( test_button.render() );
						
  test_window_renderer->present();

  SDL_Delay(500);

  dummy_event.type = SDL_MOUSEBUTTONDOWN;

  test_button.handleAction( dummy_event );

  BOOST_CHECK_NO_THROW( test_button.render() );
						
  test_window_renderer->present();

  SDL_Delay(500);

  dummy_event.type = SDL_MOUSEBUTTONUP;

  test_button.handleAction( dummy_event );

  BOOST_CHECK_NO_THROW( test_button.render() );
						
  test_window_renderer->present();

  SDL_Delay(500);

  dummy_event.type = SDL_QUIT;

  test_button.handleAction( dummy_event );

  BOOST_CHECK_NO_THROW( test_button.render() );
						
  test_window_renderer->present();

  SDL_Delay(500);
}

//---------------------------------------------------------------------------//
// end tstGeneralButton.cpp
//---------------------------------------------------------------------------//
