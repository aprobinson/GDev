//---------------------------------------------------------------------------//
//!
//! \file   RenderableObject.hpp
//! \author Alex Robinson, Sean Robinson
//! \brief  The renderable object base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef RENDERABLE_OBJECT_HPP
#define RENDERABLE_OBJECT_HPP

//! The renderable object base class
class RenderableObject
{

public:

  //! Default constructor
  RenderableObject()
  { /* ... */ }

  //! Destructor
  virtual ~RenderableObject()
  { /* ... */ }

  //! Render the object
  virtual void render() const = 0;
};

#endif // end RENDERABLE_OBJECT

//---------------------------------------------------------------------------//
// end RenderableObject.hpp
//---------------------------------------------------------------------------//
