//---------------------------------------------------------------------------//
//!
//! \file   ExceptionTestMacros.hpp
//! \author Alex Robinson
//! \brief  Macros that test if an exception has occured and throw if so
//!
//---------------------------------------------------------------------------//

#ifndef GDEV_EXCEPTION_TEST_MACROS_HPP
#define GDEV_EXCEPTION_TEST_MACROS_HPP

// Std Lib Includes
#include <sstream>
#include <string>

/*! Exception test macro used to throw an exception when a required condition
 * fails.
 *
 * This macro is based off of the Teuchos_TestForException macro. This macro
 * should be used anywhere that the failure of a specified conditions 
 * warrants the throwing of an exception.
 * \ingroup execption_macros
 */
#define TEST_FOR_EXCEPTION(throw_exception_test, Exception, msg)	\
{									\
 const bool throw_exception = (throw_exception_test);			\
 if( throw_exception ){							\
   std::ostringstream detailed_msg;					\
   detailed_msg << __FILE__ << ":" << __LINE__ << ":\n\n"		\
       << "Throw test that evaluated to true: "#throw_exception_test	\
       << "\n\n" << msg;						\
   const std::string &detailed_msg_str = detailed_msg.str();		\
   throw Exception(detailed_msg_str);					\
 }									\
} 

/*! Throw an exception always
 *
 * This macros should be used in conditional execution blocks that should never
 * be reached (e.g. default case statement).
 * \ingroup exception_macros
 */
#define THROW_EXCEPTION( Exception, msg ) \
{					  \
 std::ostringstream detailed_msg;	  \
 detailed_msg << __FILE__ << ":" << __LINE__ << ":\n\n" \
 << msg;						\
 throw Exception(detailed_msg.str());			\
}

#endif // end GDEV_EXCEPTION_TEST_MACROS_HPP

//---------------------------------------------------------------------------//
// end ExceptionTestMacros.hpp
//---------------------------------------------------------------------------//
