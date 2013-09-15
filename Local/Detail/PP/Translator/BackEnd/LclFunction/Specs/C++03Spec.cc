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
#include <WG/Local/Detail/LclFunction/BaseFunctorTypeCPP03.hh>

TEST(wg_lclfunction_codegenspec, cpp03)
{
  int slope = 2;

#define LOCAL_FUNCTION_NAME() lin
#define RETURN_TYPE() int
#define PARAMS_NTUPLE() (int const &, int const &)
  //Declare functor.
  //PP iterator over captured vars.
  //Expands to:
  wg::lclfunction::detail::base_functor_type
  <
    RETURN_TYPE()PARAMS_NTUPLE(),
    boost::tuple<int const &>
    /* Note: double parenthesis around ctor param to prevent most vexing parse
       error. */
    /*--PP iterator over captured vars for both template params and ctor 
        params.*/
  > LOCAL_FUNCTION_NAME()(( boost::tuple<int const &>(slope) ));
  {
    typedef RETURN_TYPE()(local_function_type)PARAMS_NTUPLE() ;
    /*--PP iterator over captured vars for template params.*/
    typedef boost::tuple<int const &> captured_types;
  
    typedef wg::lclfunction::detail::base_functor_type
    <
      local_function_type, 
      captured_types
    > functor_type;
  
    /*--Don't FORGET the REFERENCE!!!!!*/
    functor_type & functor = LOCAL_FUNCTION_NAME();
    
    struct local_functor_type
    {
      void set_caller(functor_type & functor)
      {
        functor.set_caller(&local_functor_type::user_callback);
      }
    
    private:
      /* This functions prototype should match functor_type::callback_type. */
      static int user_callback(
        functor_type const & LOCAL_FUNCTION_NAME(), 
        int const & x, 
        int const & y, 
        captured_types & capturedvars)
      {
        /* To avoid unused var warnings. */
        (void)(LOCAL_FUNCTION_NAME());
        
        int const & slope(capturedvars.get<0>());
        
        /* User provided definition.*/
        {
          return x + slope * y;
        }
      }
#define LOCAL_OBJ_NAME() local_functor
    } LOCAL_OBJ_NAME() ;
    LOCAL_OBJ_NAME() .set_caller(functor);
  }
  
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