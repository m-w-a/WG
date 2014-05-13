#include <iostream>
#include <gtest/gtest.h>
#include <WG/Local/Tests/LclFunction/Utils/Detail/LclFunctionCallRegistrar.hh>

namespace wg
{
namespace lclfunction
{
namespace test
{

//---------------------
//lclfunction_registrar
//---------------------

lclfunction_registrar_t & lclfunction_registrar()
{
  static lclfunction_registrar_t registrar;
  return registrar;
}

//-----------------------
//lclfunction_registrar_t
//-----------------------

lclfunction_registrar_t::lclfunction_registrar_t()
{
}

lclfunction_registrar_t::~lclfunction_registrar_t()
{
  //No need to report orphaned lclfunctionS since they would have been reported
  //by some previous error message.
}

void lclfunction_registrar_t::register_call_for(
  global_functor_base_type const & lclfunction)
{
  //Note:
  //  attempted duplicate insertions are not an error since a lclfunction
  //  may be used in a for loop.
  (void)m_registry.insert(&lclfunction);
}

void lclfunction_registrar_t::unregister_call_for(
  lclfunction_registry_location const location)
{
  m_registry.erase(location);
}

lclfunction_registrar_t::query_result_type
  lclfunction_registrar_t::is_call_registered_for(
    global_functor_base_type const & lclfunction)
{
  registry_t::iterator const itfound = m_registry.find(&lclfunction);
  return query_result_type(itfound, itfound != m_registry.end());
}

}
}
}
