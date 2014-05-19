#ifndef WG_LOCAL_DETAIL_BINDER_HH_
#define WG_LOCAL_DETAIL_BINDER_HH_

#include <cstddef>
#include <cstring>
#include <boost/type_traits/remove_const.hpp>
#include <boost/tuple/tuple.hpp>

namespace wg
{
namespace lcl
{
namespace detail
{

template <typename T>
struct bind_traits
{
  typedef T bindee_type;
  typedef T binder_type;
};

template <typename T, std::size_t N>
struct bind_traits<T[N]>
{
  struct binder_type;

  typedef T bindee_type[N];
  typedef binder_type binder_type;

  struct binder_type
  {
    // array_type has to be mutable so it can be "initialized".
    typedef typename ::boost::remove_const<T>::type array_type[N];

    // Purposefully allow implicit conversion.
    // Rationale:
    //   1) Array type members of ::boost::tuple can't be initialized. The work
    //     around is to to use a struct wrapper, ie, this class. Therefore we
    //     want to be able to construct an instance of this class directly from
    //     the value of array type.
    //   2) Because this is a detail class whose use is limited and easily
    //     enumerated, the implicit conversion should not cause a problem.
    binder_type(array_type const & array)
    {
      std::memcpy(m_array, array, sizeof(array));
    }

    operator bindee_type & ()
    {
      return m_array;
    }

  private:
    array_type m_array;
  };
};

}
}
}

#endif /* WG_LOCAL_DETAIL_BINDER_HH_ */
