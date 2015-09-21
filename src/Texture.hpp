//---------------------------------------------------------------------------//
//!
//! \file   Texture.hpp
//! \author Alex Robinson, Sean Robinson
//! \brief  The texture class declaration
//!
//---------------------------------------------------------------------------//

#ifndef TEXTURE_HPP
#define TEXTURE_HPP

// Boost Includes
#include <boost/scoped_ptr.hpp>

// SDL Includes
#include <SDL2/SDL.h>

// GDev Includes
#include "RenderableObject.hpp"

//! The texture class
class Texture : public RenderableObject
{

public:
  
  //! Default constructor
  Texture();

  //! Destructor
  ~Texture();

  //! Load the image
  void loadFromFile( const std::string& filename,
		     const unsigned char color_key_red = 0xFF,
		     const unsigned char color_key_green = 0xFF,
		     const unsigned char color_key_blue = 0xFF );

  //! Load the text
  void loadFromText( const std::string& message,
		     const SDL_Color& text_color );

  //! Set the color modulation
  void setColorModulation( const SDL_Color& color_modulation );

  //! Set the blending
  void setBlendMode( const SDL_BlendMode blending );

  //! Set the alpha modulation
  void setAlpha( const unsigned char alpha );

  //! Set the position to render the texture at
  void setPosition( const int x_position, const int y_position );

  //! Set the clip rectangle
  void setClipRectangle( const SDL_Rect& clip );

  //! Reset the clip rectangle
  void resetClipRectangle();

  //! Set the rotation angle (degrees)
  void setRotationAngle( const double angle );
  
  //! Reset the rotation angle and rotation point
  void resetRotationAngle();

  //! Set the rotation center
  void setRotationCenter( const SDL_Point& center );

  //! Reset the rotation center
  void resetRotationCenter();

  //! Set the flip state
  void setRendererFlip( const SDL_RendererFlip flip );

  //! Reset the renderer flip state
  void resetRendererFlip();

  //! Render the texture
  void render() const;

  //! Get the image width
  unsigned getWidth() const;

  //! Get the image height
  unsigned getHeight() const;

private:

  // Free texture
  void freeTexture();

  // The SDL texture
  SDL_Texture* d_texture;

  // The image width
  unsigned d_width;

  // The image height
  unsigned d_height;

  // The position where the texture will be rendered
  int d_x_position;
  int d_y_position;

  // The clip rectangle
  boost::scoped_ptr<SDL_Rect> d_clip;

  // The rotation angle (degrees)
  double d_rotation_angle;

  // The rotation center
  boost::scoped_ptr<SDL_Center> d_center;

  // The renderer flip state
  SDL_RendererFlip d_flip;
};

// end TEXTURE_HPP

//---------------------------------------------------------------------------//
// end Texture.hpp
//---------------------------------------------------------------------------//
