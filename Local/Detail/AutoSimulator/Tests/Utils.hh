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

}
}
}
}

#endif /* WG_LOCAL_DETAIL_AUTOSIMULATOR_TESTS_UTILS_HH_ */
