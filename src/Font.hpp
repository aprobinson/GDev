//---------------------------------------------------------------------------//
//!
//! \file   Font.hpp
//! \author Alex Robinson
//! \brief  The font wrapper class decl.
//!
//---------------------------------------------------------------------------//

#ifndef GDEV_FONT_HPP
#define GDEV_FONT_HPP

// Std Lib Includes
#include <string>

// Boost Includes
#include <boost/core/noncopyable.hpp>

// SDL Includes
#include <SDL2/SDL_ttf.h>

namespace GDev{

/*! The font wrapper class
 * \details The wrapper class does not allow copy construction or assignment.
 * If multiple "copies" are needed, use a smart pointer class.
 */
class Font : private boost::noncopyable
{

public:

  //! Constructor
  Font( const std::string& font_filename, const unsigned font_size );

  //! Destructor
  ~Font();

  //! Get the font size
  unsigned getFontSize() const;

  //! Get the raw font pointer (potentially dangerous)
  const TTF_Font* getRawFontPtr() const;

  //! Get the raw font pointer (potentially dangerous)
  TTF_Font* getRawFontPtr();

private:

  // Free the font
  void free();

  //! Do not allow default construction
  Font();

  // The TTF font
  TTF_Font* d_font;

  // The font size
  unsigned d_font_size;
};

//! The font exception class
class FontException : public std::runtime_error
{
public:
  FontException( const std::string& message )
    : std::runtime_error( message )
  { /* ... */ }

  ~FontException() throw()
  { /* ... */ }
};

} // end GDev namespace

#endif // end GDEV_FONT_HPP

//---------------------------------------------------------------------------//
// end Font.hpp
//---------------------------------------------------------------------------//
