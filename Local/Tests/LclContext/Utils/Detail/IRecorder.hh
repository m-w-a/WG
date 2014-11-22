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

  // Throws std::invalid_argument if duplicate "id" entered.
  void makeRecordFor(ScopeManager::Id const id);

  // Throws std::invalid_argument if duplicate "id" entered.
  void makeRecordFor(ScopeManager::Id const id, std::size_t const position);

  // Throws std::invalid_argument if record not found.
  void markEntryCallFor(ScopeManager::Id const id);

  // Throws std::invalid_argument if record not found.
  void markEntryWillThrowFor(ScopeManager::Id const id);

  // Throws std::invalid_argument if record not found.
  void markExitCallFor(ScopeManager::Id const id);

  // Throws std::invalid_argument if record not found.
  void markScopeCompletionFor(ScopeManager::Id const id);

private:
  RecordKeeper * /* const */ m_pImpl;
};

}
}
}
}
}

#endif /* WG_LCLCONTEXT_DETAIL_TEST_DETAIL_IRECORDER_HH_ */
