//---------------------------------------------------------------------------//
//!
//! \file   tstStaticTexture.cpp
//! \author Alex Robinson
//! \brief  The static texture wrapper class unit tests
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
#include "StaticTexture.hpp"
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

    if( boost::unit_test::framework::master_test_suite().argc > 2 )
    {
      test_image_filename =
	boost::unit_test::framework::master_test_suite().argv[1];
      test_font_filename = 
	boost::unit_test::framework::master_test_suite().argv[2];
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
// Check that the static texture can be constructed
BOOST_AUTO_TEST_CASE( constructor_shape_surfrend )
{
  GDev::Ellipse ellipse( 100, 50, 100, 50, 2 );

  SDL_Color inside_color = {0,0xFF,0xFF};
  SDL_Color edge_color = {0,0,0};
  SDL_Color outside_color = {0xFF,0,0xFF};

  BOOST_CHECK_NO_THROW( GDev::StaticTexture dummy_texture( 
							 test_surface_renderer,
							 ellipse,
							 inside_color,
							 edge_color,
							 outside_color ) );
}

//---------------------------------------------------------------------------//
// Check that the static texture can be constructed
BOOST_AUTO_TEST_CASE( constructor_shape_windrend )
{
  GDev::Ellipse ellipse( 100, 50, 100, 50, 2 );

  SDL_Color inside_color = {0,0xFF,0xFF};
  SDL_Color edge_color = {0,0,0};
  SDL_Color outside_color = {0xFF,0,0xFF};

  BOOST_CHECK_NO_THROW( GDev::StaticTexture dummy_texture( 
							 test_window_renderer,
							 ellipse,
							 inside_color,
							 edge_color,
							 outside_color ) );
}

//---------------------------------------------------------------------------//
// Check that the static texture can be constructed
BOOST_AUTO_TEST_CASE( constructor_surface_surfrend )
{
  GDev::Surface image_surface( test_image_filename );
  
  BOOST_CHECK_NO_THROW( GDev::StaticTexture dummy_texture( test_surface_renderer,
							   image_surface ) );
}

//---------------------------------------------------------------------------//
// Check that the static texture can be constructed
BOOST_AUTO_TEST_CASE( constructor_surface_windrend )
{
  GDev::Surface image_surface( test_image_filename );
  
  BOOST_CHECK_NO_THROW( GDev::StaticTexture dummy_texture( test_window_renderer,
							   image_surface ) );
}

//---------------------------------------------------------------------------//
// Check that the static texture can be constructed
BOOST_AUTO_TEST_CASE( constructor_image_surfrend )
{
  BOOST_CHECK_NO_THROW( GDev::StaticTexture dummy_texture( test_surface_renderer,
							   test_image_filename ) );
}

//---------------------------------------------------------------------------//
// Check that the static texture can be constructed
BOOST_AUTO_TEST_CASE( constructor_image_windrend )
{
  BOOST_CHECK_NO_THROW( GDev::StaticTexture dummy_texture( test_window_renderer,
							   test_image_filename ) );
}

//---------------------------------------------------------------------------//
// Check that the static texture can be constructed
BOOST_AUTO_TEST_CASE( constructor_text_surfrend )
{
  GDev::Font test_font( test_font_filename, 16 );
  SDL_Color txt_color = {0xFF,0,0};
  BOOST_CHECK_NO_THROW( GDev::StaticTexture dummy_texture( test_surface_renderer, 
							   "Texture",
							   test_font,
							   txt_color ) );

  SDL_Color bg_color = {0,0xFF,0};
  BOOST_CHECK_NO_THROW( GDev::StaticTexture dummy_texture( test_surface_renderer,
							   "Texture",
							   test_font,
							   txt_color,
							   &bg_color ) );
							   
}

//---------------------------------------------------------------------------//
// Check that the static texture can be constructed
BOOST_AUTO_TEST_CASE( constructor_text_windrend )
{
  GDev::Font test_font( test_font_filename, 16 );
  SDL_Color txt_color = {0xFF,0,0};
  BOOST_CHECK_NO_THROW( GDev::StaticTexture dummy_texture( test_window_renderer, 
							   "Texture",
							   test_font,
							   txt_color ) );

  SDL_Color bg_color = {0,0xFF,0};
  BOOST_CHECK_NO_THROW( GDev::StaticTexture dummy_texture( test_window_renderer,
							   "Texture",
							   test_font,
							   txt_color,
							   &bg_color ) );
							   
}

//---------------------------------------------------------------------------//
// Check that the width of the texture can be returned
BOOST_AUTO_TEST_CASE( getWidth_surfrend )
{
  GDev::StaticTexture texture( test_surface_renderer, test_image_filename );

  BOOST_CHECK_EQUAL( texture.getWidth(), 800 );
}

//---------------------------------------------------------------------------//
// Check that the width of the texture can be returned
BOOST_AUTO_TEST_CASE( getWidth_windrend )
{
  GDev::StaticTexture texture( test_window_renderer, test_image_filename );

  BOOST_CHECK_EQUAL( texture.getWidth(), 800 );
}

//---------------------------------------------------------------------------//
// Check that the height of the texture can be returned
BOOST_AUTO_TEST_CASE( getHeight_surfrend )
{
  GDev::StaticTexture texture( test_surface_renderer, test_image_filename );

  BOOST_CHECK_EQUAL( texture.getHeight(), 600 );
}

//---------------------------------------------------------------------------//
// Check that the height of the texture can be returned
BOOST_AUTO_TEST_CASE( getHeight_windrend )
{
  GDev::StaticTexture texture( test_window_renderer, test_image_filename );

  BOOST_CHECK_EQUAL( texture.getHeight(), 600 );
}

//---------------------------------------------------------------------------//
// Check that the alpha modulation can be returned
BOOST_AUTO_TEST_CASE( get_setAlphaMod_surfrend )
{
  GDev::StaticTexture texture( test_surface_renderer, test_image_filename );

  Uint8 alpha_mod;

  BOOST_CHECK_NO_THROW( alpha_mod = texture.getAlphaMod() );
  BOOST_CHECK_EQUAL( alpha_mod, 0xFF );

  BOOST_CHECK_NO_THROW( texture.setAlphaMod( 0 ) );
  BOOST_CHECK_NO_THROW( alpha_mod = texture.getAlphaMod() );
  BOOST_CHECK_EQUAL( alpha_mod, 0 );
}

//---------------------------------------------------------------------------//
// Check that the alpha modulation can be returned
BOOST_AUTO_TEST_CASE( get_setAlphaMod_windrend )
{
  GDev::StaticTexture texture( test_window_renderer, test_image_filename );

  Uint8 alpha_mod;

  BOOST_CHECK_NO_THROW( alpha_mod = texture.getAlphaMod() );
  BOOST_CHECK_EQUAL( alpha_mod, 0xFF );

  BOOST_CHECK_NO_THROW( texture.setAlphaMod( 0 ) );
  BOOST_CHECK_NO_THROW( alpha_mod = texture.getAlphaMod() );
  BOOST_CHECK_EQUAL( alpha_mod, 0 );
}

//---------------------------------------------------------------------------//
// Check that the color modulation can be returned
BOOST_AUTO_TEST_CASE( get_setColorMod_surfrend )
{
  GDev::StaticTexture texture( test_surface_renderer, test_image_filename );

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
BOOST_AUTO_TEST_CASE( get_setColorMod_windrend )
{
  GDev::StaticTexture texture( test_window_renderer, test_image_filename );

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
BOOST_AUTO_TEST_CASE( get_setBlendMode_surfrend )
{
  GDev::StaticTexture texture( test_surface_renderer, test_image_filename );

  SDL_BlendMode mode;

  BOOST_CHECK_NO_THROW( mode = texture.getBlendMode() );
  BOOST_CHECK_EQUAL( mode, SDL_BLENDMODE_BLEND );
  
  BOOST_CHECK_NO_THROW( texture.setBlendMode( SDL_BLENDMODE_ADD ) );
  BOOST_CHECK_NO_THROW( mode = texture.getBlendMode() );
  BOOST_CHECK_EQUAL( mode, SDL_BLENDMODE_ADD );
  
  BOOST_CHECK_NO_THROW( texture.setBlendMode( SDL_BLENDMODE_MOD ) );
  BOOST_CHECK_NO_THROW( mode = texture.getBlendMode() );
  BOOST_CHECK_EQUAL( mode, SDL_BLENDMODE_MOD );
  
  BOOST_CHECK_NO_THROW( texture.setBlendMode( SDL_BLENDMODE_NONE ) );
  BOOST_CHECK_NO_THROW( mode = texture.getBlendMode() );
  BOOST_CHECK_EQUAL( mode, SDL_BLENDMODE_NONE );
}

//---------------------------------------------------------------------------//
// Check that the blend mode can be returned
BOOST_AUTO_TEST_CASE( get_setBlendMode_windrend )
{
  GDev::StaticTexture texture( test_window_renderer, test_image_filename );

  SDL_BlendMode mode;

  BOOST_CHECK_NO_THROW( mode = texture.getBlendMode() );
  BOOST_CHECK_EQUAL( mode, SDL_BLENDMODE_BLEND );
  
  BOOST_CHECK_NO_THROW( texture.setBlendMode( SDL_BLENDMODE_ADD ) );
  BOOST_CHECK_NO_THROW( mode = texture.getBlendMode() );
  BOOST_CHECK_EQUAL( mode, SDL_BLENDMODE_ADD );
  
  BOOST_CHECK_NO_THROW( texture.setBlendMode( SDL_BLENDMODE_MOD ) );
  BOOST_CHECK_NO_THROW( mode = texture.getBlendMode() );
  BOOST_CHECK_EQUAL( mode, SDL_BLENDMODE_MOD );
  
  BOOST_CHECK_NO_THROW( texture.setBlendMode( SDL_BLENDMODE_NONE ) );
  BOOST_CHECK_NO_THROW( mode = texture.getBlendMode() );
  BOOST_CHECK_EQUAL( mode, SDL_BLENDMODE_NONE );
}

//---------------------------------------------------------------------------//
// Check that the format can be returned
BOOST_AUTO_TEST_CASE( getFormat_surfrend )
{
  GDev::StaticTexture texture( test_surface_renderer, test_image_filename );

  Uint32 format = texture.getFormat();

  BOOST_CHECK( format != SDL_PIXELFORMAT_UNKNOWN );
}

//---------------------------------------------------------------------------//
// Check that the format can be returned
BOOST_AUTO_TEST_CASE( getFormat_windrend )
{
  GDev::StaticTexture texture( test_window_renderer, test_image_filename );

  Uint32 format = texture.getFormat();

  BOOST_CHECK( format != SDL_PIXELFORMAT_UNKNOWN );
}

//---------------------------------------------------------------------------//
// Check that the access pattern can be returned
BOOST_AUTO_TEST_CASE( getAccessPattern_surfrend )
{
  GDev::StaticTexture texture( test_surface_renderer, test_image_filename );

  BOOST_CHECK_EQUAL( texture.getAccessPattern(), SDL_TEXTUREACCESS_STATIC );
}

//---------------------------------------------------------------------------//
// Check that the access pattern can be returned
BOOST_AUTO_TEST_CASE( getAccessPattern_windrend )
{
  GDev::StaticTexture texture( test_window_renderer, test_image_filename );

  BOOST_CHECK_EQUAL( texture.getAccessPattern(), SDL_TEXTUREACCESS_STATIC );
}

//---------------------------------------------------------------------------//
// Check that the raw texture pointer can be returned
BOOST_AUTO_TEST_CASE( getRawTexturePtr_surfrend )
{
  GDev::StaticTexture texture( test_surface_renderer, test_image_filename );

  BOOST_CHECK( texture.getRawTexturePtr() != NULL );

  const GDev::StaticTexture const_texture( test_surface_renderer, test_image_filename);

  BOOST_CHECK( const_texture.getRawTexturePtr() != NULL );
}

//---------------------------------------------------------------------------//
// Check that the raw texture pointer can be returned
BOOST_AUTO_TEST_CASE( getRawTexturePtr_windrend )
{
  GDev::StaticTexture texture( test_window_renderer, test_image_filename );

  BOOST_CHECK( texture.getRawTexturePtr() != NULL );

  const GDev::StaticTexture const_texture( test_window_renderer, test_image_filename);

  BOOST_CHECK( const_texture.getRawTexturePtr() != NULL );
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

  // Load the image
  GDev::StaticTexture texture( test_surface_renderer, test_image_filename );
  
  // Render the image
  BOOST_CHECK_NO_THROW( texture.render() );

  test_surface_renderer->present();

  test_surface->exportToBMP( "test_default_rendered_surface.bmp" );
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

  // Load the image
  GDev::StaticTexture texture( test_window_renderer, test_image_filename );
  
  // Render the image
  BOOST_CHECK_NO_THROW( texture.render() );

  test_window_renderer->present();

  SDL_Delay(500);
}

//---------------------------------------------------------------------------//
// Check that the texture can be rendered
BOOST_AUTO_TEST_CASE( render_more_advanced_surfrend )
{
  // Clear the surface
  SDL_Color white = {0xFF,0xFF,0xFF,0xFF};
  test_surface_renderer->setDrawColor( white );
  test_surface_renderer->clear();
  test_surface_renderer->present();

  // Load the image
  GDev::StaticTexture texture( test_surface_renderer, test_image_filename );

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
					90.0, 
					&rotation_center ) );

  test_surface_renderer->present();

  test_surface->exportToBMP( "test_more_advanced_rendered_surface.bmp" );
}

//---------------------------------------------------------------------------//
// Check that the texture can be rendered
BOOST_AUTO_TEST_CASE( render_more_advanced_windrend )
{
  // Clear the window
  SDL_Color white = {0xFF,0xFF,0xFF,0xFF};
  test_window_renderer->setDrawColor( white );
  test_window_renderer->clear();
  test_window_renderer->present();

  // Load the image
  GDev::StaticTexture texture( test_window_renderer, test_image_filename );

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
					90.0, 
					&rotation_center ) );

  test_window_renderer->present();

  SDL_Delay(500);
}

//---------------------------------------------------------------------------//
// Check that the texture can be rendered
BOOST_AUTO_TEST_CASE( render_advanced_surfrend )
{
  // Clear the surface
  SDL_Color white = {0xFF,0xFF,0xFF,0xFF};
  test_surface_renderer->setDrawColor( white );
  test_surface_renderer->clear();
  test_surface_renderer->present();

  // Load the image
  GDev::StaticTexture texture( test_surface_renderer, test_image_filename );

  // Render the image
  SDL_Rect texture_clip = {texture.getWidth()/4,
			   texture.getWidth()/4,
			   texture.getWidth()/2,
			   texture.getWidth()/2};
  SDL_Rect target_clip = {0,0,texture.getWidth(),texture.getHeight()};
  
  BOOST_CHECK_NO_THROW( texture.render( &target_clip, &texture_clip, 45.0 ) );

  test_surface_renderer->present();

  test_surface->exportToBMP( "test_advanced_rendered_surface.bmp" );
}

//---------------------------------------------------------------------------//
// Check that the texture can be rendered
BOOST_AUTO_TEST_CASE( render_advanced_windrend )
{
  // Clear the window
  SDL_Color white = {0xFF,0xFF,0xFF,0xFF};
  test_window_renderer->setDrawColor( white );
  test_window_renderer->clear();
  test_window_renderer->present();

  // Load the image
  GDev::StaticTexture texture( test_window_renderer, test_image_filename );

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
// end tstStaticTexture.cpp
//---------------------------------------------------------------------------//
