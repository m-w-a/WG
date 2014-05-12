#include <gtest/gtest.h>
#include <WG/Local/Tests/LclFunction/Utils/Detail/LclFunctionCallVerifier.hh>
#include <WG/Local/Tests/LclFunction/Utils/Detail/LclFunctionCallRegistrar.hh>

namespace wg
{
namespace lclfunction
{
namespace test
{

//-------------------------
//lclfunction_call_verifier
//-------------------------

lclfunction_call_verifier::lclfunction_call_verifier(
  char const * const lclfunction_name,
  char const * const file,
  std::size_t const line)
  : m_lclfunction_name(lclfunction_name),
    m_did_verify_call(false),
    m_file(file),
    m_line(line)
{
}

lclfunction_call_verifier::~lclfunction_call_verifier()
{
  if( ! m_did_verify_call )
  {
    ADD_FAILURE_AT(m_file, m_line)
      << "unverified local function: '"
      << m_lclfunction_name << "'"
      << "\n"
      << "Did you forget to invoke WG_TEST_LCLFUNCTION_VERIFYCALL";
  }
}

void lclfunction_call_verifier::verify_call_to(
  global_functor_base_type const & lclfunction)
{
  m_did_verify_call = true;
  lclfunction_registrar_t::query_result_type const is_registered =
    lclfunction_registrar().is_call_registered_for(lclfunction);
  if( ! is_registered.second )
  {
    ADD_FAILURE_AT(m_file, m_line)
      << "uncalled or unmarked local function: '"
      << m_lclfunction_name
      << "'";
  }
  else
  {
    lclfunction_registrar().unregister_call_for(is_registered.first);
  }
}

}
}
}
