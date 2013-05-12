#ifndef WG_UTILS_SCOPEDSTDSTREAMREDIRECTOR_HH_
#define WG_UTILS_SCOPEDSTDSTREAMREDIRECTOR_HH_

#include <iosfwd>
#include <WG/Utils/ClassMethodDisablers.hh>

namespace WG
{
namespace Utils
{

std::streambuf & getNullStreambuf();

class ScopedStdStreamRedirector
{
public:
  ///@brief Redirect on object construction.
  ScopedStdStreamRedirector(
    std::ios & streamToRedirect,
    std::streambuf & newStrmbuf);
  ///@brief Disable redirection on object destruction.
  ~ScopedStdStreamRedirector();

  WG_DISABLE_DEFAULT_CTOR(ScopedStdStreamRedirector);
  WG_DISABLE_COPY_CTOR(ScopedStdStreamRedirector);
  WG_DISABLE_COPY_ASSIGNMENT(ScopedStdStreamRedirector);
  WG_DISABLE_HEAP_ALLOCATION();
  
private:
  std::ios & m_StreamToRedirect;
  std::streambuf & m_NewStrmbuf;
  std::streambuf * const m_pOriginalStreambuf;
};

}
}

#endif //WG_UTILS_SCOPEDSTDSTREAMREDIRECTOR_HH_
