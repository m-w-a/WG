#ifndef WG_TESTS_LCLFUNCTION_LCLFUNCTIONCALLVERIFIER_HH_
#define WG_TESTS_LCLFUNCTION_LCLFUNCTIONCALLVERIFIER_HH_

#include <cstddef>

namespace wg
{
namespace lclfunction
{

namespace detail
{
class global_functor_base_type;
}

namespace test
{

class lclfunction_call_verifier
{
public:
  typedef
    ::wg::lclfunction::detail::global_functor_base_type
     global_functor_base_type;

public:
  lclfunction_call_verifier(
    char const * const lclfunction_name,
    char const * const file,
    std::size_t const line);
  ~lclfunction_call_verifier();
  void verify_call_to(global_functor_base_type const & lclfunction);
private:
  //Purposefully declared and not defined.
  lclfunction_call_verifier();
  //Purposefully declared and not defined.
  lclfunction_call_verifier(lclfunction_call_verifier const &);
  //Purposefully declared and not defined.
  lclfunction_call_verifier & operator=(lclfunction_call_verifier const &);
private:
  char const * const m_lclfunction_name;
  bool m_did_verify_call;
  char const * const m_file;
  std::size_t const m_line;
};

}
}
}

#endif /* WG_TESTS_LCLFUNCTION_LCLFUNCTIONCALLVERIFIER_HH_ */
