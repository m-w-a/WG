#ifndef WAVEGLIDER_CORE_LAZYINITOR_HH_
#define WAVEGLIDER_CORE_LAZYINITOR_HH_

#include <unordered_set.hpp>
#include <algorithm>
#include <functional.hpp>

namespace WaveGlider
{
namespace Core
{

class ICachedValue
{
public:
    ICachedValue() {}
    virtual ~ICachedValue() {}

    virtual void reset() = 0;

private:
    //Purposefully declared and not defined.
    ICachedValue(ICachedValue const &);
    //Purposefully declared and not defined.
    ICachedValue & operator=(ICachedValue const &);
};

class ICachedMutators
{
public:
    ICachedMutators() {}
    virtual ~ICachedMutators() {}

    virtual void addCachedValue(ICachedValue &) = 0;

private:
    //Purposefully declared and not defined.
    ICachedMutators(ICachedMutators const &);
    ICachedMutators & operator=(ICachedMutators const &);
    //Purposefully declared and not defined.
};

template <typename M>
class CachedMutators : public ICachedMutators
{
public:
    CachedMutators();
    virtual ~CachedMutators();
    CachedMutators(CachedMutators const & rhs);
    CachedMutators & operator=(CachedMutators const & rhs);

    virtual void addCachedValue(ICachedValue & cachedValue);
    M & operator()();
    M const & operator()() const;

private:
    typedef std::tr1::unordered_set<ICachedValue *> ICachedValuePtrHashSet;

private:
    M m_Mutators;
    ICachedValuePtrHashSet m_CachedValues;
};

template <typename T, typename Initor>
class CachedValue2 : public ICachedValue
{
public:
    CachedValue2(
        ICachedMutators & mutator,
        Initor initor);
    CachedValue2(
        ICachedMutators & mutator,
        Initor initor,
        T & defaultValue);
    virtual ~CachedValue2();
    virtual void reset();
    T const & operator()() const;

private:
    //Purposefully declared and not defined.
    CachedValue2();
    //Purposefully declared and not defined.
    CachedValue2(CachedValue2 &);
    //Purposefully declared and not defined.
    CachedValue2 & operator=(CachedValue2 &);

private:
    mutable ICachedMutators & m_Mutator;
    mutable bool m_IsInit;
    Initor m_Initor;
    mutable T m_Value;
};

//Template Definitions.

//--------------
//CachedMutators
//--------------

template <typename M>
CachedMutators<M>::CachedMutators()
{
}

template <typename M>
CachedMutators<M>::~CachedMutators()
{
}

template <typename M>
CachedMutators<M>::CachedMutators(CachedMutators const & rhs)
: m_Mutators(rhs.m_Mutators)
{
}

template <typename M>
CachedMutators & CachedMutators<M>::operator=(CachedMutators const & rhs)
{
    if(this != &rhs)
    {
        m_Mutators = rhs.m_Mutators;
    }

    return *this;
}

template <typename M>
void CachedMutators<M>::addCachedValue(ICachedValue & cachedValue)
{
    m_CachedValues.insert(cachedValue);
}

template <typename M>
M & CachedMutators<M>::operator()()
{
    std::for_each(
        m_CachedValues.begin(),
        m_CachedValues.end(),
        std::tr1::bind(&ICachedValue::reset, _1));

    m_CachedValues.clear();

    return m_Mutators;
}

template <typename M>
M const & CachedMutators<M>::operator()() const
{
    return m_Mutators;
}

//-----------
//CachedValue2
//-----------

template <typename T, typename Initor>
CachedValue2<T, Initor>::CachedValue2(
    ICachedMutators & mutator,
    Initor initor)
: m_Mutator(mutator),
  m_IsInit(false),
  m_Initor(initor)
{
    m_Mutator.addCachedValue(*this);
}

template <typename T, typename Initor>
CachedValue2<T, Initor>::CachedValue2(
    ICachedMutators & mutator,
    Initor initor,
    T & value)
: m_Mutator(mutator),
  m_IsInit(true),
  m_Initor(initor),
  m_Value(value)
{
    m_Mutator.addCachedValue(*this);
}

template <typename T, typename Initor>
T const & CachedValue2<T, Initor>::operator()() const
{
    if(m_IsInit) { return m_Value; }
    else
    {
        m_Mutator.add(*this);
        m_Value = m_Initor();
        m_IsInit = true;
        return m_Value;
    }
}

template <typename T, typename Initor>
void CachedValue2<T, Initor>::reset()
{
    m_IsInit = false;
}

}
}

#endif /* WAVEGLIDER_CORE_LAZYINITOR_HH_ */
