#ifndef WG_LCLCONTEXT_DETAIL_TEST_UTILS_HH_
#define WG_LCLCONTEXT_DETAIL_TEST_UTILS_HH_

#include <vector>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/mem_fun.hpp>
#include <boost/multi_index/tag.hpp>

namespace wg
{
namespace lclcontext
{
namespace detail
{
namespace test
{

struct Exception1 {};
struct Exception2 {};
struct Exception3 {};

struct ScopeManager
{
  enum Id
  {
    Id0,
    Id1,
    Id2,
    Id3,
    Id4
  };
};

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

class RecordKeeper
{
public:
  RecordKeeper();
public:
  // Throws std::invalid_argument if duplicate "id" entered.
  void makeRecordFor(ScopeManager::Id const id);
  // Throws std::invalid_argument if record not found.
  Record const & getRecordFor(ScopeManager::Id const id);
  // Throws std::invalid_argument if record not found.
  void markEntryCallFor(ScopeManager::Id const id);
  // Throws std::invalid_argument if record not found.
  void markExitCallFor(ScopeManager::Id const id);
  // Throws std::invalid_argument if record not found.
  void markScopeCompletionFor(ScopeManager::Id const id);
  bool isEntryCallOrderCorrect() const;
  bool isExitCallOrderCorrect() const;
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

  typedef std::vector<ScopeManager::Id> IdVector;
private:
  RecordsIndexedById::iterator getMutableRecordFor(ScopeManager::Id const id);
private:
  RecordCntr m_Records;
  IdVector m_EntryCalls;
  IdVector m_ExitCalls;
};

class SimpleScopeMngr
{
public:
  explicit SimpleScopeMngr(ScopeManager::Id const id, RecordKeeper & records)
  : m_Id(id),
    m_Records(records)
  {
    m_Records.makeRecordFor(m_Id);
  }

  void enter()
  {
    m_Records.markEntryCallFor(m_Id);
  }

  void exit(bool const scope_completed)
  {
    m_Records.markExitCallFor(m_Id);
    if(scope_completed)
    {
      m_Records.markScopeCompletionFor(m_Id);
    }
  }

private:
  ScopeManager::Id const m_Id;
  RecordKeeper & m_Records;
};

}
}
}
}

#endif /* WG_LCLCONTEXT_DETAIL_TEST_UTILS_HH_ */
