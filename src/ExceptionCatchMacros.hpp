//---------------------------------------------------------------------------//
//!
//! \file   ExceptionCatchMacros.hpp
//! \author Alex Robinson
//! \brief  Macros for catching Exceptions
//!
//---------------------------------------------------------------------------//

#ifndef GDEV_EXCEPTION_CATCH_MACROS_HPP
#define GDEV_EXCEPTION_CATCH_MACROS_HPP

// Std Lib Includes
#include <stdlib.h>
#include <iostream>
#include <sstream>

/*! \defgroup exception_macros Exception Test/Catch Macros
 *
 * These macros are design to catch certain types of exceptions, print
 * out error messages with the file name and line where the exception
 * occurred and then exit the program.
 */

/*! Catch statement macro for catching of user specified exceptions
 * \ingroup exception_macros
 */
#define EXCEPTION_CATCH_AND_EXIT( Exception, msg ) \
  catch( const Exception &exception ) \
  {				      \
    std::ostringstream oss;	      \
    oss << " *** Caught " << #Exception << " Exception *** \n\n";	\
    oss << "File: " << __FILE__ << "\n";				\
    oss << "Line: " << __LINE__ << "\n";				\
    oss << msg << "\n";							\
    oss << " " << exception.what() << "\n";				\
    std::cerr << std::flush;						\
    std::cerr << oss.str();						\
    exit(EXIT_FAILURE);							\
  } 

/*! Catch macro for catching exceptions, adding error info, rethrowing
 * 
 * This macro should be used anywhere an exception is thrown in order to 
 * properly document the exception and add additional information to it before
 * throwing it again.
 * \ingroup exception_macros
 */
#define EXCEPTION_CATCH_RETHROW( Exception, msg ) \
catch( const Exception &exception )				\
{								\
  std::ostringstream detailed_msg;				\
  detailed_msg << __FILE__ << ":" << __LINE__ << ":\n\n"	\
	       << msg << "\n"					\
	       << exception.what() << "\n";			\
  throw Exception(detailed_msg.str());				\
}

/*! Catch macro for catching exceptions, adding error info, and rethrowing
 *
 * This macro should be used anywhere an exception is thrown in order to
 * properly document the exception and add additional information to it before
 * throwing it again. This macro should also be used when the exception to
 * throw is different than the caught exception.
 * \ingroup exception_macros
 */
#define EXCEPTION_CATCH_RETHROW_AS( ExceptionIn, ExceptionOut, msg )	\
catch( const ExceptionIn &exception )					\
{									\
  std::ostringstream detailed_msg;					\
  detailed_msg << __FILE__ << ":" << __LINE__ << ":\n\n"		\
               << msg << "\n"						\
               << exception.what() << "\n";				\
  throw ExceptionOut(detailed_msg.str());				\
}

/*! Catch statement macro for catching of user specified exceptions
 * \ingroup exception_macros
 */
#define EXCEPTION_CATCH( Exception, Exit, msg )	\
  catch( const Exception &exception ) \
  {				      \
    std::ostringstream oss;	      \
    oss << " *** Caught " << #Exception << " Exception *** \n\n";	\
    oss << "File: " << __FILE__ << "\n";				\
    oss << "Line: " << __LINE__ << "\n";				\
    oss << msg << "\n";							\
    oss << " " << exception.what() << "\n";				\
    if( Exit )								\
    {									\
      std::cerr << std::flush;						\
      std::cerr << oss.str();						\
      exit(EXIT_FAILURE);						\
    }									\
    else								\
      throw Exception(oss.str());					\
  } 

#endif // end GDEV_EXCEPTION_CATCH_MACROS_HPP

//---------------------------------------------------------------------------//
// end ExceptionCatchMacros.hpp
//---------------------------------------------------------------------------//
