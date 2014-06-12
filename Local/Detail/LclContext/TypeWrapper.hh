#ifndef WG_LCLCONTEXT_DETAIL_TYPEWRAPPER_HH_
#define WG_LCLCONTEXT_DETAIL_TYPEWRAPPER_HH_

// Aknowledgements.
//   This is the same technique Boost.Foreach uses to determine the type of
//   expressions without evaluating them.

//###########
//Public APIs
//###########


namespace wg
{
namespace lclcontext
{
namespace detail
{

template<typename T>
struct type_wrapper;

}
}
}

// Expands to "type_wrapper<T> *", where T represents the type of "expr",
// without evaluating "expr".
#define WG_LCLCONTEXT_DETAIL_ENCODEDTYPEOF_EXPLICITSCOPEMNGR(expr) \
  WG_LCLCONTEXT_DETAIL_ENCODEDTYPEOF_EXPLICITSCOPEMNGR_IMPL(expr)

//####
//Impl
//####

namespace wg
{
namespace lclcontext
{
namespace detail
{

template<typename T>
struct type_wrapper
{
};

template<typename T>
inline type_wrapper<T> * encode_type(T &)
{
  return 0;
}

#define WG_LCLCONTEXT_DETAIL_ENCODEDTYPEOF_EXPLICITSCOPEMNGR_IMPL(expr) \
  (true \
    ? 0 \
    : ::wg::lclcontext::detail::encode_type(expr))

}
}
}

#endif /* WG_LCLCONTEXT_DETAIL_TYPEWRAPPER_HH_ */
