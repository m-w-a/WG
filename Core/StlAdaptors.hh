#ifndef WAVEGLIDER_CORE_STLADAPTORS_HH_
#define WAVEGLIDER_CORE_STLADAPTORS_HH_

#include <functional>
#include <memory.hpp>

namespace WaveGlider
{
namespace Core
{

//Declared and purposefully not defined.
template <typename T>
struct LessByPointedToType;


template <typename T>
struct LessByPointedToType<T *>
{
    int operator()(T const & lhs, T const & rhs) const
    {
        return std::less<T>()(*lhs, *rhs);
    }
};

template <typename T>
struct LessByPointedToType< std::tr1::shared_ptr<T> >
{
    typedef std::tr1::shared_ptr<T> TSp;
    int operator()(TSp const & lhs, TSp const & rhs) const
    {
        return std::less<T>()(*lhs, *rhs);
    }
};

}
}

#endif //WAVEGLIDER_CORE_STLADAPTORS_HH_
