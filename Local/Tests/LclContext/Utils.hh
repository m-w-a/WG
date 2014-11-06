#ifndef WG_LCLCONTEXT_DETAIL_TEST_UTILS_HH_
#define WG_LCLCONTEXT_DETAIL_TEST_UTILS_HH_

#include <vector>

namespace wg
{
namespace lclcontext
{
namespace detail
{
namespace test
{

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

class Record;
typedef std::vector<Record> RecordKeeper;

class Record
{
public:
  class PrivateKey { friend class SimpleScopeMngr; };
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

  void markEnterCall(PrivateKey) { m_DidCallEnter = true; }
  void markExitCall(PrivateKey) { m_DidCallExit = true; }
  void markScopeCompletion(PrivateKey) { m_WasScopeCompleted = true; }

private:
  ScopeManager::Id /*const*/ m_Id;
  bool m_DidCallEnter;
  bool m_DidCallExit;
  bool m_WasScopeCompleted;
};

class SimpleScopeMngr
{
public:
  // Appends a record pertaining to this object to "records".
  explicit SimpleScopeMngr(ScopeManager::Id const id, RecordKeeper & records)
  : m_Id(id),
    m_Records(records)
  {
    m_Records.push_back(Record(m_Id));
  }

  void enter()
  {
    m_Records.back().markEnterCall(Record::PrivateKey());
  }

  void exit(bool const scope_completed)
  {
    m_Records.back().markExitCall(Record::PrivateKey());
    if(scope_completed)
    {
      m_Records.back().markScopeCompletion(Record::PrivateKey());
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
