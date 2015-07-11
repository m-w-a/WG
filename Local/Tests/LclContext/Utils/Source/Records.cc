#include <WG/Local/Tests/LclContext/Utils/Records.hh>
#include <utility>
#include <boost/utility/addressof.hpp>

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

Result::Kind RecordKeeper::makeRecordFor(
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
    return Result::Failure;
  }

  return Result::Success;
}

Result::Kind RecordKeeper::makeRecordFor(ScopeManager::Id const id)
{
  std::pair<RecordsIndexedByDclnOrder::iterator, bool> result =
    m_Records.get<by_dcln_order>().push_back(Record(id));

  if( ! result.second )
  {
    return Result::Failure;
  }

  return Result::Success;
}

Result::Kind RecordKeeper::markEntryCallFor(ScopeManager::Id const id)
{
  struct MarkEntryCall
  {
    static void apply(Record & rcd)
    {
      rcd.markEntryCall();
    }
  };

  std::pair<RecordsIndexedById::iterator, Result::Kind> rcdResult =
    this->getMutableRecordFor(id);
  if(rcdResult.second == Result::Failure)
  {
    return Result::Failure;
  }

  bool const didModify =
    m_Records.get<by_id>().modify(rcdResult.first, MarkEntryCall::apply);
  if( ! didModify )
  {
    return Result::Failure;
  }

  this->m_EntryCalls.push_back(id);

  return Result::Success;
}

Result::Kind RecordKeeper::markEntryWillThrowFor(ScopeManager::Id const id)
{
  // Ensure id exists.
  std::pair<RecordsIndexedById::iterator, Result::Kind> rcdResult =
    this->getMutableRecordFor(id);
  if(rcdResult.second == Result::Failure)
  {
    return Result::Failure;
  }

  m_EnterMethodThatThrew = id;

  return Result::Success;
}

Result::Kind RecordKeeper::markExitCallFor(ScopeManager::Id const id)
{
  struct MarkExitCall
  {
    static void apply(Record & rcd)
    {
      rcd.markExitCall();
    }
  };

  std::pair<RecordsIndexedById::iterator, bool> rcdResult =
    this->getMutableRecordFor(id);
  if(rcdResult.second == Result::Failure)
  {
    return Result::Failure;
  }

  bool const didModify =
    m_Records.get<by_id>().modify(rcdResult.first, MarkExitCall::apply);
  if( ! didModify )
  {
    return Result::Failure;
  }

  this->m_ExitCalls.push_back(id);

  return Result::Success;
}

Result::Kind RecordKeeper::markScopeCompletionFor(ScopeManager::Id const id)
{
  struct MarkScopeCompletion
  {
    static void apply(Record & rcd)
    {
      rcd.markScopeCompletion();
    }
  };

  std::pair<RecordsIndexedById::iterator, Result::Kind> rcdResult =
    this->getMutableRecordFor(id);
  if(rcdResult.second == Result::Failure)
  {
    return Result::Failure;
  }

  bool const didModify =
    m_Records.get<by_id>().modify(rcdResult.first, MarkScopeCompletion::apply);
  if( ! didModify )
  {
    return Result::Failure;
  }

  return Result::Success;
}

std::pair<Record const *, Result::Kind>
  RecordKeeper::getRecordFor(ScopeManager::Id const id)
{
  std::pair<RecordsIndexedById::iterator, Result::Kind> rcdResult =
    this->getMutableRecordFor(id);

  Record const * pRcd =
    (rcdResult.second == Result::Success) ? ::boost::addressof(*rcdResult.first) : 0;
  return std::make_pair(pRcd, rcdResult.second);
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

std::pair<RecordKeeper::RecordsIndexedById::iterator, Result::Kind>
  RecordKeeper::getMutableRecordFor(ScopeManager::Id const id)
{
  RecordsIndexedById & recordsById = m_Records.get<by_id>();
  RecordsIndexedById::iterator const it = recordsById.find(id);

  if(it == recordsById.end())
  {
    return std::make_pair(it, Result::Failure);
  }

  return std::make_pair(it, Result::Success);
}

}
}
}
}
