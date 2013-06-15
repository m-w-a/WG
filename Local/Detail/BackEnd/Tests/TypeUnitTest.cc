#include <WG/Local/Detail/Tests/test.h>
#include <WG/Local/Detail/Tests/TestHelper.hh>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_reference.hpp>
#include "../Type.hh"

//Unit Tests.
#define S1 SomeGlobalType &
#define S2 local(SomeLocalType *)
#define S3 local(SomeLocalType *) (const)
#define S4 local(SomeLocalType *) (ref)
#define S5 local(SomeLocalType *) (const) (ref)

/*
WG_PP_PARSEDTYPE_EXTRACTCPPTYPE(S1)
WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_ADDREFERENCE(S1)
WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_ADDCONSTADDREFERENCE(S1)

WG_PP_PARSEDTYPE_LOCALTYPE_OPERAND(S2)
WG_PP_PARSEDTYPE_EXTRACTCPPTYPE(S2)
WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_ADDREFERENCE(S2)
WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_ADDCONSTADDREFERENCE(S2)

WG_PP_PARSEDTYPE_LOCALTYPE_OPERAND(S3)
WG_PP_PARSEDTYPE_EXTRACTCPPTYPE(S3)
WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_ADDREFERENCE(S3)
WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_ADDCONSTADDREFERENCE(S3)

WG_PP_PARSEDTYPE_LOCALTYPE_OPERAND(S4)
WG_PP_PARSEDTYPE_EXTRACTCPPTYPE(S4)
WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_ADDREFERENCE(S4)
WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_ADDCONSTADDREFERENCE(S4)

WG_PP_PARSEDTYPE_LOCALTYPE_OPERAND(S5)
WG_PP_PARSEDTYPE_EXTRACTCPPTYPE(S5)
WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_ADDREFERENCE(S5)
WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_ADDCONSTADDREFERENCE(S5)

//EXPECTED:
SomeGlobalType &
boost::add_reference<SomeGlobalType &>::type
boost::add_reference< boost::add_const<SomeGlobalType &>::type >::type

SomeLocalType *
SomeLocalType *
SomeLocalType * &
SomeLocalType * const &

SomeLocalType *
SomeLocalType * const
SomeLocalType * const &
SomeLocalType * const &

SomeLocalType *
SomeLocalType * &
SomeLocalType * &
SomeLocalType * &

SomeLocalType *
SomeLocalType * const &
SomeLocalType * const &
SomeLocalType * const &
*/

struct SomeGlobalType {};
void testGlobalType()
{
  using namespace boost;
  typedef SomeGlobalType & S1Type;

  WG_PP_TESTHELPER_IS_SAME_TYPE(
    S1Type, WG_PP_PARSEDTYPE_EXTRACTCPPTYPE(S1))

  WG_PP_TESTHELPER_IS_SAME_TYPE(
    add_reference<S1Type>::type, WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_ADDREFERENCE(S1))

  WG_PP_TESTHELPER_IS_SAME_TYPE(
    add_reference<add_const<S1Type>::type>::type,
    WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_ADDCONSTADDREFERENCE(S1))
}

void testLocalTypeNoQual()
{
  struct SomeLocalType {};
  typedef SomeLocalType * Operand;

  WG_PP_TESTHELPER_IS_SAME_TYPE(
    Operand, WG_PP_PARSEDTYPE_LOCALTYPE_OPERAND(S2))

  WG_PP_TESTHELPER_IS_SAME_TYPE(
    Operand, WG_PP_PARSEDTYPE_EXTRACTCPPTYPE(S2))

  WG_PP_TESTHELPER_IS_SAME_TYPE(
    Operand &, WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_ADDREFERENCE(S2))

  WG_PP_TESTHELPER_IS_SAME_TYPE(
    Operand const &, WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_ADDCONSTADDREFERENCE(S2))
}

void testLocalTypeConstQual()
{
  struct SomeLocalType {};
  typedef SomeLocalType * Operand;

  WG_PP_TESTHELPER_IS_SAME_TYPE(
    Operand, WG_PP_PARSEDTYPE_LOCALTYPE_OPERAND(S3))

  WG_PP_TESTHELPER_IS_SAME_TYPE(
    Operand const, WG_PP_PARSEDTYPE_EXTRACTCPPTYPE(S3))

  WG_PP_TESTHELPER_IS_SAME_TYPE(
    Operand const &, WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_ADDREFERENCE(S3))

  WG_PP_TESTHELPER_IS_SAME_TYPE(
    Operand const &, WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_ADDCONSTADDREFERENCE(S3))
}

void testLocalTypeRefQual()
{
  struct SomeLocalType {};
  typedef SomeLocalType * Operand;

  WG_PP_TESTHELPER_IS_SAME_TYPE(
    Operand, WG_PP_PARSEDTYPE_LOCALTYPE_OPERAND(S4))

  WG_PP_TESTHELPER_IS_SAME_TYPE(
    Operand &, WG_PP_PARSEDTYPE_EXTRACTCPPTYPE(S4))

  WG_PP_TESTHELPER_IS_SAME_TYPE(
    Operand &, WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_ADDREFERENCE(S4))

  WG_PP_TESTHELPER_IS_SAME_TYPE(
    Operand &, WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_ADDCONSTADDREFERENCE(S4))
}

void testLocalTypeConstRefQual()
{
  struct SomeLocalType {};
  typedef SomeLocalType * Operand;

  WG_PP_TESTHELPER_IS_SAME_TYPE(
    Operand, WG_PP_PARSEDTYPE_LOCALTYPE_OPERAND(S5))

  WG_PP_TESTHELPER_IS_SAME_TYPE(
    Operand const &, WG_PP_PARSEDTYPE_EXTRACTCPPTYPE(S5))

  WG_PP_TESTHELPER_IS_SAME_TYPE(
    Operand const &, WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_ADDREFERENCE(S5))

  WG_PP_TESTHELPER_IS_SAME_TYPE(
    Operand const &, WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_ADDCONSTADDREFERENCE(S5))
}
