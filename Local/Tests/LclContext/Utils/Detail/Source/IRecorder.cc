#include <WG/Local/Tests/LclContext/Utils/Detail/IRecorder.hh>
#include <WG/Local/Tests/LclContext/Utils/Records.hh>

namespace wg
{
namespace lclcontext
{
namespace detail
{
namespace test
{
namespace detail
{

IRecorder::IRecorder(RecordKeeper & impl)
: m_pImpl(::boost::addressof(impl))
{}

Result::Kind IRecorder::makeRecordFor(ScopeManager::Id const id)
{
  return m_pImpl->makeRecordFor(id);
}

Result::Kind IRecorder::makeRecordFor(
  ScopeManager::Id const id, std::size_t const position)
{
  return m_pImpl->makeRecordFor(id, position);
}

Result::Kind IRecorder::markEntryCallFor(ScopeManager::Id const id)
{
  return m_pImpl->markEntryCallFor(id);
}

Result::Kind IRecorder::markEntryWillThrowFor(ScopeManager::Id const id)
{
  return m_pImpl->markEntryWillThrowFor(id);
}

Result::Kind IRecorder::markExitCallFor(ScopeManager::Id const id)
{
  return m_pImpl->markExitCallFor(id);
}

Result::Kind IRecorder::markScopeCompletionFor(ScopeManager::Id const id)
{
  return m_pImpl->markScopeCompletionFor(id);
}

}
}
}
}
}
