//---------------------------------------------------------------------------//
//!
//! \file   Font.cpp
//! \author Alex Robinson
//! \brief  The font wrapper class definition.
//!
//---------------------------------------------------------------------------//

// SDL Includes
#include "Font.hpp"
#include "ExceptionTestMacros.hpp"
#include "DBCMacros.hpp"

namespace GDev{

// Constructor
Font::Font( const std::string& font_filename, const unsigned font_size )
  : d_font( NULL ),
    d_font_size( font_size )
{
  // Make sure the font filename is valid
  testPrecondition( font_filename.size() > 0 );

  // Load the font
  d_font = TTF_OpenFont( font_filename.c_str(), font_size );

  // Make sure the font was successfully loaded
  TEST_FOR_EXCEPTION( d_font == NULL,
		      FontException,
		      "Unable to load font from file " << font_filename <<
		      "! SDL_ttf Error: " << TTF_GetError() );
}

// Destructor
Font::~Font()
{
  this->free();
}

// Get the font size
unsigned Font::getFontSize() const
{
  return d_font_size;
}

// Get the raw font pointer (potentially dangerous)
/*! \details Use this with the SDL C interface when necessary.
 */
const TTF_Font* Font::getRawFontPtr() const
{
  return d_font;
}

// Get the raw font pointer (potentially dangerous)
/*! \details Use this with the SDL C interface when necessary.
 */
TTF_Font* Font::getRawFontPtr()
{
  return d_font;
}

// Free the font
void Font::free()
{
  // Close the font
  TTF_CloseFont( d_font );

  d_font = NULL;
  
  // Reset the font size
  d_font_size = 0u;
}

} // end GDev namespace

//---------------------------------------------------------------------------//
// end Font.cpp
//---------------------------------------------------------------------------//
