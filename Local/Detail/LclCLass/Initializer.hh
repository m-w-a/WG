#ifndef WG_LOCAL_LCLCLASS_INITIALIZER_HH_
#define WG_LOCAL_LCLCLASS_INITIALIZER_HH_

#include <boost/config.hpp>

namespace wg
{
namespace lclclass
{
namespace detail
{

struct initializer
{
protected:
  void init() BOOST_NOEXCEPT { /* noop */ }
};

}
}
}

#endif /* WG_LOCAL_LCLCLASS_INITIALIZER_HH_ */
