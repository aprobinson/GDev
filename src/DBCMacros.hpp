//---------------------------------------------------------------------------//
//!
//! \file   DBCMacros.hpp
//! \author Alex Robinson
//! \brief  Design-by-Contract macros
//!
//---------------------------------------------------------------------------//

#ifndef GDEV_DBC_MACROS_HPP
#define GDEV_DBC_MACROS_HPP

// Boost Includes
#include <boost/static_assert.hpp>
#include <boost/type_traits.hpp>
#include <boost/mpl/int.hpp>

// FRENSIE Includes
#include "GDev_dbc_config.hpp"
#include "ContractException.hpp"
#include "ExceptionTestMacros.hpp"
#include "ExceptionCatchMacros.hpp"

/*! \defgroup contract_exceptions_macros Design-By-Contract Exceptions and Macros
 *
 * Design-By-Contract is a powerful way to ensure that certain function
 * preconditions and postconditions are explicit. When Design-By-Contract
 * functionality is enabled, the program will exit whenever one of these
 * conditions is not met. This functionality is made possible through a series
 * of macros and an exception class.
 */

#if HAVE_GDev_DBC

/*! Test a function precondition
 * \ingroup contract_exceptions_macros 
 */
#define testPrecondition(c)						\
  TEST_FOR_EXCEPTION( !(c),						\
		      GDev::ContractException,			\
		      "Precondition exception" << std::endl ) 

/*! Test a function postcondition
 * \ingroup contract_exceptions_macros
 */
#define testPostcondition(c)					\
  TEST_FOR_EXCEPTION( !(c),					\
		      GDev::ContractException,		\
		      "Postcondition exception" << std::endl ) 

/*! Test a function invariant
 * \ingroup contract_exceptions_macros
 */
#define testInvariant(c)						\
  TEST_FOR_EXCEPTION( !(c),						\
		      GDev::ContractException,			\
		      "Invariant exception" << std::endl )

/*! Test all nested conditions
 * \details This should be placed around any function call that implements
 * DBC. It can be used to create what is essentially a stacktrace. 
 * 
 * \ingroup contract_exceptions_macros
 */
#define testNestedConditions(c)				\
  try{							\
    c;							\
  }							\
  EXCEPTION_CATCH_RETHROW( GDev::ContractException,	\
			   "Nested condition violated" << std::endl )

/*! Test all nested conditions in a block
 * \details This should be placed at the beginning of a block where all
 * functions implementing DBC are to be checked for DBC violations. It
 * must be paired with the testNestedConditionsBlockEnd macro. This macro in
 * combination with the testNestedConditionsEnd macro can be used to
 * create what is essentially a stacktrace.
 *
 * \ingroup contract_exceptions_macros
 */
#define testNestedConditionsBegin(depth)		\
  try{							\
  typedef boost::mpl::int_<depth> __NESTED_CONDITION_DEPTH_CHECK__

/*! Test all nested conditions in a block
 * \details This should be at the end of a block where all functions
 * implementing DBC are to be checked for DBC violations. It must be paired
 * with the testNestedConditionsBlockBegin macro. This macro in combination
 * with the testNestedConditionsBlockBegin macro can be used to create
 * what is essentiall a stacktrace.
 * \ingroup contract_exceptions_macros
 */
#define testNestedConditionsEnd(depth)				\
  BOOST_STATIC_ASSERT( (boost::is_same<__NESTED_CONDITION_DEPTH_CHECK__,boost::mpl::int_<depth> >::value) ); \
  }								\
  EXCEPTION_CATCH_RETHROW( GDev::ContractException,		\
			   "Nested condition violated" << std::endl )
  
/*! Remember a variable, typedef, etc. that is needed for DBC testing
 * \ingroup contract_exceptions_macros
 */
#define remember(...) __VA_ARGS__

#else
			      
#define testPrecondition(c)
#define testPostcondition(c)
#define testInvariant(c)
#define testNestedConditions(c)
#define testNestedConditionsBegin(depth)
#define testNestedConditionsEnd(depth)
#define remember(...)

#endif // end HAVE_GDev_DBC

/*! test a templated function static precondition
 * \ingroup contract_exceptions_macros
 */
#define testStaticPrecondition(c) \
  BOOST_STATIC_ASSERT( (c) )

#endif // end GDEV_DBC_MACROS_HPP

//---------------------------------------------------------------------------//
// end DBCMacros.hpp
//---------------------------------------------------------------------------//
