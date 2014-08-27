#ifndef WG_LOCAL_DETAIL_AUTOSIMULATOR_TESTS_UTILS_HH_
#define WG_LOCAL_DETAIL_AUTOSIMULATOR_TESTS_UTILS_HH_

#include <gtest/gtest.h>
#include <boost/move/core.hpp>
#include <boost/move/utility.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_object.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_reference.hpp>

namespace wg
{
namespace autosimulator
{
namespace detail
{
namespace test
{

template <typename T>
bool isConst(T &)
{
  return false;
}

template <typename T>
bool isConst(T const &)
{
  return true;
}

class ExprGenerator
{
private:
  struct CallCountVerifier
  {
    CallCountVerifier() : m_CallCount(0) {}
    void verifyEvalCount() { EXPECT_EQ(0, m_CallCount); ++m_CallCount; }
  private:
    unsigned int m_CallCount;
  };

public:
  enum { ArrayCount = 5 };
  typedef int A5[ArrayCount];
  typedef A5 const ConstA5;

  struct Cntr
  {
    Cntr() : value(11) {}
    int value;
  };

  struct MoveOnlyCntr
  {
    MoveOnlyCntr() : value(121) {}
    MoveOnlyCntr(BOOST_RV_REF(MoveOnlyCntr) rhs) : value(rhs.value) {}
    int value;
  private:
    BOOST_MOVABLE_BUT_NOT_COPYABLE(MoveOnlyCntr)
  };

  template <typename ExprType>
  struct ArrayExpr : private CallCountVerifier
  {
    ArrayExpr & operator=(A5 const & rhs)
    { std::copy(rhs, rhs + ArrayCount, m_Value); return *this; }
    ExprType & operator()() { this->verifyEvalCount(); return m_Value;  }
  private:
    A5 m_Value;
  };

  struct CopyableTag {};
  struct MoveOnlyTag {};

  template
  <
    typename ExprType,
    typename Cloneability = CopyableTag,
    typename EnableIfDummyArg = void
  >
  struct NonArrayExpr : private CallCountVerifier
  {
    ExprType operator()() { this->verifyEvalCount(); return m_Value; }
  private:
    typedef
      typename ::boost::remove_const
       <
         typename ::boost::remove_reference<ExprType>::type
       >::type  ValueType;
  private:
    ValueType m_Value;
  };

  template <typename ExprType>
  struct NonArrayExpr
  <
    ExprType,
    MoveOnlyTag,
    typename  ::boost::enable_if< ::boost::is_object<ExprType> >::type
  > : private CallCountVerifier
  {
    ExprType operator()() { this->verifyEvalCount(); return MoveOnlyCntr(); }
  };

  ExprGenerator()
  {
    A5 arr = {0, 1, 2, 3, 4};
    ConstA5 carr = {10, 11, 12, 13, 14};
    array = arr;
    constArray = carr;
  }

  ArrayExpr<A5>             array;
  ArrayExpr<ConstA5>        constArray;

  NonArrayExpr<Cntr>        mutableRValue;
  NonArrayExpr<Cntr const>  constRValue;
  NonArrayExpr<Cntr &>      mutableLValue;
  NonArrayExpr<Cntr const &> constLValue;

  NonArrayExpr<MoveOnlyCntr, MoveOnlyTag>        moveonlyMutableRValue;
  NonArrayExpr<MoveOnlyCntr const, MoveOnlyTag>  moveonlyConstRValue;
  NonArrayExpr<MoveOnlyCntr &, MoveOnlyTag>      moveonlyMutableLValue;
  NonArrayExpr<MoveOnlyCntr const &, MoveOnlyTag> moveonlyConstLValue;
};


}
}
}
}

#endif /* WG_LOCAL_DETAIL_AUTOSIMULATOR_TESTS_UTILS_HH_ */
