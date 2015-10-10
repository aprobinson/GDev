//---------------------------------------------------------------------------//
//!
//! \file   tstSurface.cpp
//! \author Sean Robinson
//! \brief  Surface wrapper class unit tests.
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
#include "Surface.hpp"
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

struct CommandLineArgsFixture
{
  CommandLineArgsFixture()
  { 
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

  // The image filename
  std::string test_image_filename;
  // The font filename
  std::string test_font_filename;  
};

BOOST_GLOBAL_FIXTURE( GlobalInitFixture );

BOOST_FIXTURE_TEST_SUITE( Surface, CommandLineArgsFixture )

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a blank surface can be constructed
BOOST_AUTO_TEST_CASE( constructor_blank )
{
  BOOST_CHECK_NO_THROW( GDev::Surface dummy_surface( 10, 20, SDL_PIXELFORMAT_ARGB8888 ) );
}

//---------------------------------------------------------------------------//
// Check that a surface object can be constructed
BOOST_AUTO_TEST_CASE( constructor_image )
{
  BOOST_CHECK_NO_THROW( GDev::Surface dummy_surface( test_image_filename ));
}

//---------------------------------------------------------------------------//
// Check that a surface object can be constructed
BOOST_AUTO_TEST_CASE( constructor_text )
{
  GDev::Font test_font( test_font_filename, 16 );
  SDL_Color txt_color = {0,0,0};
  BOOST_CHECK_NO_THROW( GDev::Surface dummy_surface( "Tree", test_font, txt_color ));

  SDL_Color bg_color = {0,0,0};
  BOOST_CHECK_NO_THROW( GDev::Surface dummy_surface( "Tree", test_font, txt_color, &bg_color ));
}

//---------------------------------------------------------------------------//
// Check that a surface object can be converted to another surface object
BOOST_AUTO_TEST_CASE( constructor_conversion )
{
  GDev::Surface surface_a( test_image_filename );

  BOOST_CHECK_NO_THROW( GDev::Surface surface_b( test_image_filename, surface_a.getPixelFormat().format ) );
}

//---------------------------------------------------------------------------//
// Check that a surface object can be constructed
BOOST_AUTO_TEST_CASE( constructor_raw_surface )
{
  GDev::Surface surface( test_image_filename );
  GDev::Surface test_surface( surface.getRawSurfacePtr() );

  BOOST_CHECK( test_surface.getRawSurfacePtr() != NULL );
  BOOST_CHECK_EQUAL( surface.getRawSurfacePtr(), test_surface.getRawSurfacePtr());
}

//---------------------------------------------------------------------------//
// Check that isLocallyOwned works
BOOST_AUTO_TEST_CASE( isLocallyOwned )
{
  GDev::Surface surface1( test_image_filename );
  BOOST_CHECK( surface1.isLocallyOwned() );
  
  GDev::Font test_font( test_font_filename, 16 );
  SDL_Color txt_color = {0,0,0};
  GDev::Surface surface2( "Tree", test_font, txt_color );
  BOOST_CHECK( surface2.isLocallyOwned() );

  GDev::Surface surface3( surface1, SDL_PIXELFORMAT_ARGB8888 );
  BOOST_CHECK( surface3.isLocallyOwned() );
    
  GDev::Surface surface4( surface1.getRawSurfacePtr() );
  BOOST_CHECK( !surface4.isLocallyOwned() );
}

//---------------------------------------------------------------------------//
// Check that width can be returned
BOOST_AUTO_TEST_CASE( getWidth )
{
  GDev::Surface surface( test_image_filename );
  unsigned width = surface.getWidth();
  BOOST_CHECK_EQUAL( width, 800 );
}

//---------------------------------------------------------------------------//
// Check that the height can be returned
BOOST_AUTO_TEST_CASE( getHeight )
{
  GDev::Surface surface( test_image_filename );
  unsigned height = surface.getHeight();
  BOOST_CHECK_EQUAL( height, 600 );
}

//---------------------------------------------------------------------------//
// Check that the pitch can be returned
BOOST_AUTO_TEST_CASE( getPitch )
{
  GDev::Surface surface( test_image_filename );
  unsigned pitch = surface.getPitch();
  BOOST_CHECK_EQUAL( pitch, 3200 );
}

//---------------------------------------------------------------------------//
// Check that pixel format can be returned
BOOST_AUTO_TEST_CASE( getPixelFormat )
{
  GDev::Surface surface( test_image_filename );
  GDev::Surface formatted_surface( surface, SDL_PIXELFORMAT_ARGB8888 );

  BOOST_CHECK_EQUAL( formatted_surface.getPixelFormat().format,
		     SDL_PIXELFORMAT_ARGB8888 );
  BOOST_CHECK( formatted_surface.getPixelFormat().palette == NULL );
  BOOST_CHECK_EQUAL( formatted_surface.getPixelFormat().BitsPerPixel, 32 );
  BOOST_CHECK_EQUAL( formatted_surface.getPixelFormat().BytesPerPixel, 4 );
  BOOST_CHECK( formatted_surface.getPixelFormat().Rmask != 0 );
  BOOST_CHECK( formatted_surface.getPixelFormat().Gmask != 0 );
  BOOST_CHECK( formatted_surface.getPixelFormat().Bmask != 0 );
  BOOST_CHECK( formatted_surface.getPixelFormat().Amask != 0 );
}

//---------------------------------------------------------------------------//
// Check that the pixel format value can be returned
BOOST_AUTO_TEST_CASE( getPixelFormatValue )
{
  GDev::Surface surface( test_image_filename );
  GDev::Surface formatted_surface( surface, SDL_PIXELFORMAT_ARGB8888 );

  BOOST_CHECK_EQUAL( formatted_surface.getPixelFormatValue(),
		     SDL_PIXELFORMAT_ARGB8888 );
}

//---------------------------------------------------------------------------//
// Check that the number of surface pixels can be returned
BOOST_AUTO_TEST_CASE( getNumberOfPixels )
{
  GDev::Surface surface( test_image_filename );
  GDev::Surface formatted_surface( surface, SDL_PIXELFORMAT_ARGB8888 );

  BOOST_CHECK_EQUAL( formatted_surface.getNumberOfPixels(), 480000 ); 
}

//---------------------------------------------------------------------------//
// Check that the SDL Rect structure used to clip blits to the surface can be 
// returned and set
BOOST_AUTO_TEST_CASE( get_setClipRectangle )
{
  GDev::Surface surface( test_image_filename );
  SDL_Rect test_rect = {0,0,10,15};

  BOOST_CHECK_NO_THROW( surface.setClipRectangle( test_rect ));
  BOOST_CHECK_EQUAL( surface.getClipRectangle().x, 0 );
  // Will truncate values to fit screen
  BOOST_CHECK_EQUAL( surface.getClipRectangle().y, 0 );
  BOOST_CHECK_EQUAL( surface.getClipRectangle().w, 10 );
  BOOST_CHECK_EQUAL( surface.getClipRectangle().h, 15 );
}

//---------------------------------------------------------------------------//
// Check that the color key can be returned and set
BOOST_AUTO_TEST_CASE( get_setColorKey )
{
  GDev::Surface surface( test_image_filename );
  Uint32 color_key, returned_color_key;
  color_key = SDL_MapRGB( &surface.getPixelFormat(), 0, 0xFF, 0xFF );

  BOOST_CHECK_NO_THROW( surface.setColorKey( color_key ) );
  BOOST_CHECK_NO_THROW( returned_color_key = surface.getColorKey() );
  BOOST_CHECK_EQUAL( color_key, returned_color_key );
}

//---------------------------------------------------------------------------//
// Check that isColorKeyEnabled works
BOOST_AUTO_TEST_CASE( isColorKeySet )
{
  GDev::Surface surface( test_image_filename );
  Uint32 color_key;
  color_key = SDL_MapRGB( &surface.getPixelFormat(), 0, 0xFF, 0xFF );

  BOOST_CHECK_NO_THROW( surface.setColorKey( color_key ) );
  
  bool color_key_enabled;
  BOOST_CHECK_NO_THROW( color_key_enabled = surface.isColorKeySet() );
  BOOST_CHECK( color_key_enabled );
}

//---------------------------------------------------------------------------//
// Check that the color key can be disabled
BOOST_AUTO_TEST_CASE( unsetColorKey )
{
  GDev::Surface surface( test_image_filename );
  
  BOOST_CHECK( !surface.isColorKeySet() );

  Uint32 color_key;
  color_key = SDL_MapRGB( &surface.getPixelFormat(), 0, 0xFF, 0xFF );

  BOOST_CHECK_NO_THROW( surface.setColorKey( color_key ) );
  BOOST_CHECK( surface.isColorKeySet() );
  
  BOOST_CHECK_NO_THROW( surface.unsetColorKey() );
  BOOST_CHECK( !surface.isColorKeySet() );
}

//---------------------------------------------------------------------------//
// Check that the alpha modulation can be returned and set
BOOST_AUTO_TEST_CASE( get_setAlphaMod )
{
  GDev::Surface surface( test_image_filename );
  Uint8 alpha, returned_alpha;
  alpha = 50;

  BOOST_CHECK_NO_THROW( surface.setAlphaMod( alpha ));
  BOOST_CHECK_NO_THROW( returned_alpha = surface.getAlphaMod() );
  BOOST_CHECK_EQUAL( alpha, returned_alpha );
  
}

//---------------------------------------------------------------------------//
// Check that the blend mode can be returned and set
BOOST_AUTO_TEST_CASE( get_setBlendMode)
{
  GDev::Surface surface( test_image_filename );
  SDL_BlendMode blend, returned_blend;
  blend = SDL_BLENDMODE_BLEND;
  
  BOOST_CHECK_NO_THROW( surface.setBlendMode( blend ));
  BOOST_CHECK_NO_THROW( returned_blend = surface.getBlendMode() );
  BOOST_CHECK_EQUAL ( blend, returned_blend );
}

//---------------------------------------------------------------------------//
// Check that the color mod can be returned and set
BOOST_AUTO_TEST_CASE( get_setColorMod )
{
  GDev::Surface surface( test_image_filename );
  Uint8 red, green, blue;
  red = 255;
  green = 255;
  blue = 255;

  BOOST_CHECK_NO_THROW( surface.setColorMod( red, green, blue ));

  Uint8 returned_red, returned_green, returned_blue;
  
  BOOST_CHECK_NO_THROW( surface.getColorMod( returned_red, 
					     returned_green, 
					     returned_blue ) );
  BOOST_CHECK_EQUAL( returned_red, red );
  BOOST_CHECK_EQUAL( returned_green, green );
  BOOST_CHECK_EQUAL( returned_blue, blue );
}

//---------------------------------------------------------------------------//
// Check that the raw surface pointer can be returned
BOOST_AUTO_TEST_CASE( getRawSurfacePointer )
{
  GDev::Surface surface( test_image_filename );

  BOOST_CHECK( surface.getRawSurfacePtr() != NULL );

  const GDev::Surface const_surface( test_image_filename );

  BOOST_CHECK( const_surface.getRawSurfacePtr() != NULL );
}

//---------------------------------------------------------------------------//
// Check that mustLock works
BOOST_AUTO_TEST_CASE( mustLock )
{
  GDev::Surface surface( test_image_filename );
  // My sample picture does not need to be locked to access pixels
  BOOST_CHECK( !surface.mustLock() );
}

//---------------------------------------------------------------------------//
// Check that a surface can be locked
BOOST_AUTO_TEST_CASE( lock_unlock )
{
  GDev::Surface surface( test_image_filename );

  BOOST_CHECK( !surface.isLocked() );
  
  BOOST_CHECK_NO_THROW( surface.lock() );
  
  BOOST_CHECK( surface.isLocked() );

  surface.unlock();

  BOOST_CHECK( !surface.isLocked() );
}

//---------------------------------------------------------------------------//
// Check that blitScaled works
BOOST_AUTO_TEST_CASE( blitScaled )
{
  GDev::Surface surface( test_image_filename );
  GDev::Surface blank_surface( surface.getWidth(),
			       surface.getHeight(),
			       surface.getPixelFormatValue() );

  // Basic blit
  BOOST_CHECK_NO_THROW( surface.blitScaled( blank_surface ) );

  SDL_Rect source_rect = {0, 0, surface.getWidth()/2, surface.getHeight()/2};
  SDL_Rect dest_rect = {blank_surface.getWidth()/4,
			blank_surface.getHeight()/4,
			blank_surface.getWidth()/2,
			blank_surface.getHeight()/2};

  // Advanced blit
  BOOST_CHECK_NO_THROW( surface.blitScaled( blank_surface,
					    &source_rect,
					    &dest_rect ) );
}

//---------------------------------------------------------------------------//
// Check that blitSurface works
BOOST_AUTO_TEST_CASE( blitSurface )
{
  GDev::Surface surface( test_image_filename );
  GDev::Surface blank_surface( surface.getWidth(),
			       surface.getHeight(),
			       surface.getPixelFormatValue() );

  // Basic blit
  BOOST_CHECK_NO_THROW( surface.blitSurface( blank_surface ) );

  SDL_Rect source_rect = {0, 0, surface.getWidth()/2, surface.getHeight()/2};
  SDL_Rect dest_rect = {blank_surface.getWidth()/4,
			blank_surface.getHeight()/4,
			blank_surface.getWidth()/2,
			blank_surface.getHeight()/2};

  // Advanced blit
  BOOST_CHECK_NO_THROW( surface.blitSurface( blank_surface,
					     &source_rect,
					     &dest_rect ) );
}

//---------------------------------------------------------------------------//
// Check that exportToBMP works
BOOST_AUTO_TEST_CASE( exportToBMP )
{
  GDev::Surface surface( test_image_filename );
  
  BOOST_CHECK_NO_THROW( surface.exportToBMP( "test_image.bmp" ) );

  BOOST_CHECK_NO_THROW( GDev::Surface test_surface( "test_image.bmp" ) );
}
  
BOOST_AUTO_TEST_SUITE_END()

//---------------------------------------------------------------------------//
// end tstSurface.cpp
//---------------------------------------------------------------------------//
