#ifndef WAVEGLIDER_CORE_BOOSTITERATORFACADEIMPL_HH_
#define WAVEGLIDER_CORE_BOOSTITERATORFACADEIMPL_HH_

#include <iterator>
#include <boost/iterator/iterator_facade.hpp>

namespace WaveGlider
{
namespace Core
{

template <typename ITERATORIMPL, typename BOOSTITERATORFACADE>
class BoostIteratorFacadeImpl;

template <
    typename ITERATORIMPL,
    typename BIF_DERIVED,
    typename BIF_VALUE,
    typename BIF_CATEGORYORTRAVERSAL,
    typename BIF_REFERENCE,
    typename BIF_DIFFERENCE>
class BoostIteratorFacadeImpl<
    ITERATORIMPL,
    boost::iterator_facade<
        BIF_DERIVED,
        BIF_VALUE,
        BIF_CATEGORYORTRAVERSAL,
        BIF_REFERENCE,
        BIF_DIFFERENCE> >
{
public:
    typedef ITERATORIMPL IteratorType;
    typedef boost::iterator_facade<
        BIF_DERIVED,
        BIF_VALUE,
        BIF_CATEGORYORTRAVERSAL,
        BIF_REFERENCE,
        BIF_DIFFERENCE
    > BoostIteratorFacade;
    typedef typename BoostIteratorFacade::reference ReferenceType;
    typedef typename BoostIteratorFacade::difference_type DifferenceType;

public:
    ReferenceType dereference() const
    { return *m_It; }
    bool equal(BoostIteratorFacadeImpl const & rhs) const
    { return m_It == rhs.m_It; }
    void increment()
    { ++m_It; }
    void decrement()
    { --m_It; }
    void advance(DifferenceType const n)
    { std::advance(m_It, n); }
    DifferenceType distance_to(BoostIteratorFacadeImpl const & rhs) const
    { return std::distance(m_It, rhs.m_It); }

protected:
    typedef BoostIteratorFacadeImpl<
        ITERATORIMPL,
        boost::iterator_facade<
            BIF_DERIVED,
            BIF_VALUE,
            BIF_CATEGORYORTRAVERSAL,
            BIF_REFERENCE,
            BIF_DIFFERENCE
        >
    > BoostIteratorFacadeImplType;

protected:
    BoostIteratorFacadeImpl()
    : m_It()
    {}
    BoostIteratorFacadeImpl(IteratorType const & it)
    : m_It(it)
    {}
    BoostIteratorFacadeImpl(BoostIteratorFacadeImpl const & rhs)
    : m_It(rhs.m_It)
    {}
    virtual ~BoostIteratorFacadeImpl()
    {}

private:
    //Disallowed.
    BoostIteratorFacadeImpl & operator=(BoostIteratorFacadeImpl const &);

private:
    IteratorType m_It;
};

}
}

#endif /* WAVEGLIDER_CORE_BOOSTITERATORFACADEIMPL_HH_ */
