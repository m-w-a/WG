#ifndef WG_LCLCONTEXT_DETAIL_TEST_SCOPEMNGRTEMPLATE_HH_
#define WG_LCLCONTEXT_DETAIL_TEST_SCOPEMNGRTEMPLATE_HH_

#include <WG/Local/Tests/LclContext/Utils/Utils.hh>
#include <WG/Local/Tests/LclContext/Utils/Records.hh>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_void.hpp>
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

template <typename T>
struct EntryValue
{
  typedef typename ::boost::remove_reference<T>::type EntryValueType;
  EntryValueType EntryObj;
};

template <>
struct EntryValue<void>
{};

template
<
  typename EntryReturnType,
  typename EnterThrowsT,
  typename ExitThrowsT
>
class ScopeMngrTemplate : public EntryValue<EntryReturnType>
{
public:
  explicit ScopeMngrTemplate(ScopeManager::Id const id, RecordKeeper & records)
  : m_Id(id),
    m_Recorder(records)
  {
    m_Recorder.makeRecordFor(m_Id);
  }

  explicit ScopeMngrTemplate(
    ScopeManager::Id const id,
    RecordKeeper & records,
    std::size_t const position)
  : m_Id(id),
    m_Recorder(records)
  {
    m_Recorder.makeRecordFor(m_Id, position);
  }

  EntryReturnType enter()
  {
    m_Recorder.markEntryCallFor(m_Id);

    this->enterThrows(static_cast<EnterThrowsT *>(0));

    return this->enterImpl<EntryReturnType>();
  }

  void exit(bool const scope_completed)
  {
    m_Recorder.markExitCallFor(m_Id);
    if(scope_completed)
    {
      m_Recorder.markScopeCompletionFor(m_Id);
    }

    this->exitThrows(static_cast<ExitThrowsT *>(0));
  }

private:
  template <typename R>
  typename ::boost::disable_if< ::boost::is_void<R>, R >::type
    enterImpl()
  {
    return this->EntryObj;
  }

  template <typename R>
  typename ::boost::enable_if< ::boost::is_void<R> >::type
    enterImpl()
  {}

  void enterThrows(void *)
  {}

  void exitThrows(void *)
  {}

#ifndef BOOST_NO_EXCEPTIONS
  void enterThrows(EnterThrows *)
  {
    m_Recorder.markEntryWillThrowFor(m_Id);
    throw EnterException();
  }

  void exitThrows(ExitThrows *)
  {
    throw ExitException();
  }
#endif

private:
  ScopeManager::Id const m_Id;
  IRecorder m_Recorder;
};

}
}
}
}

#endif /* WG_LCLCONTEXT_DETAIL_TEST_SCOPEMNGRTEMPLATE_HH_ */
