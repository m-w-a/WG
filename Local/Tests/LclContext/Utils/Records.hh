#ifndef WG_LCLCONTEXT_DETAIL_TEST_RECORDS_HH_
#define WG_LCLCONTEXT_DETAIL_TEST_RECORDS_HH_

#include <WG/Local/Tests/LclContext/Utils/Utils.hh>
#include <vector>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/mem_fun.hpp>
#include <boost/multi_index/tag.hpp>
#include <boost/optional.hpp>
#include <boost/utility/value_init.hpp>
#include <boost/utility/addressof.hpp>

namespace wg
{
namespace lclcontext
{
namespace detail
{
namespace test
{

class Record
{
public:
  explicit Record(ScopeManager::Id const id)
  : m_Id(id),
    m_DidCallEnter(false),
    m_DidCallExit(false),
    m_WasScopeCompleted(false)
  {}

  ScopeManager::Id id() const { return m_Id; }
  bool didCallEnter() const { return m_DidCallEnter; }
  bool didCallExit() const { return m_DidCallExit; }
  bool wasScopeCompleted() const { return m_WasScopeCompleted; }

  void markEntryCall() { m_DidCallEnter = true; }
  void markExitCall() { m_DidCallExit = true; }
  void markScopeCompletion() { m_WasScopeCompleted = true; }

private:
  ScopeManager::Id /*const*/ m_Id;
  bool m_DidCallEnter;
  bool m_DidCallExit;
  bool m_WasScopeCompleted;
};

namespace detail
{
class IRecorder;
}

class RecordKeeper
{
public:
  RecordKeeper();

  // Returns std::pair<some-undefined-obj, Result::Error> if record not found.
  std::pair<Record const *, Result::Kind> getRecordFor(ScopeManager::Id const id);
  // Returns true only if enter calls were made for each registered scope manager
  // id in the order in which those ids where registered, but only up to and
  // including the id, if any, of the first throwing scope manager.
  bool isEntryCallOrderCorrect() const;
  // Returns true only if the number of exit calls equals the number of enter
  // calls and the exit calls were made in the reverse order of the enter calls.
  bool isExitCallOrderCorrect() const;
private:
  //Declared and purposefully not defined.
  RecordKeeper(RecordKeeper const &);
  //Declared and purposefully not defined.
  RecordKeeper & operator=(RecordKeeper);
private:
  friend class detail::IRecorder;
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
  struct by_dcln_order {};
  struct by_id {};

  typedef ::boost::multi_index::multi_index_container
  <
    Record,
    ::boost::multi_index::indexed_by
    <
      ::boost::multi_index::sequenced
      <
        ::boost::multi_index::tag<by_dcln_order>
      >,
      ::boost::multi_index::ordered_unique
      <
        ::boost::multi_index::tag<by_id>,
        ::boost::multi_index::const_mem_fun<Record, ScopeManager::Id, &Record::id>
      >
    >
  > RecordCntr;

  typedef RecordCntr::index<by_id>::type RecordsIndexedById;
  typedef RecordCntr::index<by_dcln_order>::type RecordsIndexedByDclnOrder;

  typedef std::vector<ScopeManager::Id /*const*/> IdVector;
private:
  std::pair<RecordsIndexedById::iterator, Result::Kind>
    getMutableRecordFor(ScopeManager::Id const id);
private:
  RecordCntr m_Records;
  ::boost::optional<ScopeManager::Id> m_EnterMethodThatThrew;
  IdVector m_EntryCalls;
  IdVector m_ExitCalls;
};

}
}
}
}

#endif /* WG_LCLCONTEXT_DETAIL_TEST_RECORDS_HH_ */
