#ifndef WG_LCLCONTEXT_DETAIL_TEST_SCOPEMNGRTEMPLATE_HH_
#define WG_LCLCONTEXT_DETAIL_TEST_SCOPEMNGRTEMPLATE_HH_

#include <WG/Local/Tests/LclContext/Utils/Utils.hh>
#include <WG/Local/Tests/LclContext/Utils/Records.hh>
#include <boost/type_traits/remove_reference.hpp>
#include <stdexcept>

namespace wg
{
namespace lclcontext
{
namespace detail
{
namespace test
{

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

#endif /* WG_LCLCONTEXT_DETAIL_TEST_SCOPEMNGRTEMPLATE_HH_ */
