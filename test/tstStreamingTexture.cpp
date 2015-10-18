//---------------------------------------------------------------------------//
//!
//! \file   tstStreamingTexture.cpp
//! \author Alex Robinson
//! \brief  The streaming texture wrapper class unit tests
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
#include "StreamingTexture.hpp"
#include "SurfaceRenderer.hpp"
#include "WindowRenderer.hpp"
#include "GlobalSDLSession.hpp"
#include "Ellipse.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

// The test surface
std::shared_ptr<GDev::Surface> test_surface;

// The test window
std::shared_ptr<GDev::Window> test_window;

// The test surface renderer
std::shared_ptr<GDev::Renderer> test_surface_renderer;

// The test window renderer
std::shared_ptr<GDev::Renderer> test_window_renderer;

// The test image filename
std::string test_image_filename;

//---------------------------------------------------------------------------//
// Testing Structs
//---------------------------------------------------------------------------//

struct GlobalInitFixture
{
  GlobalInitFixture()
    : session()
  { 
    test_surface.reset( new GDev::Surface( 800, 600, SDL_PIXELFORMAT_ARGB8888 ) );
    test_window.reset( new GDev::Window( "test",
					 SDL_WINDOWPOS_CENTERED,
					 SDL_WINDOWPOS_CENTERED,
					 800,
					 600,
					 SDL_WINDOW_OPENGL ) );
    test_surface_renderer.reset( new GDev::SurfaceRenderer( test_surface ) );
    test_window_renderer.reset( new GDev::WindowRenderer( test_window ) );

    SDL_Color white = {0xFF,0xFF,0xFF,0xFF};
    test_window_renderer->setDrawColor( white );
    test_window_renderer->clear();
    test_window_renderer->present();

    if( boost::unit_test::framework::master_test_suite().argc > 1 )
    {
      test_image_filename =
	boost::unit_test::framework::master_test_suite().argv[1];
    }
    else
    {
      std::cerr << "Error: The image and font filename must be specified (arg 2)"
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
// Check that the streaming texture can be constructed
BOOST_AUTO_TEST_CASE( constructor_blank_surfrend )
{
  BOOST_CHECK_NO_THROW( GDev::StreamingTexture dummy_texture( 
						 test_surface_renderer,
						 test_surface->getWidth(),
						 test_surface->getHeight() ) );
}

//---------------------------------------------------------------------------//
// Check that the streaming texture can be constructed
BOOST_AUTO_TEST_CASE( constructor_blank_windrend )
{
  BOOST_CHECK_NO_THROW( GDev::StreamingTexture dummy_texture(
						  test_window_renderer,
						  test_window->getWidth(),
						  test_window->getHeight() ) );
}

//---------------------------------------------------------------------------//
// Check that the streaming texture can be constructed
BOOST_AUTO_TEST_CASE( constructor_surface_surfrend )
{
  GDev::Surface image_surface( test_image_filename );

  BOOST_CHECK_NO_THROW(GDev::StreamingTexture dummy_texture( 
							 test_surface_renderer,
							 image_surface ) );
}

//---------------------------------------------------------------------------//
// Check that the streaming texture can be constructed
BOOST_AUTO_TEST_CASE( constructor_surface_windrend )
{
  GDev::Surface image_surface( test_image_filename );

  BOOST_CHECK_NO_THROW( GDev::StreamingTexture dummy_texture( 
							  test_window_renderer,
							  image_surface ) );
}

//---------------------------------------------------------------------------//
// Check that the access pattern can be returned
BOOST_AUTO_TEST_CASE( getAccessPattern_surfrend )
{
  GDev::StreamingTexture texture( test_surface_renderer,
				  test_surface->getWidth(),
				  test_surface->getHeight() );

  BOOST_CHECK_EQUAL( texture.getAccessPattern(), SDL_TEXTUREACCESS_STREAMING );
}

//---------------------------------------------------------------------------//
// Check that the access pattern can be returned
BOOST_AUTO_TEST_CASE( getAccessPattern_windrend )
{
  GDev::StreamingTexture texture( test_window_renderer,
				  test_surface->getWidth(),
				  test_surface->getHeight() );

  BOOST_CHECK_EQUAL( texture.getAccessPattern(), SDL_TEXTUREACCESS_STREAMING );
}

//---------------------------------------------------------------------------//
// Check if the streaming texture is locked
BOOST_AUTO_TEST_CASE( isLocked_surfrend )
{
  GDev::StreamingTexture texture( test_surface_renderer,
				  test_surface->getWidth(),
				  test_surface->getHeight() );

  BOOST_CHECK( !texture.isLocked() );
}

//---------------------------------------------------------------------------//
// Check if the streaming texture is locked
BOOST_AUTO_TEST_CASE( isLocked_windrend )
{
  GDev::StreamingTexture texture( test_window_renderer,
				  test_surface->getWidth(),
				  test_surface->getHeight() );

  BOOST_CHECK( !texture.isLocked() );
}

//---------------------------------------------------------------------------//
// Check that the surface can be copied to the streaming texture
BOOST_AUTO_TEST_CASE( copy_surfrend )
{
  GDev::StreamingTexture texture( test_surface_renderer,
				  test_surface->getWidth(),
				  test_surface->getHeight() );
  
  GDev::Surface image_surface( test_image_filename );
  
  BOOST_CHECK_NO_THROW( texture.copy( image_surface ) );
}

//---------------------------------------------------------------------------//
// Check that the surface can be copied to the streaming texture
BOOST_AUTO_TEST_CASE( copy_windrend )
{
  GDev::StreamingTexture texture( test_window_renderer,
				  test_window->getWidth(),
				  test_window->getHeight() );

  GDev::Surface image_surface( test_image_filename );
  
  BOOST_CHECK_NO_THROW( texture.copy( image_surface ) );
}

//---------------------------------------------------------------------------//
// Check that the texture can be rendered
BOOST_AUTO_TEST_CASE( render_basic_surfrend )
{
  // Clear the surface
  SDL_Color white = {0xFF,0xFF,0xFF,0xFF};
  test_surface_renderer->setDrawColor( white );
  test_surface_renderer->clear();
  test_surface_renderer->present();

  GDev::StreamingTexture texture( test_surface_renderer,
				  test_surface->getWidth(),
				  test_surface->getHeight() );

  GDev::Surface image_surface( test_image_filename );

  texture.copy( image_surface );

  // Render the image
  BOOST_CHECK_NO_THROW( texture.render() );

  test_surface_renderer->present();

  test_surface->exportToBMP( "test_default_rendered_streaming_surface.bmp" );
}

//---------------------------------------------------------------------------//
// Check that the texture can be rendered
BOOST_AUTO_TEST_CASE( render_basic_windrend )
{
  // Clear the surface
  SDL_Color white = {0xFF,0xFF,0xFF,0xFF};
  test_window_renderer->setDrawColor( white );
  test_window_renderer->clear();
  test_window_renderer->present();
  
  GDev::StreamingTexture texture( test_window_renderer,
				  test_window->getWidth(),
				  test_window->getHeight() );

  GDev::Surface image_surface( test_image_filename );

  texture.copy( image_surface );

  // Render the image
  BOOST_CHECK_NO_THROW( texture.render() );

  test_window_renderer->present();

  SDL_Delay(1000);
}

//---------------------------------------------------------------------------//
// end tstStreamingTexture.cpp
//---------------------------------------------------------------------------//
