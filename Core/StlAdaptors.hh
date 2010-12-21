#ifndef WAVEGLIDER_CORE_STLADAPTORS_HH_
#define WAVEGLIDER_CORE_STLADAPTORS_HH_

#include <functional>
#include <iterator>
#include <utility>
#include <type_traits.hpp>
#include <boost/utility/compare_pointees.hpp>
#include <boost/pointee.hpp>
#include <boost/iterator/transform_iterator.hpp>

namespace WaveGlider
{
namespace Core
{

//Types.

--
// If both x and y have valid pointees, returns the result of (*x == *y)
// If only one has a valid pointee, returns false.
// If none have valid pointees, returns true.
// No-throw
template<class Pointer>
inline
bool equal_pointees(Pointer const & x, Pointer const & y)
{
    return (!x) != (!y) ? false : ( !x ? true : (*x) == (*y) );
}

template <
    class Pointer,
    class PointeeEquals = std::equal_to<typename boost::pointee<Pointer>::type> >
struct equal_pointees_t: std::binary_function<Pointer, Pointer, bool>
{
    bool operator()(Pointer const & x, Pointer const & y) const
    {
        return (!x) != (!y) ? false : ( !x ? true : m_PointeesEqual(*x, *y) );
    }

    PointeeEquals m_PointeeEquals;
};

--
template<class Pointer>
inline
bool less_pointees(Pointer const & x, Pointer const & y)
{
    return !y ? false : ( !x ? true : (*x) < (*y) );
}

template<
    class Pointer,
    class PointeeLess = std::less<typename boost::pointee<Pointer>::type> >
struct less_pointees_t : public std::binary_function<Pointer, Pointer, bool>
{
    bool operator()(Pointer const & x, Pointer const & y) const
    {
        return !y ? false : ( !x ? true : pointeeLess(*x, *y) );
    }

    PointeeLess m_PointeeLess;
};

--
template <typename T>
struct StdContainerValueAccess
{
    typedef typename T::value_type Type;
};

template <typename T>
struct StdContainerValueAccess<T const>
{
    typedef typename std::tr1::add_const<typename T::value_type>::type Type;
};

--
template <typename Iterator>
struct TakeSecondIteratorAdaptor
{
    template<typename T1, typename T2>
    struct TakeSecond
    {
        typedef T2 result_type;

        result_type operator()(std::pair<T1, T2> const & pair) const
        {
          return pair.second;
        }
    };

    typedef typename std::iterator_traits<Iterator>::value_type Pair;
    typedef typename Pair::first_type FirstType;
    typedef typename Pair::second_type SecondType;
    typedef TakeSecond<FirstType, SecondType> UnaryFunction;
    typedef boost::transform_iterator<UnaryFunction, Iterator> TransformIterator;

    TransformIterator operator()(Iterator const & it) const
    {
        return boost::make_transform_iterator(it, UnaryFunction());
    }
};

template <typename Iterator>
struct VectorPtrToArrayIteratorAdaptor
{
    template <typename VectorPtr>
    struct VectorPtrToArray
    {
        typedef typename boost::pointee<VectorPtr>::type vector;
        typedef typename StdContainerValueAccess<vector>::Type * result_type;

        result_type operator()(VectorPtr const spVector) const
        {
            return &((*spVector)[0]);
        }
    };

    typedef typename std::iterator_traits<Iterator>::value_type VectorPtr;
    typedef VectorPtrToArray<VectorPtr> UnaryFunction;
    typedef boost::transform_iterator<UnaryFunction, Iterator> TransformIterator;

    TransformIterator operator()(Iterator const & it) const
    {
        return boost::make_transform_iterator(it, UnaryFunction());
    }
};

//Functions

template <typename Iterator>
typename TakeSecondIteratorAdaptor<Iterator>::TransformIterator
    mappedTypeIteratorAdapt(Iterator const & it)
{
    return TakeSecondIteratorAdaptor<Iterator>()(it);
}

template <typename Iterator>
typename VectorPtrToArrayIteratorAdaptor<Iterator>::TransformIterator
    makeArrayIteratorFromVectorPtrIterator(Iterator const & it)
{
    return VectorPtrToArrayIteratorAdaptor<Iterator>()(it);
}

}
}

#endif //WAVEGLIDER_CORE_STLADAPTORS_HH_
