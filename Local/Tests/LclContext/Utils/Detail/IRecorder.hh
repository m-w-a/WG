#ifndef WG_LCLCONTEXT_DETAIL_TEST_DETAIL_IRECORDER_HH_
#define WG_LCLCONTEXT_DETAIL_TEST_DETAIL_IRECORDER_HH_

#include <WG/Local/Tests/LclContext/Utils/Utils.hh>
#include <cstddef>

namespace wg
{
namespace lclcontext
{
namespace detail
{
namespace test
{

class RecordKeeper;

namespace detail
{

class IRecorder
{
public:
  explicit IRecorder(RecordKeeper & impl);

  // Returns Result::Error if duplicate "id" entered.
  Result::Kind makeRecordFor(ScopeManager::Id const id);
  // Returns Result::Error if duplicate "id" entered.
  Result::Kind makeRecordFor(ScopeManager::Id const id, std::size_t const position);
  // Returns Result::Error if record not found.
  Result::Kind markEntryCallFor(ScopeManager::Id const id);
  // Returns Result::Error if record not found.
  Result::Kind markEntryWillThrowFor(ScopeManager::Id const id);
  // Returns Result::Error if record not found.
  Result::Kind markExitCallFor(ScopeManager::Id const id);
  // Returns Result::Error if record not found.
  Result::Kind markScopeCompletionFor(ScopeManager::Id const id);

private:
  RecordKeeper * /* const */ m_pImpl;
};

}
}
}
}
}

#endif /* WG_LCLCONTEXT_DETAIL_TEST_DETAIL_IRECORDER_HH_ */
