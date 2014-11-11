#include <WG/Local/Tests/LclContext/Utils.hh>
#include <stdexcept>
#include <utility>

namespace wg
{
namespace lclcontext
{
namespace detail
{
namespace test
{

//------------
//RecordKeeper
//------------

RecordKeeper::RecordKeeper()
: m_Records(), m_EnterMethodThatThrew(), m_EntryCalls(), m_ExitCalls()
{
}

void RecordKeeper::makeRecordFor(
  ScopeManager::Id const id,
  std::size_t const position)
{
  RecordsIndexedByDclnOrder::iterator it = m_Records.get<by_dcln_order>().begin();
  for(std::size_t indx = 0; indx < position; ++indx)
  {
    ++it;
  }

  std::pair<RecordsIndexedByDclnOrder::iterator, bool> result =
    m_Records.get<by_dcln_order>().insert(it, Record(id));

  if( ! result.second )
  {
    throw std::invalid_argument("Duplicate ScopeManager ID.");
  }
}

void RecordKeeper::makeRecordFor(ScopeManager::Id const id)
{
  std::pair<RecordsIndexedByDclnOrder::iterator, bool> result =
    m_Records.get<by_dcln_order>().push_back(Record(id));

  if( ! result.second )
  {
    throw std::invalid_argument("Duplicate ScopeManager ID.");
  }
}

Record const & RecordKeeper::getRecordFor(ScopeManager::Id const id)
{
  return *this->getMutableRecordFor(id);
}

void RecordKeeper::markEntryCallFor(ScopeManager::Id const id)
{
  struct MarkEntryCall
  {
    static void apply(Record & rcd)
    {
      rcd.markEntryCall();
    }
  };

  RecordsIndexedById::iterator itRcd = this->getMutableRecordFor(id);
  bool const didModify =
    m_Records.get<by_id>().modify(itRcd, MarkEntryCall::apply);
  if( ! didModify )
  {
    throw std::logic_error("Unexpected internal error.");
  }

  this->m_EntryCalls.push_back(id);
}

void RecordKeeper::markEntryWillThrowFor(ScopeManager::Id const id)
{
  // Ensure record exists.
  RecordsIndexedById::iterator itRcd = this->getMutableRecordFor(id);
  (void)itRcd;

  m_EnterMethodThatThrew = id;
}

void RecordKeeper::markExitCallFor(ScopeManager::Id const id)
{
  struct MarkExitCall
  {
    static void apply(Record & rcd)
    {
      rcd.markExitCall();
    }
  };

  RecordsIndexedById::iterator itRcd = this->getMutableRecordFor(id);
  bool const didModify =
    m_Records.get<by_id>().modify(itRcd, MarkExitCall::apply);
  if( ! didModify )
  {
    throw std::logic_error("Unexpected internal error.");
  }

  this->m_ExitCalls.push_back(id);
}

void RecordKeeper::markScopeCompletionFor(ScopeManager::Id const id)
{
  struct MarkScopeCompletion
  {
    static void apply(Record & rcd)
    {
      rcd.markScopeCompletion();
    }
  };

  RecordsIndexedById::iterator itRcd = this->getMutableRecordFor(id);
  bool const didModify =
    m_Records.get<by_id>().modify(itRcd, MarkScopeCompletion::apply);
  if( ! didModify )
  {
    throw std::logic_error("Unexpected internal error.");
  }
}

bool RecordKeeper::isEntryCallOrderCorrect() const
{
  RecordsIndexedByDclnOrder const & recordsByDclnOrder =
    m_Records.get<by_dcln_order>();

  if( ! m_EnterMethodThatThrew
      && m_EntryCalls.size() != recordsByDclnOrder.size() )
  {
    return false;
  }

  typedef std::pair
  <
    RecordsIndexedByDclnOrder::const_iterator,
    IdVector::const_iterator
  > ItPair;
  for(ItPair its = std::make_pair(recordsByDclnOrder.begin(), m_EntryCalls.begin());
    its.second != m_EntryCalls.end();
    ++its.first, ++its.second)
  {
    if(its.first->id() != *its.second)
    {
      return false;
    }
  }

  return true;
}

bool RecordKeeper::isExitCallOrderCorrect() const
{
  if(m_EntryCalls.size() != m_ExitCalls.size())
  {
    return false;
  }

  typedef std::pair
  <
    IdVector::const_iterator,
    IdVector::const_reverse_iterator
  > ItPair;

  for(ItPair its = std::make_pair(m_EntryCalls.begin(), m_ExitCalls.rbegin());
    its.first != m_EntryCalls.end();
    ++its.first, ++its.second)
  {
    if(*its.first != *its.second)
    {
      return false;
    }
  }

  return true;
}

RecordKeeper::RecordsIndexedById::iterator
  RecordKeeper::getMutableRecordFor(ScopeManager::Id const id)
{
  RecordsIndexedById & recordsById = m_Records.get<by_id>();
  RecordsIndexedById::iterator const it = recordsById.find(id);

  if(it == recordsById.end())
  {
    throw std::invalid_argument("Uknown ScopeManager ID.");
  }

  return it;
}

}
}
}
}
