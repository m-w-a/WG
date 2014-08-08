#ifndef WG_LOCAL_DETAIL_AUTOSIMULATOR_TESTS_UTILS_HH_
#define WG_LOCAL_DETAIL_AUTOSIMULATOR_TESTS_UTILS_HH_

namespace wg
{
namespace autosimulator
{
namespace detail
{
namespace test
{

template <typename T>
bool isConstLValue(T &)
{
  return false;
}

template <typename T>
bool isConstLValue(T const &)
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

  template <typename ExprType>
  struct ArrayExpr : private CallCountVerifier
  {
    ArrayExpr & operator=(A5 const & rhs)
    { std::copy(rhs, rhs + ArrayCount, m_Value); return *this; }
    ExprType & operator()() { this->verifyEvalCount(); return m_Value;  }
  private:
    A5 m_Value;
  };

  template <typename ExprType>
  struct NonArrayExpr : private CallCountVerifier
  {
    ExprType operator()() { this->verifyEvalCount(); return m_Value; }
  private:
    Cntr m_Value;
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
};


}
}
}
}

#endif /* WG_LOCAL_DETAIL_AUTOSIMULATOR_TESTS_UTILS_HH_ */
