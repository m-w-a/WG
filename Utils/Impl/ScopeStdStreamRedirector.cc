#include <WG/Utils/ScopeStdStreamRedirector.hh>
#include <boost/iostreams/stream_buffer.hpp>
#include <boost/iostreams/device/null.hpp>

std::streambuf & getNullStreambuf()
{
  using namespace boost::iostreams;
  static stream_buffer<null_sink> nullStreambuf((null_sink()));
  
  return nullStreambuf;
}

namespace WG
{
namespace Utils
{

ScopeStdStreamRedirector::ScopeStdStreamRedirector(
  std::iostream & streamToRedirect,
  std::streambuf & newStrmbuf)
: m_StreamToRedirect(streamToRedirect),
  m_NewStrmbuf(newStrmbuf),
  m_pOriginalStreambuf(m_StreamToRedirect.rdbuf(&m_NewStrmbuf))
{
}

ScopeStdStreamRedirector::~ScopeStdStreamRedirector()
{
  m_StreamToRedirect.rdbuf(m_pOriginalStreambuf);
}

}
}
