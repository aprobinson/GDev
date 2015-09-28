//---------------------------------------------------------------------------//
//!
//! \file   ContractException.hpp
//! \author Alex Robinson
//! \brief  Design-by-Contract exception handling and error policy declaration.
//!
//---------------------------------------------------------------------------//

#ifndef GDEV_CONTRACT_EXCEPTION_HPP
#define GDEV_CONTRACT_EXCEPTION_HPP

// Std Lib Includes
#include <stdexcept>
#include <string>

namespace GDev{

/*! Exception class to be thrown when function contract is not met.
 *
 * The ContractExpection class is a key part of DBC.
 * \ingroup contract_exceptions_macros
 */

class ContractException : public std::logic_error
{
public:
  ContractException( const std::string &msg )
    : std::logic_error( msg )
  { /* ... */ }
  
  virtual ~ContractException() throw()
  { /* ... */ }
};

} // end GDev namespace

#endif // end GDEV_CONTRACT_EXCEPTION_HPP

//---------------------------------------------------------------------------//
// end ContractException.hpp
//---------------------------------------------------------------------------//
