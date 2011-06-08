#ifndef WAVEGLIDER_CORE_ANYINSERTITERATOR_HH_
#define WAVEGLIDER_CORE_ANYINSERTITERATOR_HH_

#include <iterator>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/static_assert.hpp>

namespace myboost
{

template <typename VALUETYPE>
class any_insert_iterator;

namespace detail
{
template <typename CONTAINER, typename VALUETYPE>
void any_inserter_dispatch(
    void * opaqued_cntr,
    typename boost::remove_reference<VALUETYPE>::type const & value);
}

template <typename VALUETYPE, typename CONTAINER>
any_insert_iterator<VALUETYPE> any_inserter(CONTAINER & cntr);

template <typename VALUETYPE>
class any_insert_iterator :
    public std::iterator<std::output_iterator_tag, void, void, void, void>
{
public:
    typedef
        typename boost::remove_reference<VALUETYPE>::type const &
            const_reference;

public:
    any_insert_iterator();
    template <typename CONTAINER>
    explicit any_insert_iterator(CONTAINER & cntr);
    any_insert_iterator(any_insert_iterator<VALUETYPE> const & rhs);
    ~any_insert_iterator();
    any_insert_iterator<VALUETYPE> &
        operator=(any_insert_iterator<VALUETYPE> const & rhs);
    any_insert_iterator<VALUETYPE> &
        operator=(const_reference value);
    any_insert_iterator<VALUETYPE> & operator*();
    any_insert_iterator<VALUETYPE> & operator++();
    any_insert_iterator<VALUETYPE> & operator++(int);

private:
    typedef
        void
            (dispatcher)
                (void *, VALUETYPE const &);

private:
    dispatcher * dispatcher_;
    void * opaqued_cntr_;
};

//-------------------------
//Template Implementations.
//-------------------------

//------------
//any_inserter
//------------

template <typename VALUETYPE, typename CONTAINER>
any_insert_iterator<VALUETYPE> any_inserter(CONTAINER & cntr)
{
    return any_insert_iterator<VALUETYPE>(cntr);
}

//-------------------
//any_insert_iterator
//-------------------

template <typename VALUETYPE>
any_insert_iterator<VALUETYPE>::any_insert_iterator()
: dispatcher_(0),
  opaqued_cntr_(0)
{
}

template <typename VALUETYPE>
template <typename CONTAINER>
any_insert_iterator<VALUETYPE>::any_insert_iterator(CONTAINER & cntr)
: dispatcher_(detail::any_inserter_dispatch<CONTAINER, VALUETYPE>),
  opaqued_cntr_(&cntr)
{
    BOOST_STATIC_ASSERT( ! boost::is_pointer<CONTAINER>::value );
}

template <typename VALUETYPE>
any_insert_iterator<VALUETYPE>::any_insert_iterator(
    any_insert_iterator<VALUETYPE> const & rhs)
: dispatcher_(rhs.dispatcher_),
  opaqued_cntr_(rhs.opaqued_cntr_)
{
}

template <typename VALUETYPE>
any_insert_iterator<VALUETYPE>::~any_insert_iterator()
{
}

template <typename VALUETYPE>
any_insert_iterator<VALUETYPE> &
    any_insert_iterator<VALUETYPE>::operator=(
        any_insert_iterator<VALUETYPE> const & rhs)
{
    if(&rhs != this)
    {
        dispatcher_ = rhs.dispatcher_;
        opaqued_cntr_ = rhs.opaqued_cntr_;
    }

    return *this;
}

template <typename VALUETYPE>
any_insert_iterator<VALUETYPE> &
    any_insert_iterator<VALUETYPE>::operator=(const_reference value)
{
    dispatcher_(opaqued_cntr_, value);
    return *this;
}

template <typename VALUETYPE>
any_insert_iterator<VALUETYPE> &
    any_insert_iterator<VALUETYPE>::operator*()
{
    return *this;
}

template <typename VALUETYPE>
any_insert_iterator<VALUETYPE> &
    any_insert_iterator<VALUETYPE>::operator++()
{
    return *this;
}

template <typename VALUETYPE>
any_insert_iterator<VALUETYPE> &
    any_insert_iterator<VALUETYPE>::operator++(int)
{
    return *this;
}

namespace detail
{
template <typename CONTAINER, typename VALUETYPE>
void any_inserter_dispatch(
    void * opaqued_cntr,
    typename boost::remove_reference<VALUETYPE>::type const & value)
{
    CONTAINER * const cntr(static_cast<CONTAINER *>(opaqued_cntr));
    cntr->insert(value);
}
}

}

#endif /* WAVEGLIDER_CORE_ANYINSERTITERATOR_HH_ */
