#ifndef WG_LOCAL_TEST_TRILEAN_HH_
#define WG_LOCAL_TEST_TRILEAN_HH_

namespace wg
{
namespace lcl
{
namespace test
{

// Prefer this over Boost.Tribool.
// Rationale:
//   Use of Boost.Tribool makes for hard to understand to code. Consider:
//
//   tribool b = indeterminate;
//   if(b)
//   {
//   }
//   else
//   {
//   }
//
//   In the else clause it's reasonable to expect that "b == false", but that's
//   not the case. This has to do with trying to treat a tri-valued logical
//   variable as a boolean variable, and that, IMHO, is a fundamental flaw, it
//   leads to hard to understand code.

class Trilean
{
public:
  friend bool operator==(Trilean const & lhs, Trilean const & rhs)
  {
    return lhs.m_Value == rhs.m_Value;
  }

  friend bool operator!=(Trilean const & lhs, Trilean const & rhs)
  {
    return lhs.m_Value != rhs.m_Value;
  }

public:
  enum Kind
  {
    Undefined,
    True,
    False
  };

  Trilean()
  : m_Value(Undefined)
  {}

  Trilean(Kind const kind)
  : m_Value(kind)
  {}

private:
  Kind m_Value;
};

}
}
}

#endif /* WG_LOCAL_TEST_TRILEAN_HH_ */
