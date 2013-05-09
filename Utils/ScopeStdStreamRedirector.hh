#ifndef WG_UTILS_SCOPESTDSTREAMREDIRECTOR_HH_
#define WG_UTILS_SCOPESTDSTREAMREDIRECTOR_HH_

#include <iosfwd>
#include <boost/scoped_ptr.hpp>
#include <memory.hpp>
#include <WG/Utils/ClassMethodDisablers.hh>

namespace WG
{
namespace Utils
{

std::streambuf & getNullStreambuf();

class ScopeStdStreamRedirector
{
public:
  ScopeStdStreamRedirector(
    std::iostream & streamToRedirect,
    std::streambuf & newStrmbuf);
  ~ScopeStdStreamRedirector();

  WG_DISABLE_DEFAULT_CTOR(ScopeStdStreamRedirector);
  WG_DISABLE_COPY_CTOR(ScopeStdStreamRedirector);
  WG_DISABLE_COPY_ASSIGNMENT(ScopeStdStreamRedirector);
  WG_DISABLE_HEAP_ALLOCATION();
  
private:
  std::iostream & m_StreamToRedirect;
  std::streambuf & m_NewStrmbuf;
  std::streambuf * const m_pOriginalStreambuf;
};

}
}

#endif //WG_UTILS_SCOPESTDSTREAMREDIRECTOR_HH_
