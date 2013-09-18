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
// Needed for the definition of WG_PP_LCLFUNCTION_MAX_ARGS.
#include <WG/Local/LclFunction.hh>

#include <boost/tuple/tuple.hpp>
#include <WG/Local/Detail/LclFunction/BaseFunctorTypeCPP11.hh>

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
#define PARAMS_NTUPLE() (int const &, int const &)
#define CAPTURED_VAR_TYPE1 int const &
  //Expands to:
  
  /*PP iterator over captured vars for template params. */
  typedef boost::tuple<CAPTURED_VAR_TYPE1> captured_var_typesXXX128;
  typedef RETURN_TYPE()(local_function_typeXXX128)PARAMS_NTUPLE() ;

  struct local_functor_typeXXX128;
  typedef wg::lclfunction::detail::cpp11::base_functor_type
  <
    local_functor_typeXXX128,
    local_function_typeXXX128, 
    captured_var_typesXXX128
  > base_functor_typeXXX128;
  
  /* Note: double parenthesis around ctor param to prevent most vexing parse
     error. */
  /*--PP iterator over captured vars for both template params and ctor 
      params.*/
  base_functor_typeXXX128
    LOCAL_FUNCTION_NAME()(( captured_var_typesXXX128(slope) ));
    
  struct local_functor_typeXXX128
  {
    typedef captured_var_typesXXX128 captured_var_types;
    typedef base_functor_typeXXX128 base_functor_type;
    
    /* This functions prototype should match base_functor_type::callback_type. */
    static int user_callback(
      base_functor_type const & LOCAL_FUNCTION_NAME(),
      int const & x, 
      int const & y, 
      captured_var_types & capturedvars)
    {
      /* To avoid unused var warnings. */
      (void)(LOCAL_FUNCTION_NAME());
      
      boost::tuples::element<0, captured_var_types>::type
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
