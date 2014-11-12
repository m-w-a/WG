#ifndef WG_LCLCONTEXT_DETAIL_TEST_UTILS_HH_
#define WG_LCLCONTEXT_DETAIL_TEST_UTILS_HH_

#include <vector>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/mem_fun.hpp>
#include <boost/multi_index/tag.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/optional.hpp>
#include <stdexcept>
#include <boost/utility/value_init.hpp>

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
  // Throws std::invalid_argument if duplicate "id" entered.
  void makeRecordFor(ScopeManager::Id const id, std::size_t const position);
  // Throws std::invalid_argument if record not found.
  Record const & getRecordFor(ScopeManager::Id const id);
  // Throws std::invalid_argument if record not found.
  void markEntryCallFor(ScopeManager::Id const id);
  // Throws std::invalid_argument if record not found.
  void markEntryWillThrowFor(ScopeManager::Id const id);
  // Throws std::invalid_argument if record not found.
  void markExitCallFor(ScopeManager::Id const id);
  // Throws std::invalid_argument if record not found.
  void markScopeCompletionFor(ScopeManager::Id const id);
  // Returns true only if enter calls were made for each registered scope manager
  // id in the order in which those ids where registered, but only up to and
  // including the id, if any, of the first throwing scope manager.
  bool isEntryCallOrderCorrect() const;
  // Returns true only if the number of exit calls equals the number of enter
  // calls and the exit calls were made in the reverse order of the enter calls.
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

  typedef std::vector<ScopeManager::Id /*const*/> IdVector;
private:
  RecordsIndexedById::iterator getMutableRecordFor(ScopeManager::Id const id);
private:
  RecordCntr m_Records;
  ::boost::optional<ScopeManager::Id> m_EnterMethodThatThrew;
  IdVector m_EntryCalls;
  IdVector m_ExitCalls;
};

struct EmptyCntr {};
struct EnterThrows {};
struct ExitThrows {};

template
<
  typename EntryReturnType,
  typename EnterThrowsT = void,
  typename ExitThrowsT = void
>
class ScopeMngrTemplate;

typedef ScopeMngrTemplate<void> SimpleScopeMngr;
typedef ScopeMngrTemplate<void, EnterThrows, void> EnterThrowsScopeMngr;
typedef ScopeMngrTemplate<void, void, ExitThrows> ExitThrowsScopeMngr;
typedef ScopeMngrTemplate<void, EnterThrows, ExitThrows> EnterAndExitThrowScopeMngr;
typedef ScopeMngrTemplate<EmptyCntr> ByValueEntryScopeMngr;
typedef ScopeMngrTemplate<EmptyCntr &> ByRefEntryScopeMngr;

struct EnterException : public std::runtime_error
{
  EnterException()
  : std::runtime_error("")
  {}
};

struct ExitException : public std::runtime_error
{
  ExitException()
  : std::runtime_error("")
  {}
};

template
<
  typename EntryReturnType,
  typename EnterThrowsT,
  typename ExitThrowsT
>
class ScopeMngrTemplate
{
public:
  explicit ScopeMngrTemplate(ScopeManager::Id const id, RecordKeeper & records)
  : m_Id(id),
    m_Records(records)
  {
    m_Records.makeRecordFor(m_Id);
  }

  explicit ScopeMngrTemplate(
    ScopeManager::Id const id,
    RecordKeeper & records,
    std::size_t const position)
  : m_Id(id),
    m_Records(records)
  {
    m_Records.makeRecordFor(m_Id, position);
  }

  EntryReturnType enter()
  {
    m_Records.markEntryCallFor(m_Id);

    this->enterThrows(static_cast<EnterThrowsT *>(0));

    typedef
      typename ::boost::remove_reference<EntryReturnType>::type
        NoRefEntryReturnType;
    return this->enterImpl<EntryReturnType>(
      static_cast<NoRefEntryReturnType *>(0) );
  }

  void exit(bool const scope_completed)
  {
    m_Records.markExitCallFor(m_Id);
    if(scope_completed)
    {
      m_Records.markScopeCompletionFor(m_Id);
    }

    this->exitThrows(static_cast<ExitThrowsT *>(0));
  }

private:
  template <typename R, typename P1>
  R enterImpl(P1 *)
  {
    static ::boost::value_initialized<P1> retVal;
    return retVal;
  }

  template <typename R>
  R enterImpl(void *)
  {}

  void enterThrows(void *)
  {}

  void enterThrows(EnterThrows *)
  {
    m_Records.markEntryWillThrowFor(m_Id);
    throw EnterException();
  }

  void exitThrows(void *)
  {}

  void exitThrows(ExitThrows *)
  {
    throw ExitException();
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
