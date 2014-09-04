#ifndef WG_LOCAL_DETAIL_AUTOSIMULATOR_TESTS_UTILS_HH_
#define WG_LOCAL_DETAIL_AUTOSIMULATOR_TESTS_UTILS_HH_

#include <algorithm>
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

  struct CopyOnlyCntr
  {
    CopyOnlyCntr() : value(11) {}
    CopyOnlyCntr(CopyOnlyCntr const & rhs) : value(rhs.value) {}
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

  struct CopyMoveCntr
  {
    friend void swap(CopyMoveCntr & lhs, CopyMoveCntr & rhs)
    { using std::swap; swap(lhs.value, rhs.value); }

    CopyMoveCntr() : value(345) {}
    CopyMoveCntr(CopyMoveCntr const & rhs) : value(rhs.value) {}
    CopyMoveCntr(BOOST_RV_REF(CopyMoveCntr) rhs) : value(rhs.value) {}
    CopyMoveCntr & operator=(CopyMoveCntr rhs) { swap(*this, rhs); return *this; }
    int value;
  private:
    BOOST_COPYABLE_AND_MOVABLE(CopyMoveCntr)
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

  template <typename ExprType, typename DummyArg = void>
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

  template <typename DummyArg>
  struct NonArrayExpr<MoveOnlyCntr, DummyArg> : private CallCountVerifier
  {
    MoveOnlyCntr operator()()
    { this->verifyEvalCount(); return MoveOnlyCntr(); }
  };

  template <typename DummyArg>
  struct NonArrayExpr<MoveOnlyCntr const, DummyArg> : private CallCountVerifier
  {
    MoveOnlyCntr const operator()()
    { this->verifyEvalCount(); return MoveOnlyCntr(); }
  };

  ExprGenerator()
  {
    A5 arr = {0, 1, 2, 3, 4};
    ConstA5 carr = {10, 11, 12, 13, 14};
    mutableArray = arr;
    constArray = carr;
  }

  ArrayExpr<A5>             mutableArray;
  ArrayExpr<ConstA5>        constArray;

  NonArrayExpr<CopyOnlyCntr>        copyonlyMutableRValue;
  NonArrayExpr<CopyOnlyCntr const>  copyonlyConstRValue;
  NonArrayExpr<CopyOnlyCntr &>      copyonlyMutableLValue;
  NonArrayExpr<CopyOnlyCntr const &> copyonlyConstLValue;

  NonArrayExpr<MoveOnlyCntr>        moveonlyMutableRValue;
  // Commented out because noncopyable const rvalues can't be used with this lib.
  //NonArrayExpr<MoveOnlyCntr const>  moveonlyConstRValue;
  NonArrayExpr<MoveOnlyCntr &>      moveonlyMutableLValue;
  NonArrayExpr<MoveOnlyCntr const &> moveonlyConstLValue;

  NonArrayExpr<CopyMoveCntr>        copymoveMutableRValue;
  NonArrayExpr<CopyMoveCntr const>  copymoveConstRValue;
  NonArrayExpr<CopyMoveCntr &>      copymoveMutableLValue;
  NonArrayExpr<CopyMoveCntr const &> copymoveConstLValue;
};


}
}
}
}

#endif /* WG_LOCAL_DETAIL_AUTOSIMULATOR_TESTS_UTILS_HH_ */
