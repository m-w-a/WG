#ifndef WAVEGLIDER_CORE_SIMPLELAZYINITOR_HH_
#define WAVEGLIDER_CORE_SIMPLELAZYINITOR_HH_

namespace WaveGlider
{
namespace Core
{

//-----------
//CachedValue
//-----------

template <typename T, typename Initor>
class CachedValue
{
public:
    explicit CachedValue(Initor initor);
    CachedValue(Initor initor, T & value);
    CachedValue(CachedValue & rhs);
    ~CachedValue();
    CachedValue & operator=(CachedValue & rhs);
    T const & operator()() const;
    void reset();

private:
    //Purposefully declared and not defined.
    CachedValue();

private:
    mutable bool m_IsInit;
    Initor m_Initor;
    mutable T m_Value;
};

//Template Definitions.

//-----------
//CachedValue
//-----------

template <typename T, typename Initor>
CachedValue<T, Initor>::(Initor initor)
: m_IsInit(false),
  m_Initor(initor)
{
}

template <typename T, typename Initor>
CachedValue<T, Initor>::CachedValue(Initor initor, T & value)
: m_IsInit(true),
  m_Initor(initor),
  m_Value(value)
{
}

template <typename T, typename Initor>
CachedValue<T, Initor>::CachedValue(CachedValue & rhs)
: m_IsInit(rhs.m_IsInit),
  m_Initor(rhs.m_Initor),
  m_Value(rhs.m_Value)
{
}

template <typename T, typename Initor>
CachedValue<T, Initor>::~CachedValue()
{
}

template <typename T, typename Initor>
CachedValue & CachedValue<T, Initor>::operator=(CachedValue & rhs)
{
    if(this != &rhs)
    {
        m_IsInit = rhs.m_IsInit;
        m_Value = rhs.m_Value;
    }

    return *this;
}

template <typename T, typename Initor>
T const & CachedValue<T, Initor>::operator()() const
{
    if(m_IsInit) { return m_Value; }
    else
    {
        m_Value = m_Initor();
        m_IsInit = true;
        return m_Value;
    }
}

template <typename T, typename Initor>
void CachedValue<T, Initor>::reset()
{
    m_IsInit = false;
}

}
}

#endif /* WAVEGLIDER_CORE_SIMPLELAZYINITOR_HH_ */
