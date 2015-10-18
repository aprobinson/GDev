//---------------------------------------------------------------------------//
//!
//! \file   tstEllipse.hpp
//! \author Alex Robinson
//! \brief  The ellipse class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <string>
#include <memory>

// Boost Includes
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

// GDev Includes
#include "Ellipse.hpp"


//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a bounding box can be returned
BOOST_AUTO_TEST_CASE( getBoundingBox )
{
  GDev::Ellipse ellipse( 100, 50, 100, 50 );

  SDL_Rect bounding_box;

  ellipse.getBoundingBox( bounding_box );

  BOOST_CHECK_EQUAL( bounding_box.x, 0 );
  BOOST_CHECK_EQUAL( bounding_box.y, 0 );
  BOOST_CHECK_EQUAL( bounding_box.w, 200 );
  BOOST_CHECK_EQUAL( bounding_box.h, 100 );
}

//---------------------------------------------------------------------------//
// Check that the bounding box x position can be returned
BOOST_AUTO_TEST_CASE( getBoundingBoxXPosition )
{
  GDev::Ellipse ellipse( 100, 50, 100, 50 );

  BOOST_CHECK_EQUAL( ellipse.getBoundingBoxXPosition(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the bounding box y position can be returned
BOOST_AUTO_TEST_CASE( getBoundingBoxYPosition )
{
  GDev::Ellipse ellipse( 100, 50, 100, 50 );

  BOOST_CHECK_EQUAL( ellipse.getBoundingBoxYPosition(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the bounding box width can be returned
BOOST_AUTO_TEST_CASE( getBoundingBoxWidth )
{
  GDev::Ellipse ellipse( 100, 50, 100, 50 );

  BOOST_CHECK_EQUAL( ellipse.getBoundingBoxWidth(), 200 );
}

//---------------------------------------------------------------------------//
// Check that the bounding box height can be returned
BOOST_AUTO_TEST_CASE( getBoundingBoxHeight )
{
  GDev::Ellipse ellipse( 100, 50, 100, 50 );

  BOOST_CHECK_EQUAL( ellipse.getBoundingBoxHeight(), 100 );
}

//---------------------------------------------------------------------------//
// Check that the center point can be returned
BOOST_AUTO_TEST_CASE( getCenterPoint )
{
  GDev::Ellipse ellipse( 100, 50, 100, 50 );

  SDL_Point center_point;

  ellipse.getCenterPoint( center_point );

  BOOST_CHECK_EQUAL( center_point.x, 100 );
  BOOST_CHECK_EQUAL( center_point.y, 50 );
}

//---------------------------------------------------------------------------//
// Check that the center x position can be returned
BOOST_AUTO_TEST_CASE( getCenterXPosition )
{
  GDev::Ellipse ellipse( 100, 50, 100, 50 );

  BOOST_CHECK_EQUAL( ellipse.getCenterXPosition(), 100 );
}

//---------------------------------------------------------------------------//
// Check that the center y position can be returned
BOOST_AUTO_TEST_CASE( getCenterYPosition )
{
  GDev::Ellipse ellipse( 100, 50, 100, 50 );

  BOOST_CHECK_EQUAL( ellipse.getCenterYPosition(), 50 );
}

//---------------------------------------------------------------------------//
// Check if a point is in the rectangle
BOOST_AUTO_TEST_CASE( isPointIn )
{
  // No edge
  std::shared_ptr<GDev::Shape> shape( new GDev::Ellipse( 100, 50, 100, 50 ) );

  // Major axis
  BOOST_CHECK( !shape->isPointIn( -1, 50 ) );
  BOOST_CHECK( shape->isPointIn( 0, 50 ) );
  BOOST_CHECK( shape->isPointIn( 100, 50 ) );
  BOOST_CHECK( shape->isPointIn( 200, 50 ) );
  BOOST_CHECK( !shape->isPointIn( 201, 50 ) );

  // Minor axis
  BOOST_CHECK( !shape->isPointIn( 100, -1 ) );
  BOOST_CHECK( shape->isPointIn( 100, 0 ) );
  BOOST_CHECK( shape->isPointIn( 100, 50 ) );
  BOOST_CHECK( shape->isPointIn( 100, 100 ) );
  BOOST_CHECK( !shape->isPointIn( 100, 101 ) );

  // Edge
  shape.reset( new GDev::Ellipse( 100, 50, 100, 50, 2 ) );

  // Major axis
  BOOST_CHECK( !shape->isPointIn( -1, 50 ) );
  BOOST_CHECK( shape->isPointIn( 0, 50 ) );
  BOOST_CHECK( shape->isPointIn( 100, 50 ) );
  BOOST_CHECK( shape->isPointIn( 200, 50 ) );
  BOOST_CHECK( !shape->isPointIn( 201, 50 ) );

  // Minor axis
  BOOST_CHECK( !shape->isPointIn( 100, -1 ) );
  BOOST_CHECK( shape->isPointIn( 100, 0 ) );
  BOOST_CHECK( shape->isPointIn( 100, 50 ) );
  BOOST_CHECK( shape->isPointIn( 100, 100 ) );
  BOOST_CHECK( !shape->isPointIn( 100, 101 ) );
}

//---------------------------------------------------------------------------//
// Check if a point is on the rectangle boundary
BOOST_AUTO_TEST_CASE( isPointOn )
{
  // No edge
  std::shared_ptr<GDev::Shape> shape( new GDev::Ellipse( 100, 50, 100, 50 ) );

  // Major axis
  BOOST_CHECK( !shape->isPointOn( -1, 50 ) );
  BOOST_CHECK( !shape->isPointOn( 0, 50 ) );
  BOOST_CHECK( !shape->isPointOn( 100, 50 ) );
  BOOST_CHECK( !shape->isPointOn( 200, 50 ) );
  BOOST_CHECK( !shape->isPointOn( 201, 50 ) );

  // Minor axis
  BOOST_CHECK( !shape->isPointOn( 100, -1 ) );
  BOOST_CHECK( !shape->isPointOn( 100, 0 ) );
  BOOST_CHECK( !shape->isPointOn( 100, 50 ) );
  BOOST_CHECK( !shape->isPointOn( 100, 100 ) );
  BOOST_CHECK( !shape->isPointOn( 100, 101 ) );

  // Edge
  shape.reset( new GDev::Ellipse( 100, 50, 100, 50, 2 ) );

  // Major axis
  BOOST_CHECK( !shape->isPointOn( -1, 50 ) );
  BOOST_CHECK( shape->isPointOn( 0, 50 ) );
  BOOST_CHECK( shape->isPointOn( 2, 50 ) );
  BOOST_CHECK( !shape->isPointOn( 3, 50 ) );
  BOOST_CHECK( !shape->isPointOn( 100, 50 ) );
  BOOST_CHECK( !shape->isPointOn( 197, 50 ) );
  BOOST_CHECK( shape->isPointOn( 198, 50 ) );
  BOOST_CHECK( shape->isPointOn( 200, 50 ) );
  BOOST_CHECK( !shape->isPointOn( 201, 50 ) );

  // Minor axis
  BOOST_CHECK( !shape->isPointOn( 100, -1 ) );
  BOOST_CHECK( shape->isPointOn( 100, 0 ) );
  BOOST_CHECK( shape->isPointOn( 100, 2 ) );
  BOOST_CHECK( !shape->isPointOn( 100, 3 ) );
  BOOST_CHECK( !shape->isPointOn( 100, 50 ) );
  BOOST_CHECK( !shape->isPointOn( 100, 97 ) );
  BOOST_CHECK( shape->isPointOn( 100, 98 ) );
  BOOST_CHECK( shape->isPointOn( 100, 100 ) );
  BOOST_CHECK( !shape->isPointOn( 100, 101 ) );
}

//---------------------------------------------------------------------------//
// end tstEllipse.cpp
//---------------------------------------------------------------------------//
