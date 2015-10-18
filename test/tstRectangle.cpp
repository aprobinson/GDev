//---------------------------------------------------------------------------//
//!
//! \file   tstRectangle.hpp
//! \author Alex Robinson
//! \brief  The rectangle class unit tests
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
#include "Rectangle.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a bounding box can be returned
BOOST_AUTO_TEST_CASE( getBoundingBox )
{
  GDev::Rectangle rectangle( 0, 0, 200, 100 );

  SDL_Rect bounding_box;

  rectangle.getBoundingBox( bounding_box );

  BOOST_CHECK_EQUAL( bounding_box.x, 0 );
  BOOST_CHECK_EQUAL( bounding_box.y, 0 );
  BOOST_CHECK_EQUAL( bounding_box.w, 200 );
  BOOST_CHECK_EQUAL( bounding_box.h, 100 );
}

//---------------------------------------------------------------------------//
// Check that the bounding box x position can be returned
BOOST_AUTO_TEST_CASE( getBoundingBoxXPosition )
{
  GDev::Rectangle rectangle( 0, 0, 200, 100 );

  BOOST_CHECK_EQUAL( rectangle.getBoundingBoxXPosition(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the bounding box y position can be returned
BOOST_AUTO_TEST_CASE( getBoundingBoxYPosition )
{
  GDev::Rectangle rectangle( 0, 0, 200, 100 );

  BOOST_CHECK_EQUAL( rectangle.getBoundingBoxYPosition(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the bounding box width can be returned
BOOST_AUTO_TEST_CASE( getBoundingBoxWidth )
{
  GDev::Rectangle rectangle( 0, 0, 200, 100 );

  BOOST_CHECK_EQUAL( rectangle.getBoundingBoxWidth(), 200 );
}

//---------------------------------------------------------------------------//
// Check that the bounding box height can be returned
BOOST_AUTO_TEST_CASE( getBoundingBoxHeight )
{
  GDev::Rectangle rectangle( 0, 0, 200, 100 );

  BOOST_CHECK_EQUAL( rectangle.getBoundingBoxHeight(), 100 );
}

//---------------------------------------------------------------------------//
// Check that the center point can be returned
BOOST_AUTO_TEST_CASE( getCenterPoint )
{
  GDev::Rectangle rectangle( 0, 0, 200, 100 );

  SDL_Point center_point;

  rectangle.getCenterPoint( center_point );

  BOOST_CHECK_EQUAL( center_point.x, 100 );
  BOOST_CHECK_EQUAL( center_point.y, 50 );
}

//---------------------------------------------------------------------------//
// Check that the center x position can be returned
BOOST_AUTO_TEST_CASE( getCenterXPosition )
{
  GDev::Rectangle rectangle( 0, 0, 200, 100 );

  BOOST_CHECK_EQUAL( rectangle.getCenterXPosition(), 100 );
}

//---------------------------------------------------------------------------//
// Check that the center y position can be returned
BOOST_AUTO_TEST_CASE( getCenterYPosition )
{
  GDev::Rectangle rectangle( 0, 0, 200, 100 );

  BOOST_CHECK_EQUAL( rectangle.getCenterYPosition(), 50 );
}

//---------------------------------------------------------------------------//
// Check if a point is in the rectangle
BOOST_AUTO_TEST_CASE( isPointIn )
{
  // No edge
  std::shared_ptr<GDev::Shape> shape( new GDev::Rectangle( 0, 0, 200, 100 ) );

  BOOST_CHECK( !shape->isPointIn( -1, -1 ) );
  BOOST_CHECK( !shape->isPointIn( 0, -1 ) );
  BOOST_CHECK( !shape->isPointIn( 100, -1 ) );
  BOOST_CHECK( !shape->isPointIn( 200, -1 ) );
  BOOST_CHECK( !shape->isPointIn( 201, -1 ) );
  
  BOOST_CHECK( !shape->isPointIn( -1, 0 ) );
  BOOST_CHECK( shape->isPointIn( 0, 0 ) );
  BOOST_CHECK( shape->isPointIn( 100, 0 ) );
  BOOST_CHECK( shape->isPointIn( 200, 0 ) );
  BOOST_CHECK( !shape->isPointIn( 201, 0 ) );
  
  BOOST_CHECK( !shape->isPointIn( -1, 50 ) );
  BOOST_CHECK( shape->isPointIn( 0, 50 ) );
  BOOST_CHECK( shape->isPointIn( 100, 50 ) );
  BOOST_CHECK( shape->isPointIn( 200, 50 ) );
  BOOST_CHECK( !shape->isPointIn( 201, 50 ) );
  
  BOOST_CHECK( !shape->isPointIn( -1, 100 ) );
  BOOST_CHECK( shape->isPointIn( 0, 100 ) );
  BOOST_CHECK( shape->isPointIn( 100, 100 ) );
  BOOST_CHECK( shape->isPointIn( 200, 100 ) );
  BOOST_CHECK( !shape->isPointIn( 201, 100 ) );

  BOOST_CHECK( !shape->isPointIn( -1, 101 ) );
  BOOST_CHECK( !shape->isPointIn( 0, 101 ) );
  BOOST_CHECK( !shape->isPointIn( 100, 101 ) );
  BOOST_CHECK( !shape->isPointIn( 200, 101 ) );
  BOOST_CHECK( !shape->isPointIn( 201, 101 ) );

  // Edge
  shape.reset( new GDev::Rectangle( 0, 0, 200, 100, 1 ) );

  BOOST_CHECK( !shape->isPointIn( -1, -1 ) );
  BOOST_CHECK( !shape->isPointIn( 0, -1 ) );
  BOOST_CHECK( !shape->isPointIn( 100, -1 ) );
  BOOST_CHECK( !shape->isPointIn( 200, -1 ) );
  BOOST_CHECK( !shape->isPointIn( 201, -1 ) );
  
  BOOST_CHECK( !shape->isPointIn( -1, 0 ) );
  BOOST_CHECK( shape->isPointIn( 0, 0 ) );
  BOOST_CHECK( shape->isPointIn( 100, 0 ) );
  BOOST_CHECK( shape->isPointIn( 200, 0 ) );
  BOOST_CHECK( !shape->isPointIn( 201, 0 ) );
  
  BOOST_CHECK( !shape->isPointIn( -1, 50 ) );
  BOOST_CHECK( shape->isPointIn( 0, 50 ) );
  BOOST_CHECK( shape->isPointIn( 100, 50 ) );
  BOOST_CHECK( shape->isPointIn( 200, 50 ) );
  BOOST_CHECK( !shape->isPointIn( 201, 50 ) );
  
  BOOST_CHECK( !shape->isPointIn( -1, 100 ) );
  BOOST_CHECK( shape->isPointIn( 0, 100 ) );
  BOOST_CHECK( shape->isPointIn( 100, 100 ) );
  BOOST_CHECK( shape->isPointIn( 200, 100 ) );
  BOOST_CHECK( !shape->isPointIn( 201, 100 ) );

  BOOST_CHECK( !shape->isPointIn( -1, 101 ) );
  BOOST_CHECK( !shape->isPointIn( 0, 101 ) );
  BOOST_CHECK( !shape->isPointIn( 100, 101 ) );
  BOOST_CHECK( !shape->isPointIn( 200, 101 ) );
  BOOST_CHECK( !shape->isPointIn( 201, 101 ) );
}

//---------------------------------------------------------------------------//
// Check if a point is on the rectangle boundary
BOOST_AUTO_TEST_CASE( isPointOn )
{
  // No edge
  std::shared_ptr<GDev::Shape> shape( new GDev::Rectangle( 0, 0, 200, 100 ) );

  BOOST_CHECK( !shape->isPointOn( -1, -1 ) );
  BOOST_CHECK( !shape->isPointOn( 0, -1 ) );
  BOOST_CHECK( !shape->isPointOn( 100, -1 ) );
  BOOST_CHECK( !shape->isPointOn( 200, -1 ) );
  BOOST_CHECK( !shape->isPointOn( 201, -1 ) );
  
  BOOST_CHECK( !shape->isPointOn( -1, 0 ) );
  BOOST_CHECK( !shape->isPointOn( 0, 0 ) );
  BOOST_CHECK( !shape->isPointOn( 100, 0 ) );
  BOOST_CHECK( !shape->isPointOn( 200, 0 ) );
  BOOST_CHECK( !shape->isPointOn( 201, 0 ) );
  
  BOOST_CHECK( !shape->isPointOn( -1, 50 ) );
  BOOST_CHECK( !shape->isPointOn( 0, 50 ) );
  BOOST_CHECK( !shape->isPointOn( 100, 50 ) );
  BOOST_CHECK( !shape->isPointOn( 200, 50 ) );
  BOOST_CHECK( !shape->isPointOn( 201, 50 ) );
  
  BOOST_CHECK( !shape->isPointOn( -1, 100 ) );
  BOOST_CHECK( !shape->isPointOn( 0, 100 ) );
  BOOST_CHECK( !shape->isPointOn( 100, 100 ) );
  BOOST_CHECK( !shape->isPointOn( 200, 100 ) );
  BOOST_CHECK( !shape->isPointOn( 201, 100 ) );

  BOOST_CHECK( !shape->isPointOn( -1, 101 ) );
  BOOST_CHECK( !shape->isPointOn( 0, 101 ) );
  BOOST_CHECK( !shape->isPointOn( 100, 101 ) );
  BOOST_CHECK( !shape->isPointOn( 200, 101 ) );
  BOOST_CHECK( !shape->isPointOn( 201, 101 ) );

  // Edge
  shape.reset( new GDev::Rectangle( 0, 0, 200, 100, 2 ) );

  BOOST_CHECK( !shape->isPointOn( -1, -1 ) );
  BOOST_CHECK( !shape->isPointOn( 0, -1 ) );
  BOOST_CHECK( !shape->isPointOn( 2, -1 ) );
  BOOST_CHECK( !shape->isPointOn( 3, -1 ) );
  BOOST_CHECK( !shape->isPointOn( 100, -1 ) );
  BOOST_CHECK( !shape->isPointOn( 197, -1 ) );
  BOOST_CHECK( !shape->isPointOn( 198, -1 ) );
  BOOST_CHECK( !shape->isPointOn( 200, -1 ) );
  BOOST_CHECK( !shape->isPointOn( 201, -1 ) );
  
  BOOST_CHECK( !shape->isPointOn( -1, 0 ) );
  BOOST_CHECK( shape->isPointOn( 0, 0 ) );
  BOOST_CHECK( shape->isPointOn( 2, 0 ) );
  BOOST_CHECK( shape->isPointOn( 3, 0 ) );
  BOOST_CHECK( shape->isPointOn( 100, 0 ) );
  BOOST_CHECK( shape->isPointOn( 197, 0 ) );
  BOOST_CHECK( shape->isPointOn( 198, 0 ) );
  BOOST_CHECK( shape->isPointOn( 200, 0 ) );
  BOOST_CHECK( !shape->isPointOn( 201, 0 ) );
  
  BOOST_CHECK( !shape->isPointOn( -1, 2 ) );
  BOOST_CHECK( shape->isPointOn( 0, 2 ) );
  BOOST_CHECK( shape->isPointOn( 2, 2 ) );
  BOOST_CHECK( shape->isPointOn( 3, 2 ) );
  BOOST_CHECK( shape->isPointOn( 100, 2 ) );
  BOOST_CHECK( shape->isPointOn( 97, 2 ) );
  BOOST_CHECK( shape->isPointOn( 98, 2 ) );
  BOOST_CHECK( shape->isPointOn( 200, 2 ) );
  BOOST_CHECK( !shape->isPointOn( 201, 2 ) );

  BOOST_CHECK( !shape->isPointOn( -1, 3 ) );
  BOOST_CHECK( shape->isPointOn( 0, 3 ) );
  BOOST_CHECK( shape->isPointOn( 2, 3 ) );
  BOOST_CHECK( !shape->isPointOn( 3, 3 ) );
  BOOST_CHECK( !shape->isPointOn( 100, 3 ) );
  BOOST_CHECK( !shape->isPointOn( 197, 3 ) );
  BOOST_CHECK( shape->isPointOn( 198, 3 ) );
  BOOST_CHECK( shape->isPointOn( 200, 3 ) );
  BOOST_CHECK( !shape->isPointOn( 201, 3 ) );
  
  BOOST_CHECK( !shape->isPointOn( -1, 50 ) );
  BOOST_CHECK( shape->isPointOn( 0, 50 ) );
  BOOST_CHECK( shape->isPointOn( 2, 50 ) );
  BOOST_CHECK( !shape->isPointOn( 3, 50 ) );
  BOOST_CHECK( !shape->isPointOn( 100, 50 ) );
  BOOST_CHECK( !shape->isPointOn( 197, 50 ) );
  BOOST_CHECK( shape->isPointOn( 198, 50 ) );
  BOOST_CHECK( shape->isPointOn( 200, 50 ) );
  BOOST_CHECK( !shape->isPointOn( 201, 50 ) );

  BOOST_CHECK( !shape->isPointOn( -1, 97 ) );
  BOOST_CHECK( shape->isPointOn( 0, 97 ) );
  BOOST_CHECK( shape->isPointOn( 2, 97 ) );
  BOOST_CHECK( !shape->isPointOn( 3, 97 ) );
  BOOST_CHECK( !shape->isPointOn( 100, 97 ) );
  BOOST_CHECK( !shape->isPointOn( 197, 97 ) );
  BOOST_CHECK( shape->isPointOn( 198, 97 ) );
  BOOST_CHECK( shape->isPointOn( 200, 97 ) );
  BOOST_CHECK( !shape->isPointOn( 201, 97 ) );

  BOOST_CHECK( !shape->isPointOn( -1, 98 ) );
  BOOST_CHECK( shape->isPointOn( 0, 98 ) );
  BOOST_CHECK( shape->isPointOn( 2, 98 ) );
  BOOST_CHECK( shape->isPointOn( 3, 98 ) );
  BOOST_CHECK( shape->isPointOn( 100, 98 ) );
  BOOST_CHECK( shape->isPointOn( 197, 98 ) );
  BOOST_CHECK( shape->isPointOn( 198, 98 ) );
  BOOST_CHECK( shape->isPointOn( 200, 98 ) );
  BOOST_CHECK( !shape->isPointOn( 201, 98 ) );
  
  BOOST_CHECK( !shape->isPointOn( -1, 100 ) );
  BOOST_CHECK( shape->isPointOn( 0, 100 ) );
  BOOST_CHECK( shape->isPointOn( 2, 100 ) );
  BOOST_CHECK( shape->isPointOn( 3, 100 ) );
  BOOST_CHECK( shape->isPointOn( 100, 100 ) );
  BOOST_CHECK( shape->isPointOn( 197, 100 ) );
  BOOST_CHECK( shape->isPointOn( 198, 100 ) );
  BOOST_CHECK( shape->isPointOn( 200, 100 ) );
  BOOST_CHECK( !shape->isPointOn( 201, 100 ) );

  BOOST_CHECK( !shape->isPointOn( -1, 101 ) );
  BOOST_CHECK( !shape->isPointOn( 0, 101 ) );
  BOOST_CHECK( !shape->isPointOn( 2, 101 ) );
  BOOST_CHECK( !shape->isPointOn( 3, 101 ) );
  BOOST_CHECK( !shape->isPointOn( 100, 101 ) );
  BOOST_CHECK( !shape->isPointOn( 197, 101 ) );
  BOOST_CHECK( !shape->isPointOn( 198, 101 ) );
  BOOST_CHECK( !shape->isPointOn( 200, 101 ) );
  BOOST_CHECK( !shape->isPointOn( 201, 101 ) );
}

//---------------------------------------------------------------------------//
// end tstRectangle.cpp
//---------------------------------------------------------------------------//
