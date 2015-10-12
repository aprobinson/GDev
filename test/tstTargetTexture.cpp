//---------------------------------------------------------------------------//
//!
//! \file   tstTargetTexture.cpp
//! \author Alex Robinson
//! \brief  The target texture wrapper class unit tests
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
#include "TargetTexture.hpp"
#include "WindowRenderer.hpp"
#include "GlobalSDLSession.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

// The test window
std::shared_ptr<GDev::Window> test_window;

// The test window renderer
std::shared_ptr<GDev::WindowRenderer> test_window_renderer;


//---------------------------------------------------------------------------//
// Testing Structs
//---------------------------------------------------------------------------//

struct GlobalInitFixture
{
  GlobalInitFixture()
    : session()
  { 
    test_window.reset( new GDev::Window( "test", 0, 0, 800, 600, SDL_WINDOW_OPENGL ) );
    test_window_renderer.reset( new GDev::WindowRenderer( test_window ) );
  }

private:

  GDev::GlobalSDLSession session;
};

BOOST_GLOBAL_FIXTURE( GlobalInitFixture );

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the target texture can be constructed
BOOST_AUTO_TEST_CASE( constructor_basic )
{
  BOOST_CHECK_NO_THROW( GDev::TargetTexture dummy_texture( test_window_renderer ) );
}

//---------------------------------------------------------------------------//
// Check that the target texture can be constructed
BOOST_AUTO_TEST_CASE( constructor )
{
  BOOST_CHECK_NO_THROW( GDev::TargetTexture dummy_texture(
						  test_window_renderer,
						  test_window->getWidth(),
						  test_window->getHeight() ) );
}

//---------------------------------------------------------------------------//
// Check that the width of the texture can be returned
BOOST_AUTO_TEST_CASE( getWidth )
{
  GDev::TargetTexture basic_texture( test_window_renderer );

  BOOST_CHECK_EQUAL( basic_texture.getWidth(), test_window->getWidth() );
  
  GDev::TargetTexture texture( test_window_renderer, 
			       test_window->getWidth(),
			       test_window->getHeight() );

  BOOST_CHECK_EQUAL( texture.getWidth(), 800 );
}

//---------------------------------------------------------------------------//
// Check that the height of the texture can be returned
BOOST_AUTO_TEST_CASE( getHeight )
{
  GDev::TargetTexture basic_texture( test_window_renderer );
  
  BOOST_CHECK_EQUAL( basic_texture.getHeight(), test_window->getHeight() );
  
  GDev::TargetTexture texture( test_window_renderer,
			       test_window->getWidth(),
			       test_window->getHeight() );

  BOOST_CHECK_EQUAL( texture.getHeight(), 600 );
}

//---------------------------------------------------------------------------//
// Check that the alpha modulation can be returned
BOOST_AUTO_TEST_CASE( get_setAlphaMod )
{
  GDev::TargetTexture texture( test_window_renderer );

  Uint8 alpha_mod;

  BOOST_CHECK_NO_THROW( alpha_mod = texture.getAlphaMod() );
  BOOST_CHECK_EQUAL( alpha_mod, 0xFF );

  BOOST_CHECK_NO_THROW( texture.setAlphaMod( 0 ) );
  BOOST_CHECK_NO_THROW( alpha_mod = texture.getAlphaMod() );
  BOOST_CHECK_EQUAL( alpha_mod, 0 );
}

//---------------------------------------------------------------------------//
// Check that the color modulation can be returned
BOOST_AUTO_TEST_CASE( get_setColorMod )
{
  GDev::TargetTexture texture( test_window_renderer );

  Uint8 red, green, blue;

  BOOST_CHECK_NO_THROW( texture.getColorMod( red, green, blue ) );
  BOOST_CHECK_EQUAL( red, 0xFF );
  BOOST_CHECK_EQUAL( green, 0xFF );
  BOOST_CHECK_EQUAL( blue, 0xFF );

  BOOST_CHECK_NO_THROW( texture.setColorMod( 0, 0, 0 ) );
  BOOST_CHECK_NO_THROW( texture.getColorMod( red, green, blue ) );
  BOOST_CHECK_EQUAL( red, 0 );
  BOOST_CHECK_EQUAL( green, 0 );
  BOOST_CHECK_EQUAL( blue, 0 );
}

//---------------------------------------------------------------------------//
// Check that the blend mode can be returned
BOOST_AUTO_TEST_CASE( get_setBlendMode )
{
  GDev::TargetTexture texture( test_window_renderer );

  SDL_BlendMode mode;

  BOOST_CHECK_NO_THROW( mode = texture.getBlendMode() );
  BOOST_CHECK_EQUAL( mode, SDL_BLENDMODE_NONE );
  
  BOOST_CHECK_NO_THROW( texture.setBlendMode( SDL_BLENDMODE_ADD ) );
  BOOST_CHECK_NO_THROW( mode = texture.getBlendMode() );
  BOOST_CHECK_EQUAL( mode, SDL_BLENDMODE_ADD );
  
  BOOST_CHECK_NO_THROW( texture.setBlendMode( SDL_BLENDMODE_MOD ) );
  BOOST_CHECK_NO_THROW( mode = texture.getBlendMode() );
  BOOST_CHECK_EQUAL( mode, SDL_BLENDMODE_MOD );
  
  BOOST_CHECK_NO_THROW( texture.setBlendMode( SDL_BLENDMODE_BLEND ) );
  BOOST_CHECK_NO_THROW( mode = texture.getBlendMode() );
  BOOST_CHECK_EQUAL( mode, SDL_BLENDMODE_BLEND );
}

//---------------------------------------------------------------------------//
// Check that the format can be returned
BOOST_AUTO_TEST_CASE( getFormat )
{
  GDev::TargetTexture texture( test_window_renderer );

  Uint32 format = texture.getFormat();

  BOOST_CHECK( format != SDL_PIXELFORMAT_UNKNOWN );
}

//---------------------------------------------------------------------------//
// Check that the access pattern can be returned
BOOST_AUTO_TEST_CASE( getAccessPattern )
{
  GDev::TargetTexture texture( test_window_renderer );

  BOOST_CHECK_EQUAL( texture.getAccessPattern(), SDL_TEXTUREACCESS_TARGET );
}

//---------------------------------------------------------------------------//
// Check that the raw texture pointer can be returned
BOOST_AUTO_TEST_CASE( getRawTexturePtr )
{
  GDev::TargetTexture texture( test_window_renderer );

  BOOST_CHECK( texture.getRawTexturePtr() != NULL );

  const GDev::TargetTexture const_texture( test_window_renderer );

  BOOST_CHECK( const_texture.getRawTexturePtr() != NULL );
}

//---------------------------------------------------------------------------//
// Check if the texture can be set as the rendering target
BOOST_AUTO_TEST_CASE( setAsRenderTarget )
{
  GDev::TargetTexture texture( test_window_renderer );

  BOOST_CHECK( !texture.isRenderTarget() );
  BOOST_CHECK( test_window_renderer->isCurrentTargetDefault() );

  BOOST_CHECK_NO_THROW( texture.setAsRenderTarget() );

  BOOST_CHECK( texture.isRenderTarget() );
  BOOST_CHECK( !test_window_renderer->isCurrentTargetDefault() );

  BOOST_CHECK_NO_THROW( texture.unsetAsRenderTarget() );

  BOOST_CHECK( !texture.isRenderTarget() );
  BOOST_CHECK( test_window_renderer->isCurrentTargetDefault() );
}

//---------------------------------------------------------------------------//
// Check that the texture can be rendered
BOOST_AUTO_TEST_CASE( render_default )
{
  GDev::TargetTexture texture( test_window_renderer );

  // Set the texture as the target
  texture.setAsRenderTarget();

  // Clear the texture
  SDL_Color white = {0xFF,0xFF,0xFF,0xFF};
  test_window_renderer->setDrawColor( white );
  test_window_renderer->clear();

  // Draw a line on the texture
  SDL_Color red = {0xFF,0,0,0xFF};
  test_window_renderer->setDrawColor( red );
  test_window_renderer->drawLine( texture.getWidth()/2,
				  0,
				  texture.getWidth()/2,
				  texture.getHeight() );
  test_window_renderer->present();

  // Set the window as the target
  texture.unsetAsRenderTarget();
  
  // Render the image
  BOOST_CHECK_NO_THROW( texture.render() );

  test_window_renderer->present();

  SDL_Delay(2000);
}

//---------------------------------------------------------------------------//
// end tstTargetTexture.cpp
//---------------------------------------------------------------------------//
