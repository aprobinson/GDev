//---------------------------------------------------------------------------//
//!
//! \file   tstGlobalSDLSession.hpp
//! \author Alex Robinson
//! \brief  The global SDL session class unit tests
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
#include "GlobalSDLSession.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that GlobalSDLSession initializes correctly
BOOST_AUTO_TEST_CASE( default_state )
{
  BOOST_CHECK( !GDev::GlobalSDLSession::isSDLInitialized() );
  BOOST_CHECK( !GDev::GlobalSDLSession::isSDLFinalized() );
}

//---------------------------------------------------------------------------//
// Check that the constructor initializes SDL
BOOST_AUTO_TEST_CASE( constructor_destructor, 
		      * boost::unit_test::depends_on("default_state") )
{
  {
    GDev::GlobalSDLSession session;

    BOOST_CHECK( GDev::GlobalSDLSession::isSDLInitialized() );
    BOOST_CHECK( !GDev::GlobalSDLSession::isSDLFinalized() );
  }

  BOOST_CHECK( !GDev::GlobalSDLSession::isSDLInitialized() );
  BOOST_CHECK( GDev::GlobalSDLSession::isSDLFinalized() );
}

//---------------------------------------------------------------------------//
// end tstGlobalSDLSession.hpp
//---------------------------------------------------------------------------//
