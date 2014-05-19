#ifndef WG_TESTS_LCLFUNCTION_LCLFUNCTIONCALLREGISTRAR_HH_
#define WG_TESTS_LCLFUNCTION_LCLFUNCTIONCALLREGISTRAR_HH_

#include <set>
#include <utility>

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

class lclfunction_registrar_t;
class lclfunction_call_verifier;

lclfunction_registrar_t & lclfunction_registrar();

class lclfunction_registrar_t
{
private:
  typedef std::set
  <
    ::wg::lclfunction::detail::global_functor_base_type const *
  > registry_t;

public:
  typedef
    ::wg::lclfunction::detail::global_functor_base_type
     global_functor_base_type;
  typedef registry_t::iterator lclfunction_registry_location;

public:
  lclfunction_registrar_t();
  ~lclfunction_registrar_t();
  void register_call_for(global_functor_base_type const & lclfunction);

private:
  //Declared and purposefully not defined.
  lclfunction_registrar_t(lclfunction_registrar_t const &);
  //Declared and purposefully not defined.
  lclfunction_registrar_t & operator=(lclfunction_registrar_t const &);

private:
  friend class lclfunction_call_verifier;
private:
  void unregister_call_for(lclfunction_registry_location const location);

  typedef std::pair<lclfunction_registry_location, bool> query_result_type;
  query_result_type is_call_registered_for(
    global_functor_base_type const & lclfunction);

private:
  registry_t m_registry;
};

}
}
}

#endif /* WG_TESTS_LCLFUNCTION_LCLFUNCTIONCALLREGISTRAR_HH_ */
