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

void IRecorder::makeRecordFor(ScopeManager::Id const id)
{
  m_pImpl->makeRecordFor(id);
}

void IRecorder::makeRecordFor(
  ScopeManager::Id const id, std::size_t const position)
{
  m_pImpl->makeRecordFor(id, position);
}

void IRecorder::markEntryCallFor(ScopeManager::Id const id)
{
  m_pImpl->markEntryCallFor(id);
}

void IRecorder::markEntryWillThrowFor(ScopeManager::Id const id)
{
  m_pImpl->markEntryWillThrowFor(id);
}

void IRecorder::markExitCallFor(ScopeManager::Id const id)
{
  m_pImpl->markExitCallFor(id);
}

void IRecorder::markScopeCompletionFor(ScopeManager::Id const id)
{
  m_pImpl->markScopeCompletionFor(id);
}

}
}
}
}
}
