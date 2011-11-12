#ifndef WAVEGLIDER_CORE_EXCEPTIONS_HH_
#define WAVEGLIDER_CORE_EXCEPTIONS_HH_

#include <boost/cstdint.hpp>
#include <boost/filesystem.hpp>
#include <boost/exception/enable_current_exception.hpp>
#include <boost/current_function.hpp>
#include <boost/concept/assert.hpp>
#include <string>

#define WG_THROW_EX(OBJECT) \
    throw boost::enable_current_exception(OBJECT);

//T =
//  ErrorExceptT template instantiation
//KIND =
//  ErrorExceptionT::Kind, or, more conveniently
//  (ErrorExceptT template instantiation)::Kind
//MSG =
//  std::string
#define WG_THROW_ERROREX(TYPE, KIND, MSG) \
    throw boost::enable_current_exception( \
        TYPE( \
            KIND, \
            MSG, \
            BOOST_CURRENT_FUNCTION, \
            boost::filesystem::path(__FILE__).filename().string(), \
            __LINE__));

#define WG_RETHROW_EX() \
    boost::rethrow_exception(boost::current_exception());

namespace WaveGlider
{
namespace Core
{

namespace Requirements
{
namespace Check
{
template <typename T>
struct IsSuperClassExceptionT;
template <typename T>
struct IsHeirarchyRootedAtBaseExceptionT;
template <typename T>
struct IsSuperClassAbstractErrorExceptionT;
template <typename T>
struct IsAncestorClassBaseErrorExceptionT;
}
}

//Class Definitions.

//----------
//ExceptionT
//----------
//
//************
//Description:
//************
// ExceptionT specializations are all pure virtual classes.
// ExceptionT all have the following interface:
// IDTAG is a unique id identifying the template instantiation.
// PARENT must be an ExceptionT or omitted from the template parameter list.
//
//  template <typename IDTAG, typename PARENT = void>
//	class ExceptionT<...>
//	{
//	  public:
//    	ExceptionT() throw();
//    	ExceptionT(ExceptionT const &) throw();
//    	virtual ~ExceptionT() throw() = 0;
//		...
//	};
//
//******
//Usage:
//******
//	struct RootExTag;
//	typedef ExceptionT<RootExTag> RootEx;
//
//	//SomeProgenyEx will be derived from RootEx:
//
//	struct SomeProgenyExTax;
//	typedef ExceptionT<SomeProgenyExTax, RootEx> SomeProgenyEx;
//----------

template <typename TAG, typename PARENT = void>
class ExceptionT;

//Base Template Specialization.
template <typename TAG>
class ExceptionT<TAG, void>
{
public:
    ExceptionT() throw();
    ExceptionT(ExceptionT const &) throw();
    virtual ~ExceptionT() throw() = 0;
private:
    //Disallowed.
    ExceptionT & operator=(ExceptionT const &);
};

template <typename TAG, typename PARENT>
class ExceptionT : public PARENT
{
    BOOST_CONCEPT_ASSERT((
        Requirements::Check::IsHeirarchyRootedAtBaseExceptionT<PARENT>));
    BOOST_CONCEPT_ASSERT((
        Requirements::Check::IsSuperClassExceptionT<PARENT>));
public:
    ExceptionT() throw();
    ExceptionT(ExceptionT const &) throw();
    virtual ~ExceptionT() throw() = 0;
private:
    //Disallowed.
    ExceptionT & operator=(ExceptionT const &);
};

//---------------
//ErrorExceptionT
//---------------
//
//***********
//Description
//***********
// ErrorExceptionT all have the following interface:
// IDTAG is a unique id identifying the template instantiation.
// PARENT must be an ErrorExceptionT<..., ..., false> or an ExceptionT.
// ISCONCRETE = true makes an instantiable class.
//
//  template <
//    typename IDTAG,
//    typename PARENT,
//    bool ISCONCRETE = false>
//	class ErrorExceptionT<...>
//	{
//	public:
//    typedef enum KIND
//    {
//        LogicError,
//        RuntimeError,
//        InvalidArgumentError,
//        DomainError
//    } Kind;
//
//    ErrorExceptionT() throw() {}
//    ErrorExceptionT(ErrorExceptionT const &) throw() {}
//    virtual ~ErrorExceptionT() throw() {}
//
//    virtual Kind kind() const throw() = 0;
//    virtual std::string const & what() const throw() = 0;
//    virtual std::string const & functionName() const throw() = 0;
//    virtual std::string const & filename() const throw() = 0;
//    virtual boost::uint16_t lineNumber() const throw() = 0;
//	  ...
//	};
//
//******
//Usage:
//******
//	struct RootExceptionTag;
//	typedef ExceptionT<RootExceptionTag> RootException;
//
//	struct ErrorExceptionTag;
//	typedef ErrorExceptionT<
//		ErrorExceptionTag,
//		RootException,
//		true
//	> ErrorException;
//---------------

template <
    typename TAG,
    typename PARENT,
    bool ISCONCRETE = false>
class ErrorExceptionT;

//Base Specialization.
//Base specialization derives from ExceptionT.
//Base specialization needed in order to define nested types.
//Leaf specialization has class members and not this one so as to enable the
// former to directly derive from ExceptionT.
template <typename TAG, typename PARENTTAG, typename GRANDPARENT>
class ErrorExceptionT<TAG, ExceptionT<PARENTTAG, GRANDPARENT>, false> :
    public ExceptionT<PARENTTAG, GRANDPARENT>
{
public:
	//GCC WORKAROUND.
	//typedef needed and has to be different from enum name because of
    //using keyword bug, see "using ...::KIND" below.
    typedef enum KIND
    {
        LogicError,
        RuntimeError,
        InvalidArgumentError,
        DomainError
    } Kind;

public:
    ErrorExceptionT() throw() {}
    ErrorExceptionT(ErrorExceptionT const &) throw() {}
    virtual ~ErrorExceptionT() throw() {}

    virtual Kind kind() const throw() = 0;
    virtual std::string const & what() const throw() = 0;
    virtual std::string const & functionName() const throw() = 0;
    virtual std::string const & filename() const throw() = 0;
    virtual boost::uint16_t lineNumber() const throw() = 0;

private:
    //Disallowed.
    ErrorExceptionT & operator=(ErrorExceptionT const &) throw();
};

//Intermediate Specialization.
//Intermediate specializations derive from ErrorExceptionT.
template <typename TAG, typename PARENT>
class ErrorExceptionT<TAG, PARENT, false> : public PARENT
{
    BOOST_CONCEPT_ASSERT((
        Requirements::Check::IsSuperClassAbstractErrorExceptionT<PARENT>));
public:
    //Inject enum constants into this class's scope.
    using PARENT::KIND;
    typedef typename PARENT::Kind Kind;

public:
    ErrorExceptionT() throw() {}
    ErrorExceptionT(ErrorExceptionT const &) throw() {}
    virtual ~ErrorExceptionT() throw() {}

    virtual Kind kind() const throw() = 0;
    virtual std::string const & what() const throw() = 0;
    virtual std::string const & functionName() const throw() = 0;
    virtual std::string const & filename() const throw() = 0;
    virtual boost::uint16_t lineNumber() const throw() = 0;

private:
    //Disallowed.
    ErrorExceptionT & operator=(ErrorExceptionT const & ) throw();
};

namespace Internal
{
template <typename PARENT>
struct ErrorExceptionSuperClassSelector;

template <typename TAG, typename PARENT>
struct ErrorExceptionSuperClassSelector<ExceptionT<TAG, PARENT> >
{
    struct ErrorExceptionSuperClassSelectorTag;
    typedef ErrorExceptionT<
        ErrorExceptionSuperClassSelectorTag,
        ExceptionT<TAG, PARENT>
    > Selection;
};

template <typename TAG, typename PARENTTAG, typename GRANDPARENT>
struct ErrorExceptionSuperClassSelector<
	ErrorExceptionT<TAG, ExceptionT<PARENTTAG, GRANDPARENT>, false> >
{
	typedef 
    	ErrorExceptionT<TAG, ExceptionT<PARENTTAG, GRANDPARENT>, false>
        	Selection;
};

template <typename TAG, typename PARENT>
struct ErrorExceptionSuperClassSelector<
	ErrorExceptionT<TAG, PARENT, false> >
{
	typedef ErrorExceptionT<TAG, PARENT, false> Selection;
};
}

//Leaf Specialization.
template <typename TAG, typename PARENT>
class ErrorExceptionT<TAG, PARENT, true> :
    public Internal::ErrorExceptionSuperClassSelector<PARENT>::Selection
{
	typedef 
    	typename Internal::ErrorExceptionSuperClassSelector<PARENT>::Selection
        	INTERNALPARENT;
public:
    //Inject enum constants into this class's scope.
    using INTERNALPARENT::KIND;
    typedef typename INTERNALPARENT::Kind Kind;

public:
    ErrorExceptionT(
        Kind const errorKind,
        std::string const & errMsg,
        std::string const & functionName,
        std::string const & filename,
        boost::uint16_t const lineNumber) throw();
    ErrorExceptionT(ErrorExceptionT const & rhs) throw();
    virtual ~ErrorExceptionT() throw();

    virtual Kind kind() const throw();
    virtual std::string const & what() const throw();
    virtual std::string const & functionName() const throw();
    virtual std::string const & filename() const throw();
    virtual boost::uint16_t lineNumber() const throw();

private:
    //Disallowed.
    ErrorExceptionT() throw();
    //Disallowed.
    ErrorExceptionT & operator=(ErrorExceptionT const & ) throw();

private:
    Kind const m_Kind;
    std::string const m_What;
    std::string const m_FunctionName;
    std::string const m_Filename;
    boost::uint16_t const m_LineNumber;
};

//---------------------------
//Member Template Definitions.
//---------------------------

namespace Requirements
{
namespace Check
{

template <typename TAG, typename PARENT>
struct IsSuperClassExceptionT<ExceptionT<TAG, PARENT> >
{};

template <typename TAG, typename PARENT>
struct IsSuperClassAbstractErrorExceptionT<
	ErrorExceptionT<TAG, PARENT, false> >
{};

template <typename TAG>
struct IsHeirarchyRootedAtBaseExceptionT<ExceptionT<TAG, void> >
{};
template <typename TAG, typename PARENT>
struct IsHeirarchyRootedAtBaseExceptionT<ExceptionT<TAG, PARENT> > :
    public IsHeirarchyRootedAtBaseExceptionT<PARENT>
{};
}
}

//---------------------
//ExceptionT<TAG, void>
//---------------------

template <typename TAG>
ExceptionT<TAG, void>::ExceptionT() throw()
{
}

template <typename TAG>
ExceptionT<TAG, void>::ExceptionT(ExceptionT const &) throw()
{
}

template <typename TAG>
ExceptionT<TAG, void>::~ExceptionT() throw()
{
}

//----------
//ExceptionT
//----------

template <typename TAG, typename PARENT>
ExceptionT<TAG, PARENT>::ExceptionT() throw()
{
}

template <typename TAG, typename PARENT>
ExceptionT<TAG, PARENT>::ExceptionT(ExceptionT const &) throw()
{
}

template <typename TAG, typename PARENT>
ExceptionT<TAG, PARENT>::~ExceptionT() throw()
{
}

//----------------------------------
//ErrorExceptionT<TAG, PARENT, true>
//----------------------------------

template <typename TAG, typename PARENT>
ErrorExceptionT<TAG, PARENT, true>::ErrorExceptionT(
    Kind const errorKind,
    std::string const & errMsg,
    std::string const & functionName,
    std::string const & filename,
    boost::uint16_t const lineNumber) throw()
: INTERNALPARENT(),
  m_Kind(errorKind),
  m_What(errMsg),
  m_FunctionName(functionName),
  m_Filename(filename),
  m_LineNumber(lineNumber)
{
}

template <typename TAG, typename PARENT>
ErrorExceptionT<TAG, PARENT, true>::ErrorExceptionT(
    ErrorExceptionT const & rhs) throw()
: INTERNALPARENT(rhs),
  m_Kind(rhs.m_Kind),
  m_What(rhs.m_What),
  m_FunctionName(rhs.m_FunctionName),
  m_Filename(rhs.m_Filename),
  m_LineNumber(rhs.m_LineNumber)
{
}

template <typename TAG, typename PARENT>
ErrorExceptionT<TAG, PARENT, true>::~ErrorExceptionT() throw()
{
}

template <typename TAG, typename PARENT>
typename ErrorExceptionT<TAG, PARENT, true>::Kind 
	ErrorExceptionT<TAG, PARENT, true>::kind() const throw()
{
	return m_Kind;
}

template <typename TAG, typename PARENT>
std::string const & ErrorExceptionT<TAG, PARENT, true>::what() const throw()
{
    return m_What;
}

template <typename TAG, typename PARENT>
std::string const &
    ErrorExceptionT<TAG, PARENT, true>::functionName() const throw()
{
    return m_FunctionName;
}

template <typename TAG, typename PARENT>
std::string const &
    ErrorExceptionT<TAG, PARENT, true>::filename() const throw()
{
    return m_Filename;
}

template <typename TAG, typename PARENT>
boost::uint16_t ErrorExceptionT<TAG, PARENT, true>::lineNumber() const throw()
{
    return m_LineNumber;
}

}
}

#endif /* WAVEGLIDER_CORE_HH_ */
