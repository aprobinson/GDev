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
#include <memory>

// Boost Includes
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>

// GDev Includes
#include "GlobalSDLSession.hpp"

//---------------------------------------------------------------------------//
// Testing variables
//---------------------------------------------------------------------------//
std::shared_ptr<GDev::GlobalSDLSession> session;

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
BOOST_AUTO_TEST_CASE( constructor, 
		      * boost::unit_test::depends_on("default_state") )
{
  session.reset( new GDev::GlobalSDLSession() );

  BOOST_CHECK( GDev::GlobalSDLSession::isSDLInitialized() );
  BOOST_CHECK( !GDev::GlobalSDLSession::isSDLFinalized() ); 
}

//---------------------------------------------------------------------------//
// Check that the number of milliseconds since initialization can be returned
BOOST_AUTO_TEST_CASE( getMilliseconds,
		      * boost::unit_test::depends_on("constructor") )
{
  Uint32 time_1 = GDev::GlobalSDLSession::getMilliseconds();
  BOOST_CHECK( time_1 > 0 );

  GDev::GlobalSDLSession::delay( 1 );

  Uint32 time_2 = GDev::GlobalSDLSession::getMilliseconds();
  
  BOOST_CHECK_EQUAL( time_2, time_1+1 );
}

//---------------------------------------------------------------------------//
// Check that the destructor finalizes SDL
BOOST_AUTO_TEST_CASE( destructor,
		      * boost::unit_test::depends_on("constructor") )
{
  session.reset();
  
  BOOST_CHECK( !GDev::GlobalSDLSession::isSDLInitialized() );
  BOOST_CHECK( GDev::GlobalSDLSession::isSDLFinalized() );
}

//---------------------------------------------------------------------------//
// end tstGlobalSDLSession.hpp
//---------------------------------------------------------------------------//
