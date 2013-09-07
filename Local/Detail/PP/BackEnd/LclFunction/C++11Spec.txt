#include <iostream>

#include <boost/tuple/tuple.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/function_types/result_type.hpp>
#include <boost/function_types/parameter_types.hpp>
#include <boost/function_types/function_pointer.hpp>
#include <boost/function_types/function_arity.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/int.hpp>

namespace wg
{
namespace lclfunction
{
namespace detail
{
namespace cpp11
{

// FUNCTOR: The local functor type (C++11).
// LCLFUNCTION: The specified local function type.
// CAPTUREDVARS: A tuple of captured local variables, if any.
template<
  typename FUNCTOR, 
  typename LCLFUNCTION, 
  typename CAPTUREDVARS>
class base_functor_type
{
public:
  typedef FUNCTOR functor_type;
  typedef LCLFUNCTION local_function_type;
  typedef CAPTUREDVARS captured_types;
  
private:
  // Synthesize the call back type. It's prototype should be:
  // 
  //   typedef typename result_type<LCLFUNCTION>::type (*callback_type)( 
  //   base_functor_type const &, param_types<LCLFUNCTION>, CAPTUREDVARS &);
  typedef 
    typename boost::mpl::push_back
    <
      typename boost::mpl::push_front
      <
        typename boost::mpl::push_front
        <
          boost::function_types::parameter_types<local_function_type>,
          //const issue.
          base_functor_type const &
        >::type,
        typename boost::function_types::result_type<local_function_type>::type
      >::type,
      typename boost::add_reference<captured_types>::type
    >::type mpl_callback_type;

public:
  typedef 
    typename boost::function_types::function_pointer<mpl_callback_type>::type
      callback_type;

public:
  explicit base_functor_type(captured_types const & vars)
  : m_CapturedVars(vars)
  {}
  
  typedef
    typename boost::function_types::result_type<local_function_type>::type
      result_type;
  
  typedef 
    boost::function_types::parameter_types<local_function_type>
      parameter_types;
  
  static int const arity = 
    boost::function_types::function_arity<local_function_type>::value;
  
  //--------------------------------------------------------------------------//
  // PP generate operator() methods up to WG_PP_LCLFUNCTION_MAX_ARGS params.
  // add_const add_ref params until very end.
  // Method const so as to be able to be called by const std::function.
  //--------------------------------------------------------------------------//
  
  result_type operator()() const
  {
    BOOST_STATIC_ASSERT((base_functor_type::arity == 0));
    return functor_type::user_callback(*this, m_CapturedVars);
  }
  
 /* int operator()(int const & arg0, int const & arg1) const */
  result_type operator()(
    typename boost::add_reference
    <
      typename boost::add_const
      <
        typename boost::mpl::at<parameter_types, boost::mpl::int_<0> >::type
      >::type
    >::type arg0,
    typename boost::add_reference
    <
      typename boost::add_const
      <
        typename boost::mpl::at<parameter_types, boost::mpl::int_<1> >::type
      >::type
    >::type arg1) const
  {
    BOOST_STATIC_ASSERT((base_functor_type::arity == 2));
    return functor_type::user_callback(*this, arg0, arg1, m_CapturedVars);
  }

private:
  // Captured vars are mutable because their mutability is determined at the 
  // point of their capture, and not by class methods.
  mutable captured_types m_CapturedVars;
};

}
}
}
}

int main()
{
  int slope = 2;

#define LOCAL_FUNCTION_NAME() lin
#define RETURN_TYPE() int
#define PARAMS_NTUPLE() (int const &, int const &)
  //Declare functor.
  //PP iterator over captured vars.
  //Expands to:
  
  struct local_functor_typeXXX128;
  typedef RETURN_TYPE()(local_function_typeXXX128)PARAMS_NTUPLE() ;
  /*--PP iterator over captured vars for template params.*/
  typedef boost::tuple<int const &> captured_typesXXX128;

  typedef wg::lclfunction::detail::cpp11::base_functor_type
  <
    local_functor_typeXXX128,
    local_function_typeXXX128, 
    captured_typesXXX128
  > functor_typeXXX128;
  
  /* Note: double parenthesis around ctor param to prevent most vexing parse
     error. */
  /*--PP iterator over captured vars for both template params and ctor 
      params.*/
  functor_typeXXX128 
    LOCAL_FUNCTION_NAME()(( boost::tuple<int const &>(slope) ));
    
  struct local_functor_typeXXX128
  {
    typedef functor_typeXXX128 functor_type;
    
    /* This functions prototype should match functor_type::callback_type. */
    static int user_callback(
      functor_type const & LOCAL_FUNCTION_NAME(), 
      int const & x, 
      int const & y, 
      captured_typesXXX128 & capturedvars)
    {
      /* To avoid unused var warnings. */
      (void)(LOCAL_FUNCTION_NAME());
      
      int const & slope(capturedvars.get<0>());
      
      /* User provided definition.*/
      {
        return x + slope * y;
      }
    }
  };

//  std::cout << lin() << std::endl;
  std::cout << lin(1,2) << std::endl;
  
  return 0;
}