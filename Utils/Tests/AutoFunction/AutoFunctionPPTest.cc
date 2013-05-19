//******************************************************************************
//Note: this file is not meant to be compiled.
//  It is to be used for preprocessing tests only.
//******************************************************************************

#include <boost/preprocessor.hpp>
//#include <WG/Utils/AutoFunction.hh>
#include <WG/Utils/AutoFunction2.hh>
//#include <boost/type_traits/add_const.hpp>
//#include <boost/type_traits/add_reference.hpp>
//#include <boost/local_function.hpp>
//TESTS Begin

#define TEST_SEQ (w)(x) (y)(z) (a)(b) (c)(d) (class)(this_)
#define ASEQ (T1)(t, foo.bar) (T2)(q, this->foo())
#define HUH (int)(age) (char)(c)
#define WTF (w)(x)

//WG_AUTOFUNCTION(foo, TEST_SEQ, ASEQ)
//{
//}
//WG_AUTOFUNCTION_END;

int main()
{
/*
  WG_AUTOFUNCTION(noParamsArg, (void), (void))
  {
  }WG_AUTOFUNCTION_END;
//  __LINE__
*/
//  #define spec foo
//  WG_PP_AUTOFUNCTION_SPEC_PROCESSIFHEAD_ASSIGNTO(spec)

#define EAT_assignto
#define EAT_return
#define EAT_parambind

#define EAT_HEAD(spec) \
  BOOST_PP_CAT(EAT_, spec)
/*
// Process spec if it's head token matches currentkeyword by passing control to
//  WG_PP_AUTOFUNCTION_PROCESSIMPL_<CURRENTKEYWORD>,
// else call WG_PP_AUTOFUNCTION_SPEC_PROCESSIFHEAD_<NEXTKEYWORD>
#define WG_PP_AUTOFUNCTION_SPEC_PROCESSIFHEAD( \
  spec, currentkeyword, nextkeyword) \
    BOOST_PP_IIF( \
      BOOST_PP_CAT(WG_PP_TOKENS_STARTS_WITH_, currentkeyword) (spec), \
      BOOST_PP_CAT(WG_PP_AUTOFUNCTION_PROCESSIMPL_, currentkeyword) \
        (spec) \
        WG_PP_AUTOFUNCTION_SPEC_TRAILINGTOKENS BOOST_PP_EMPTY, \
      WG_PP_AUTOFUNCTION_SPEC_LEADINGTOKENS \
        BOOST_PP_CAT( \
          WG_PP_AUTOFUNCTION_SPEC_PROCESSIFHEAD_, \
          nextkeyword) BOOST_PP_EMPTY)() (spec)

#define WG_PP_AUTOFUNCTION_SPEC_PROCESSIFHEAD_ASSIGNTO(spec) \
  WG_PP_AUTOFUNCTION_SPEC_PROCESSIFHEAD(spec, ASSIGNTO, RETURN)
#define WG_PP_AUTOFUNCTION_PROCESSIMPL_ASSIGNTO(spec) \
  (assignto) \
  BOOST_PP_CAT(WG_PP_AUTOFUNCTION_SPEC_PROCESSIFHEAD_, RETURN)\
    ( EAT_HEAD(spec) )

#define WG_PP_AUTOFUNCTION_SPEC_PROCESSIFHEAD_RETURN(spec) \
  WG_PP_AUTOFUNCTION_SPEC_PROCESSIFHEAD(spec, RETURN, PARAMBIND)
#define WG_PP_AUTOFUNCTION_PROCESSIMPL_RETURN(spec) \
  (return)
//  BOOST_PP_CAT(WG_PP_AUTOFUNCTION_SPEC_PROCESSIFHEAD_, PARAMBIND) \
    ( EAT_HEAD(spec) )
*/

// Process spec if it's head token matches currentkeyword by passing control to
//  WG_PP_AUTOFUNCTION_PROCESSIMPL_<CURRENTKEYWORD>,
// else call WG_PP_AUTOFUNCTION_SPEC_PROCESSIFHEAD_<NEXTKEYWORD>
#define WG_PP_AUTOFUNCTION_SPEC_PROCESSIFHEAD( \
  spec, currentkeyword, nextkeyword) \
    BOOST_PP_IIF( \
      BOOST_PP_CAT(WG_PP_TOKENS_STARTS_WITH_, currentkeyword) (spec), \
      BOOST_PP_CAT(WG_PP_AUTOFUNCTION_PROCESSIMPL_, currentkeyword), \
      BOOST_PP_CAT(WG_PP_AUTOFUNCTION_SPEC_PROCESSIFHEAD_, nextkeyword)) \
    BOOST_PP_LPAREN() \
      BOOST_PP_SEQ_ENUM( \
        BOOST_PP_IIF( \
          BOOST_PP_CAT(WG_PP_TOKENS_STARTS_WITH_, currentkeyword) (spec), \
          (spec), \
          (spec) )) \
    BOOST_PP_RPAREN()

#define WG_PP_AUTOFUNCTION_SPEC_PROCESSIFHEAD_ASSIGNTO(spec) \
  WG_PP_AUTOFUNCTION_SPEC_PROCESSIFHEAD \
  BOOST_PP_LPAREN() spec, ASSIGNTO, RETURN BOOST_PP_RPAREN()
#define WG_PP_AUTOFUNCTION_PROCESSIMPL_ASSIGNTO(spec) \
  (assignto) \
  BOOST_PP_CAT(WG_PP_AUTOFUNCTION_SPEC_PROCESSIFHEAD_, RETURN)\
  BOOST_PP_LPAREN() EAT_HEAD(spec) BOOST_PP_RPAREN()

#define WG_PP_AUTOFUNCTION_SPEC_PROCESSIFHEAD_RETURN(spec) \
  WG_PP_AUTOFUNCTION_SPEC_PROCESSIFHEAD \
  BOOST_PP_LPAREN() spec, RETURN, PARAMBIND BOOST_PP_RPAREN()
#define WG_PP_AUTOFUNCTION_PROCESSIMPL_RETURN(spec) \
  (return) \
  BOOST_PP_CAT(WG_PP_AUTOFUNCTION_SPEC_PROCESSIFHEAD_, PARAMBIND) \
    BOOST_PP_LPAREN() EAT_HEAD(spec) BOOST_PP_RPAREN()

#define WG_PP_AUTOFUNCTION_SPEC_PROCESSIFHEAD_PARAMBIND(spec) \
  WG_PP_AUTOFUNCTION_SPEC_PROCESSIFHEAD \
  BOOST_PP_LPAREN() spec, PARAMBIND, PARAMSET BOOST_PP_RPAREN()
#define WG_PP_AUTOFUNCTION_PROCESSIMPL_PARAMBIND(spec) \
  (parambind)
    
#define spec assignto return parambind
BOOST_PP_EXPAND(BOOST_PP_EXPAND(BOOST_PP_EXPAND(BOOST_PP_EXPAND( \
  WG_PP_AUTOFUNCTION_SPEC_PROCESSIFHEAD_ASSIGNTO(spec) \
))))
//WG_PP_AUTOFUNCTION_SPEC_PROCESSIFHEAD(return, RETURN, PARAMBIND)

  
#define FOO(x) x a
//FOO(BOOST_PP_CAT(FO, O)(z))

#define A(y) y B BOOST_PP_LPAREN() y BOOST_PP_RPAREN()
#define B(x) A BOOST_PP_LPAREN() x BOOST_PP_RPAREN()

// A(1)     // B
// BOOST_PP_EXPAND( A(1)(2) )   // A
// BOOST_PP_EXPAND( BOOST_PP_EXPAND( A(1)(2) ) (3) ) // B 
// BOOST_PP_EXPAND( BOOST_PP_EXPAND( BOOST_PP_EXPAND( A(1)(2) ) (3) ) (4)) // B
  
// A(1)
// BOOST_PP_EXPAND( A(1) )
// BOOST_PP_EXPAND( BOOST_PP_EXPAND( A(1) ) )
  
  // #define TRAILING_TOKENS BOOST_PP_EMPTY BOOST_PP_COMMA
  
  // #define PROCESS_LEADINGTOKENS_NOLEADINGTOKENS
  // #define PROCESS_LEADINGTOKENS_LEADINGTOKENS BOOST_PP_EMPTY BOOST_PP_COMMA()
  
  // #define TRAILING_TOKENS_PROCESS_TRAILING_TOKENS TRAILING_TOKENS()
  
  // #define seq LEADINGTOKENS (a)(b)(c)(d) TRAILING_TOKENS
  // BOOST_PP_CAT( \
    // PROCESS_LEADINGTOKENS_, \
    // seq)
  
/*
  WG_AUTOFUNCTION(oneBoundArg, (bool)(didArgumentBind) (int)(y2), (void))
  {
  } WG_AUTOFUNCTION_END;
//  __LINE__

  WG_AUTOFUNCTION(oneAssignedArg, (void), (int)(age, 10))
  {
  } WG_AUTOFUNCTION_END;
//  __LINE__

  WG_AUTOFUNCTION(
    generalAutoFunction, 
    (bool)(didArgumentBind), 
    (int)(age, 10))
  {
  } WG_AUTOFUNCTION_END;
//  __LINE__
  
  WG_AUTOFUNCTION(keywordBoundArg, (MyClass)(this_), (void))
  {
  }WG_AUTOFUNCTION_END;
//  __LINE__
*/

  return 0;
}

