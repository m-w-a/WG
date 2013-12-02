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
#include <boost/type_traits/add_reference.hpp>
#include <WG/Local/Detail/LclFunction/GlobalFunctorTypeCPP03.hh>

TEST(wg_lclfunction_codegenspec, cpp03)
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

  /* PP iterator over captured var types for template params. */
  typedef boost::tuple<CAPTURED_VAR_TYPE1> captured_vars_typeXXX32;

  typedef wg::lclfunction::detail::global_functor_type
  <
    RETURN_TYPE(),
    boost::mpl::vector<PARAMS_LIST()>,
    captured_vars_typeXXX32
  > global_functor_typeXXX32;
  /* Note: double parenthesis around ctor param to prevent most vexing parse
     error. */
  /* PP iterator over captured vars for ctor params. */
  global_functor_typeXXX32
    LOCAL_FUNCTION_NAME()(( captured_vars_typeXXX32(slope) ));
  {
    /* Don't FORGET the REFERENCE!!!!! */
    global_functor_typeXXX32 & functor = LOCAL_FUNCTION_NAME();
    
    struct local_functor_type
    {
      typedef captured_vars_typeXXX32 captured_vars_type;
      typedef global_functor_typeXXX32 global_functor_type;

      void set_caller(global_functor_type & functor)
      {
        functor.set_caller(&local_functor_type::user_callback);
      }
    
    private:
      /* This functions prototype should match global_functor_type::callback_type. */
      static int user_callback(
        global_functor_type const & LOCAL_FUNCTION_NAME(),
        int const & x, 
        int const & y, 
        captured_vars_type & capturedvars)
      {
        /* To avoid unused var warnings. */
        (void)(LOCAL_FUNCTION_NAME());
        
        boost::add_reference
        <
          boost::tuples::element<0, captured_vars_type>::type
        >::type
          slope(capturedvars.get<0>());
        
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
