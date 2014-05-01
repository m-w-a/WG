//***************************//
// START: Not part of the spec.
//***************************//
#include <gtest/gtest.h>

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
//**************************//
// End: Not part of the spec.
//**************************//

// Not part of the spec.
// Needed for the definition of WG_PP_LCLFUNCTION_CONFIG_PARAMS_MAX_ARITY.
#include <WG/Local/LclFunction.hh>

#include <boost/tuple/tuple.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <WG/Local/Detail/LclFunction/GlobalFunctorTypeCPP11.hh>

TEST(wg_lclfunction_codegenspec, cpp11)
{
  int slope = 2;

  //Declare functor.
  //
  //WG_LCLFUNCTION
  //(lin,
  //  return (int)
  //  params (int const & x, int const & y)
  //  varbind (const ref slope) )
  //{
  //  return x + slope * y;
  //}
  //WG_LCLFUNCTION_END;
#define LOCAL_FUNCTION_NAME() lin
#define RETURN_TYPE() int
#define PARAMS_LIST() int const &, int const &
#define CAPTURED_VAR_TYPE1 int const &
  //Expands to:
  
  /*PP iterator over captured vars for template params. */
  typedef ::boost::tuple<CAPTURED_VAR_TYPE1> captured_vars_typeXXX128;

  struct local_functor_typeXXX128;
  typedef wg::lclfunction::detail::cpp11::global_functor_type
  <
    local_functor_typeXXX128,
    RETURN_TYPE() ( PARAMS_LIST() ),
    captured_vars_typeXXX128
  > global_functor_typeXXX128;
  
  /* Note: double parenthesis around ctor param to prevent most vexing parse
     error. */
  /*--PP iterator over captured vars for both template params and ctor 
      params.*/
  global_functor_typeXXX128
    LOCAL_FUNCTION_NAME()(( captured_vars_typeXXX128(slope) ));
    
  struct local_functor_typeXXX128
  {
    typedef captured_vars_typeXXX128 captured_vars_type;
    typedef global_functor_typeXXX128 global_functor_type;
    
    /* This functions prototype should match global_functor_type::callback_type. */
    static int user_callback(
      global_functor_type const & LOCAL_FUNCTION_NAME(),
      int const & x, 
      int const & y, 
      captured_vars_type & capturedvars)
    {
      /* To avoid unused var warnings. */
      (void)(LOCAL_FUNCTION_NAME());
      
      ::boost::add_reference
      <
        ::boost::tuples::element<0, captured_vars_type>::type
      >::type
        slope(capturedvars.get<0>());
      
      /* User provided definition.*/
      {
        return x + slope * y;
      }
    }
  };
  
  //***************************//
  // START: Not part of the spec.
  //***************************//
  #ifndef EXPECT_EQ
    #define EXPECT_EQ(expected, actual)
  #endif
  EXPECT_EQ(5, lin(1,2));
  //***************************//
  // END: Not part of the spec.
  //***************************//
}
