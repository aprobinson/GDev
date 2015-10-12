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
#include "SurfaceRenderer.hpp"
#include "WindowRenderer.hpp"
#include "GlobalSDLSession.hpp"

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
  }

private:

  GDev::GlobalSDLSession session;
};

BOOST_GLOBAL_FIXTURE( GlobalInitFixture );

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the target texture can be constructed
BOOST_AUTO_TEST_CASE( constructor_basic_surface )
{
  BOOST_CHECK_NO_THROW( GDev::TargetTexture dummy_texture( test_surface_renderer ) );
}

//---------------------------------------------------------------------------//
// Check that the target texture can be constructed
BOOST_AUTO_TEST_CASE( constructor_basic_window )
{
  BOOST_CHECK_NO_THROW( GDev::TargetTexture dummy_texture( test_window_renderer ) );
}

//---------------------------------------------------------------------------//
// Check that the target texture can be constructed
BOOST_AUTO_TEST_CASE( constructor_surface )
{
  BOOST_CHECK_NO_THROW( GDev::TargetTexture dummy_texture( 
						 test_surface_renderer,
						 test_surface->getWidth(),
						 test_surface->getHeight() ) );
}

//---------------------------------------------------------------------------//
// Check that the target texture can be constructed
BOOST_AUTO_TEST_CASE( constructor_window )
{
  BOOST_CHECK_NO_THROW( GDev::TargetTexture dummy_texture( 
						 test_window_renderer,
						 test_window->getWidth(),
						 test_window->getHeight() ) );
}

//---------------------------------------------------------------------------//
// Check that the width of the texture can be returned
BOOST_AUTO_TEST_CASE( getWidth_surface )
{
  GDev::TargetTexture basic_texture( test_surface_renderer );

  BOOST_CHECK_EQUAL( basic_texture.getWidth(), test_surface->getWidth() );
  
  GDev::TargetTexture texture( test_surface_renderer, 
			       test_surface->getWidth(),
			       test_surface->getHeight() );

  BOOST_CHECK_EQUAL( texture.getWidth(), 800 );
}

//---------------------------------------------------------------------------//
// Check that the width of the texture can be returned
BOOST_AUTO_TEST_CASE( getWidth_window )
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
BOOST_AUTO_TEST_CASE( getHeight_surface )
{
  GDev::TargetTexture basic_texture( test_surface_renderer );
  
  BOOST_CHECK_EQUAL( basic_texture.getHeight(), test_surface->getHeight() );
  
  GDev::TargetTexture texture( test_surface_renderer,
			       test_surface->getWidth(),
			       test_surface->getHeight() );

  BOOST_CHECK_EQUAL( texture.getHeight(), 600 );
}

//---------------------------------------------------------------------------//
// Check that the height of the texture can be returned
BOOST_AUTO_TEST_CASE( getHeight_window )
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
BOOST_AUTO_TEST_CASE( get_setAlphaMod_surface )
{
  GDev::TargetTexture texture( test_surface_renderer );

  Uint8 alpha_mod;

  BOOST_CHECK_NO_THROW( alpha_mod = texture.getAlphaMod() );
  BOOST_CHECK_EQUAL( alpha_mod, 0xFF );

  BOOST_CHECK_NO_THROW( texture.setAlphaMod( 0 ) );
  BOOST_CHECK_NO_THROW( alpha_mod = texture.getAlphaMod() );
  BOOST_CHECK_EQUAL( alpha_mod, 0 );
}

//---------------------------------------------------------------------------//
// Check that the alpha modulation can be returned
BOOST_AUTO_TEST_CASE( get_setAlphaMod_window )
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
BOOST_AUTO_TEST_CASE( get_setColorMod_surface )
{
  GDev::TargetTexture texture( test_surface_renderer );

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
// Check that the color modulation can be returned
BOOST_AUTO_TEST_CASE( get_setColorMod_window )
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
BOOST_AUTO_TEST_CASE( get_setBlendMode_surface )
{
  GDev::TargetTexture texture( test_surface_renderer );

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
// Check that the blend mode can be returned
BOOST_AUTO_TEST_CASE( get_setBlendMode_window )
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
BOOST_AUTO_TEST_CASE( getFormat_surface )
{
  GDev::TargetTexture texture( test_surface_renderer );

  Uint32 format = texture.getFormat();

  BOOST_CHECK( format != SDL_PIXELFORMAT_UNKNOWN );
}

//---------------------------------------------------------------------------//
// Check that the format can be returned
BOOST_AUTO_TEST_CASE( getFormat_window )
{
  GDev::TargetTexture texture( test_window_renderer );

  Uint32 format = texture.getFormat();

  BOOST_CHECK( format != SDL_PIXELFORMAT_UNKNOWN );
}

//---------------------------------------------------------------------------//
// Check that the access pattern can be returned
BOOST_AUTO_TEST_CASE( getAccessPattern_surface )
{
  GDev::TargetTexture texture( test_surface_renderer );

  BOOST_CHECK_EQUAL( texture.getAccessPattern(), SDL_TEXTUREACCESS_TARGET );
}

//---------------------------------------------------------------------------//
// Check that the access pattern can be returned
BOOST_AUTO_TEST_CASE( getAccessPattern_window )
{
  GDev::TargetTexture texture( test_window_renderer );

  BOOST_CHECK_EQUAL( texture.getAccessPattern(), SDL_TEXTUREACCESS_TARGET );
}

//---------------------------------------------------------------------------//
// Check that the raw texture pointer can be returned
BOOST_AUTO_TEST_CASE( getRawTexturePtr_surface )
{
  GDev::TargetTexture texture( test_surface_renderer );

  BOOST_CHECK( texture.getRawTexturePtr() != NULL );

  const GDev::TargetTexture const_texture( test_surface_renderer );

  BOOST_CHECK( const_texture.getRawTexturePtr() != NULL );
}

//---------------------------------------------------------------------------//
// Check that the raw texture pointer can be returned
BOOST_AUTO_TEST_CASE( getRawTexturePtr_window )
{
  GDev::TargetTexture texture( test_window_renderer );

  BOOST_CHECK( texture.getRawTexturePtr() != NULL );

  const GDev::TargetTexture const_texture( test_window_renderer );

  BOOST_CHECK( const_texture.getRawTexturePtr() != NULL );
}

//---------------------------------------------------------------------------//
// Check if the texture can be set as the rendering target
BOOST_AUTO_TEST_CASE( setAsRenderTarget_surface )
{
  GDev::TargetTexture texture( test_surface_renderer );

  BOOST_CHECK( !texture.isRenderTarget() );
  BOOST_CHECK( test_surface_renderer->isCurrentTargetDefault() );

  BOOST_CHECK_NO_THROW( texture.setAsRenderTarget() );

  BOOST_CHECK( texture.isRenderTarget() );
  BOOST_CHECK( !test_surface_renderer->isCurrentTargetDefault() );

  BOOST_CHECK_NO_THROW( texture.unsetAsRenderTarget() );

  BOOST_CHECK( !texture.isRenderTarget() );
  BOOST_CHECK( test_surface_renderer->isCurrentTargetDefault() );
}

//---------------------------------------------------------------------------//
// Check if the texture can be set as the rendering target
BOOST_AUTO_TEST_CASE( setAsRenderTarget_window )
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
BOOST_AUTO_TEST_CASE( render_basic_surface )
{
  GDev::TargetTexture texture( test_surface_renderer );

  BOOST_CHECK_NO_THROW( texture.render() );

  // Set the texture as the target
  texture.setAsRenderTarget();

  // Clear the texture
  SDL_Color white = {0xFF,0xFF,0xFF,0xFF};
  test_surface_renderer->setDrawColor( white );
  test_surface_renderer->clear();

  // Draw a line on the texture
  SDL_Color red = {0xFF,0,0,0xFF};
  test_surface_renderer->setDrawColor( red );
  test_surface_renderer->drawLine( texture.getWidth()/2,
			   0,
			   texture.getWidth()/2,
			   texture.getHeight() );
  test_surface_renderer->present();

  // Set the surface as the target
  texture.unsetAsRenderTarget();
  //test_surface_renderer->setCurrentTargetDefault();

  // Render the image
  BOOST_CHECK_NO_THROW( texture.render() );
  
  test_surface->exportToBMP( "test_default_target_rendered_surface.bmp" );
}

//---------------------------------------------------------------------------//
// Check that the texture can be rendered
BOOST_AUTO_TEST_CASE( render_basic_window )
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

  SDL_Delay(500);
}

//---------------------------------------------------------------------------//
// Check that the texture can be rendered
BOOST_AUTO_TEST_CASE( render_more_advanced_surface )
{
  GDev::TargetTexture texture( test_surface_renderer );

  // Set the texture as the target
  texture.setAsRenderTarget();

  // Clear the texture
  SDL_Color white = {0xFF,0xFF,0xFF,0xFF};
  test_surface_renderer->setDrawColor( white );
  test_surface_renderer->clear();

  // Draw a line on the texture
  SDL_Color red = {0xFF,0,0,0xFF};
  test_surface_renderer->setDrawColor( red );
  test_surface_renderer->drawLine( texture.getWidth()/2,
			   0,
			   texture.getWidth()/2,
			   texture.getHeight() );
  test_surface_renderer->present();

  // Set the surface as the target
  texture.unsetAsRenderTarget();
  //test_surface_renderer->setCurrentTargetDefault();

  test_surface_renderer->setDrawColor( white );
  test_surface_renderer->clear();

  // Render the image
  SDL_Rect texture_clip = {texture.getWidth()/4,
			   texture.getWidth()/4,
			   texture.getWidth()/2,
			   texture.getWidth()/2};

  SDL_Point rotation_center = {texture.getWidth()/4, 
			       texture.getWidth()/4};
  
  BOOST_CHECK_NO_THROW( texture.render( 0,
					0,
					&texture_clip,
					90,
					&rotation_center ) );
  
  test_surface->exportToBMP( "test_default_target_more_advanced_rendered_surface.bmp" );
}

//---------------------------------------------------------------------------//
// Check that the texture can be rendered
BOOST_AUTO_TEST_CASE( render_more_advanced_window )
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

  test_window_renderer->setDrawColor( white );
  test_window_renderer->clear();
  
  // Render the image
  SDL_Rect texture_clip = {texture.getWidth()/4,
			   texture.getWidth()/4,
			   texture.getWidth()/2,
			   texture.getWidth()/2};

  SDL_Point rotation_center = {texture.getWidth()/4, 
			       texture.getWidth()/4};
  
  BOOST_CHECK_NO_THROW( texture.render( 0,
					0,
					&texture_clip,
					90,
					&rotation_center ) );
  
  test_window_renderer->present();

  SDL_Delay(500);
}

//---------------------------------------------------------------------------//
// Check that the texture can be rendered
BOOST_AUTO_TEST_CASE( render_advanced_surface )
{
  GDev::TargetTexture texture( test_surface_renderer );

  // Set the texture as the target
  texture.setAsRenderTarget();

  // Clear the texture
  SDL_Color white = {0xFF,0xFF,0xFF,0xFF};
  test_surface_renderer->setDrawColor( white );
  test_surface_renderer->clear();

  // Draw a line on the texture
  SDL_Color red = {0xFF,0,0,0xFF};
  test_surface_renderer->setDrawColor( red );
  test_surface_renderer->drawLine( texture.getWidth()/2,
			   0,
			   texture.getWidth()/2,
			   texture.getHeight() );
  test_surface_renderer->present();

  // Set the surface as the target
  texture.unsetAsRenderTarget();
  //test_surface_renderer->setCurrentTargetDefault();

  test_surface_renderer->setDrawColor( white );
  test_surface_renderer->clear();

  // Render the image
  SDL_Rect texture_clip = {texture.getWidth()/4,
			   texture.getWidth()/4,
			   texture.getWidth()/2,
			   texture.getWidth()/2};
  SDL_Rect target_clip = {0,0,texture.getWidth(),texture.getHeight()};
  
  
  BOOST_CHECK_NO_THROW( texture.render( &target_clip, &texture_clip, 45.0 ) );
  
  test_surface->exportToBMP( "test_default_target_advanced_rendered_surface.bmp" );
}

//---------------------------------------------------------------------------//
// Check that the texture can be rendered
BOOST_AUTO_TEST_CASE( render_advanced_window )
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

  test_window_renderer->setDrawColor( white );
  test_window_renderer->clear();
  
  // Render the image
  SDL_Rect texture_clip = {texture.getWidth()/4,
			   texture.getWidth()/4,
			   texture.getWidth()/2,
			   texture.getWidth()/2};
  SDL_Rect target_clip = {0,0,texture.getWidth(),texture.getHeight()};
  
  BOOST_CHECK_NO_THROW( texture.render( &target_clip, &texture_clip, 45.0 ) );
  
  test_window_renderer->present();

  SDL_Delay(500);
}

//---------------------------------------------------------------------------//
// end tstTargetTexture.cpp
//---------------------------------------------------------------------------//
