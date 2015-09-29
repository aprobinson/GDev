//---------------------------------------------------------------------------//
//!
//! \file   tstFont.cpp
//! \author Alex Robinson
//! \brief  Font wrapper class unit tests.
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
#include "Font.hpp"
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
    if( boost::unit_test::framework::master_test_suite().argc > 1 )
    {
      test_font_filename = 
	boost::unit_test::framework::master_test_suite().argv[1];
    }
    else
    {
      std::cerr << "Error: The font filename must be specified (arg 1)"
		<< std::endl;

      exit(1);
    }
  }

  // The font filename
  std::string test_font_filename;  
};

BOOST_GLOBAL_FIXTURE( GlobalInitFixture );

BOOST_FIXTURE_TEST_SUITE( Font, CommandLineArgsFixture )

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a font object can be constructed
BOOST_AUTO_TEST_CASE( constructor )
{
  BOOST_CHECK_NO_THROW( GDev::Font dummy_font( test_font_filename, 28 ) );
}

//---------------------------------------------------------------------------//
// Check that the font size can be constructed
BOOST_AUTO_TEST_CASE( getFontSize )
{
  GDev::Font font_1( test_font_filename, 28 );

  BOOST_CHECK_EQUAL( font_1.getFontSize(), 28 );

  GDev::Font font_2( test_font_filename, 48 );

  BOOST_CHECK_EQUAL( font_2.getFontSize(), 48 );
}

//---------------------------------------------------------------------------//
// Check that the raw pointer can be returned
BOOST_AUTO_TEST_CASE( getRawFontPtr )
{
  GDev::Font font( test_font_filename, 10 );

  BOOST_CHECK( font.getRawFontPtr() );
  
  const GDev::Font const_font( test_font_filename, 20 );

  BOOST_CHECK( font.getRawFontPtr() );
}

BOOST_AUTO_TEST_SUITE_END()

//---------------------------------------------------------------------------//
// end tstFont.cpp
//---------------------------------------------------------------------------//
