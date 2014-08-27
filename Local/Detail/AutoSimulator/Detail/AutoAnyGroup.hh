#ifndef WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_HH_
#define WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_HH_

#include <cstddef>
#include <boost/tuple/tuple.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/at.hpp>
#include <boost/aligned_storage.hpp>
#include <boost/type_traits/alignment_of.hpp>
#include <boost/move/utility.hpp>
#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/PP/Seq.hh>
#include <WG/Local/Detail/AutoSimulator/Detail/AutoAny.hh>

//###########
//Public APIs
//###########

#ifndef WG_AUTOSIMULATOR_AUTOANYGROUP_CONFIG_PARAMS_MAX_ARITY
  #define WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_CONFIG_PARAMS_MAX_ARITY 11
#else
  #define WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_CONFIG_PARAMS_MAX_ARITY \
    BOOST_PP_INC(WG_AUTOSIMULATOR_AUTOANYGROUP_CONFIG_PARAMS_MAX_ARITY)
#endif

#define WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_MAKEGROUP(exprseq) \
  WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_MAKEGROUP_IMPL(exprseq)

#define WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_MAKECUSTOMGROUP( \
  baseclass, exprseq) \
    WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_MAKECUSTOMGROUP_IMPL( \
      baseclass, exprseq)

#define WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_INITGROUP( \
  opaqued_group, mutable_boolean_flag, exprseq) \
    WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_INITGROUP_IMPL( \
      opaqued_group, mutable_boolean_flag, exprseq)

#define WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_ITEM_VALUE( \
  opaqued_group, itemno, exprseq) \
    WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_ITEM_VALUE_IMPL( \
      opaqued_group, itemno, exprseq)

#define WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_ITEM_ISRVALUE( \
  opaqued_group, itemno, exprseq) \
    WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_ITEM_ISRVALUE_IMPL( \
      opaqued_group, itemno, exprseq)

//####
//Impl
//####

//----------------------------------------------
//WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_MAKEGROUP
//----------------------------------------------

#define WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_MAKEGROUP_IMPL(exprseq) \
  WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_MAKECUSTOMGROUP( \
    ::wg::autosimulator::detail::auto_any_group, \
     exprseq)

//----------------------------------------------------
//WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_MAKECUSTOMGROUP
//----------------------------------------------------

#define WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_MAKECUSTOMGROUP_IMPL( \
  baseclass, exprseq) \
    ::wg::autosimulator::detail::make_group \
     < \
       baseclass \
     > \
     ( \
       WG_PP_SEQ_ENUM( \
         WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_DEDUCEDAUTOANYIMPLPTRSEQ(exprseq)) \
     )

//---------------------------------------------
//WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_GETGROUP
//---------------------------------------------

#define WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_GETGROUP(opaqued_group, exprseq) \
  ::wg::autosimulator::detail::get_group( \
    opaqued_group \
    WG_PP_SEQ_ENUM_TRAILING( \
      WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_DEDUCEDAUTOANYIMPLPTRSEQ(exprseq)) )

//-------------------------------------------------------------------
//WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_AAGIMPL_PARTIALSPECIALIZATIONS
//-------------------------------------------------------------------

#define WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_AAGIMPL_PARTIALSPECIALIZATIONS( \
  argn) \
    BOOST_PP_REPEAT( \
      argn, \
      WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_AAGIMPL_PARTIALSPECIALIZATIONS_DEF, \
      ~)

// TODO: make this a non-PPMP class.
//   Just have to figure out how to make a tuple of aligned_storage<auto_any_impl>
//   from AutoAnyImplTypeVec.
//   Additionally, would finalize have to be public, or can we friend the
//   recursive metafunction?
#define WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_AAGIMPL_PARTIALSPECIALIZATIONS_DEF( \
  z, argn, data) \
    template \
    < \
      typename Base, \
      typename AutoAnyImplTypeVec \
    > \
    class auto_any_group_impl<argn, Base, AutoAnyImplTypeVec> : public Base \
    { \
    public: \
      typedef auto_any_group_impl<argn, Base, AutoAnyImplTypeVec> this_type; \
      WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_AAGIMPL_ITEMTYPENAME_DCLNS( \
        argn, AutoAnyImplTypeVec) \
    public: \
      /* Note: */ \
      /* Default default ctor and copy assignment will make bit-wise copies. */ \
      ~auto_any_group_impl() \
      { \
        WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_AAGIMPL_FINALIZE_DCLNS(argn) \
        WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_AAGIMPL_DESTRUCT_DCLNS(argn) \
      } \
      \
      template <std::size_t I> \
      this_type const & capture( \
        /* Purposefully capture by value so as to enable copy elision. */ \
        BOOST_DEDUCED_TYPENAME boost::mpl::at \
        < \
          AutoAnyImplTypeVec, \
          boost::mpl::int_<I> \
        >::type wrapped_obj) const \
      { \
        typedef BOOST_DEDUCED_TYPENAME \
          boost::mpl::at<AutoAnyImplTypeVec, boost::mpl::int_<I> >::type \
            item_type; \
        ::new(this->m_items.template get<I>().address()) \
          item_type( ::boost::move(wrapped_obj) ); \
        \
        return *this; \
      } \
      \
      template <std::size_t I> \
      BOOST_DEDUCED_TYPENAME boost::mpl::at \
      < \
        AutoAnyImplTypeVec, \
        boost::mpl::int_<I> \
      >::type & \
        captured_obj() const \
      { \
        typedef BOOST_DEDUCED_TYPENAME \
          boost::mpl::at<AutoAnyImplTypeVec, boost::mpl::int_<I> >::type \
            item_type; \
        return *static_cast<item_type *>( \
          this->m_items.template get<I>().address()); \
      } \
      \
    private: \
      typedef ::boost::tuple \
      < \
        WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_AAGIMPL_ALIGNEDSTORAGELIST(argn) \
      > AlignedStorageTuple; \
    private: \
      mutable AlignedStorageTuple m_items; \
    };

//~~~~~~~~~~~~~~~
// ItemTypeNames.
//~~~~~~~~~~~~~~~

#define WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_AAGIMPL_ITEMTYPENAME(indx) \
  BOOST_PP_CAT(item_type, indx)

#define WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_AAGIMPL_ITEMTYPENAME_DCLNS( \
  argn, typevector) \
    BOOST_PP_REPEAT( \
      argn, \
      WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_AAGIMPL_ITEMTYPENAME_DCLN, \
      typevector)

// BOOST_PP_REPEAT functor.
#define WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_AAGIMPL_ITEMTYPENAME_DCLN( \
  z, argno, typevector) \
    typedef BOOST_DEDUCED_TYPENAME ::boost::mpl::at \
    < \
      typevector, \
      ::boost::mpl::int_<argno> \
    >::type \
      WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_AAGIMPL_ITEMTYPENAME(argno) ;

//~~~~~~~~~~~~~~~~~~~~~~~~~
// AlignedStorageTupleList.
//~~~~~~~~~~~~~~~~~~~~~~~~~

// typenamemacro:
//   A 1-arg function macro that when invoked with an unsigned integer expands
//   to a type for which an aligned_storage class should be instantiated.
#define WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_AAGIMPL_ALIGNEDSTORAGELIST(argn) \
  BOOST_PP_ENUM( \
    argn, \
    WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_AAGIMPL_ALIGNEDSTORAGELIST_ENTRY, \
    WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_AAGIMPL_ITEMTYPENAME)

// BOOST_PP_ENUM functor.
#define WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_AAGIMPL_ALIGNEDSTORAGELIST_ENTRY( \
  z, argno, typenamemacro) \
    BOOST_DEDUCED_TYPENAME ::boost::aligned_storage \
    < \
      sizeof( typenamemacro(argno) ), \
      ::boost::alignment_of< typenamemacro(argno) >::value \
    >::type

//~~~~~~~~~~~~~~
// Finalization.
//~~~~~~~~~~~~~~

#define WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_AAGIMPL_FINALIZE_DCLNS(argn) \
  WG_PP_SEQ_FLATTEN( \
    WG_PP_SEQ_REVERSE( \
      (()) (BOOST_PP_EMPTY) \
      BOOST_PP_REPEAT(\
        argn, \
        WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_AAGIMPL_FINALIZE_DCLN, \
        ~) ))

// BOOST_PP_REPEAT functor.
#define WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_AAGIMPL_FINALIZE_DCLN( \
  z, argno, data) \
    ( \
      this->finalize( this->captured_obj<argno>() ); \
    )

//~~~~~~~~~~~~~
// Destruction.
//~~~~~~~~~~~~~

#define WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_AAGIMPL_DESTRUCT_DCLNS(argn) \
  WG_PP_SEQ_FLATTEN( \
    WG_PP_SEQ_REVERSE( \
      (()) (BOOST_PP_EMPTY) \
      BOOST_PP_REPEAT(\
        argn, \
        WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_AAGIMPL_DESTRUCT_DCLN, \
        ~) ))

// BOOST_PP_REPEAT functor.
#define WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_AAGIMPL_DESTRUCT_DCLN( \
  z, argno, data) \
    ( \
      destruct( this->captured_obj<argno>() ); \
    )

//-------------------
//AutoAnyImplTplUtils
//-------------------

//~~~~~~~~~~~~
//TPLPARAMNAME
//~~~~~~~~~~~~

#define WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_AUTOANYIMPLTPL_PARAMNAME(indx) \
  BOOST_PP_CAT(auto_any_impl, indx)

//~~~~~~~~~~~~~~~~~~~~
//TRAILINGTPLPARAMLIST
//~~~~~~~~~~~~~~~~~~~~

#define WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_AUTOANYIMPLTPL_TRAILINGTPLPARAMLIST( \
  argn) \
  BOOST_PP_ENUM_TRAILING( \
    argn, \
    WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_AUTOANYIMPLTPL_TRAILINGTPLPARAMLIST_ENTRY, \
    WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_AUTOANYIMPLTPL_PARAMNAME)

// BOOST_PP_ENUM_TRAILING functor.
#define \
  WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_AUTOANYIMPLTPL_TRAILINGTPLPARAMLIST_ENTRY( \
    z, indx, tplparamname) \
      typename tplparamname(indx)

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//TPLPARAMNAMELIST_AUTOANYIMPL
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#define WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_AUTOANYIMPLTPL_PARAMNAMELIST(argn) \
  BOOST_PP_ENUM( \
    argn, \
    WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_AUTOANYIMPLTPL_PARAMNAMELIST_ENTRY, \
    WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_AUTOANYIMPLTPL_PARAMNAME)

// BOOST_PP_ENUM functor.
#define WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_AUTOANYIMPLTPL_PARAMNAMELIST_ENTRY( \
  z, indx, tplparamname) \
    tplparamname(indx)

//~~~~~~~~~~~~~~~~~~~~~~~~
//PARAMLIST_AUTOANYIMPLPTR
//~~~~~~~~~~~~~~~~~~~~~~~~

#define WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_AUTOANYIMPLTPL_PTRPARAMLIST(argn) \
  BOOST_PP_ENUM( \
    argn, \
    WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_AUTOANYIMPLTPL_PTRPARAMLIST_ENTRY, \
    WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_AUTOANYIMPLTPL_PARAMNAME)

// BOOST_PP_ENUM functor.
#define WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_AUTOANYIMPLTPL_PTRPARAMLIST_ENTRY( \
  z, indx, tplparamname) \
    tplparamname(indx) *

//------------------------
//DEDUCEDAUTOANYIMPLPTRSEQ
//------------------------

#define WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_DEDUCEDAUTOANYIMPLPTRSEQ(exprseq) \
  WG_PP_SEQ_FOR_EACH( \
    WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_DEDUCEDAUTOANYIMPLPTRSEQ_ENTRY, \
    ~, \
    exprseq)

#define WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_DEDUCEDAUTOANYIMPLPTRSEQ_ENTRY( \
  r, data, expr) \
    ( \
      WG_AUTOSIMULATOR_DETAIL_AUTOANY_AUTOANYIMPL_DEDUCEDPTRTYPE(expr) \
    )

//----------------------------------------------------------
//WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_MAKEGROUP_DEFINITIONS
//----------------------------------------------------------

#define WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_MAKEGROUP_DEFINITIONS(argn) \
  BOOST_PP_REPEAT( \
    argn, \
    WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_MAKEGROUP_DEFINITIONS_DEF, \
    ~)

#define WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_MAKEGROUP_DEFINITIONS_DEF( \
  z, argn, data) \
  template \
  < \
    typename Base \
    WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_AUTOANYIMPLTPL_TRAILINGTPLPARAMLIST(argn) \
  > \
  inline auto_any_group_impl \
  < \
    argn, \
    Base, \
    ::boost::mpl::vector \
    < \
      WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_AUTOANYIMPLTPL_PARAMNAMELIST(argn) \
    > \
  > \
    make_group(WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_AUTOANYIMPLTPL_PTRPARAMLIST(argn)) \
    { \
      typedef ::boost::mpl::vector \
      < \
        WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_AUTOANYIMPLTPL_PARAMNAMELIST(argn) \
      > auto_any_impl_typevec; \
      \
      return auto_any_group_impl<argn, Base, auto_any_impl_typevec>(); \
    }

//---------------------------------------------------------
//WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_GETGROUP_DEFINITIONS
//---------------------------------------------------------

#define WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_GETGROUP_DEFINITIONS(argn) \
  BOOST_PP_REPEAT( \
    argn, \
    WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_GETGROUP_DEFINITIONS_DEF, \
    ~)

#define WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_GETGROUP_DEFINITIONS_DEF( \
  z, argn, data) \
  template \
  < \
    typename Base \
    WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_AUTOANYIMPLTPL_TRAILINGTPLPARAMLIST(argn) \
  > \
  inline auto_any_group_impl \
  < \
    argn, \
    Base, \
    ::boost::mpl::vector \
    < \
      WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_AUTOANYIMPLTPL_PARAMNAMELIST(argn) \
    > \
  > const & \
    get_group( \
      Base const & opaqued_group BOOST_PP_COMMA_IF(argn) \
      WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_AUTOANYIMPLTPL_PTRPARAMLIST(argn) ) \
    { \
      typedef ::boost::mpl::vector \
      < \
        WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_AUTOANYIMPLTPL_PARAMNAMELIST(argn) \
      > auto_any_impl_typevec; \
      \
      typedef auto_any_group_impl \
      < \
        argn, \
        Base, \
        auto_any_impl_typevec \
      > group_type; \
      \
      return static_cast<group_type const &>(opaqued_group); \
    }

//----------------------------------------------
//WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_INITGROUP
//----------------------------------------------

#define WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_INITGROUP_IMPL( \
  opaqued_group, mutable_boolean_flag, exprseq) \
    BOOST_PP_EXPR_IIF( \
      BOOST_PP_COMPL( \
        WG_PP_SEQ_ISNIL(exprseq)), \
        WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_GETGROUP(opaqued_group, exprseq) ) \
    WG_PP_SEQ_NOTHING_FOR_EACH_I( \
      WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_INITGROUP_ENTRY, \
      mutable_boolean_flag, \
      exprseq) ;

// WG_PP_SEQ_FOR_EACH functor.
#define WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_INITGROUP_ENTRY( \
  r, mutable_boolean_flag, indx, expr) \
    . capture<indx>( \
      WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CAPTURE(expr, mutable_boolean_flag) )

//----------------------------------------------
//WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_ITEM_VALUE
//----------------------------------------------

#define WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_ITEM_VALUE_IMPL( \
  opaqued_group, itemno, exprseq) \
    WG_AUTOSIMULATOR_DETAIL_AUTOANY_AUTOANYIMPL_VALUE \
    ( \
      WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_GETGROUP( \
        opaqued_group, exprseq) . captured_obj<itemno>() \
    )

//--------------------------------------------------
//WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_ITEM_ISRVALUE
//--------------------------------------------------

#define WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_ITEM_ISRVALUE_IMPL( \
  opaqued_group, itemno, exprseq) \
    WG_AUTOSIMULATOR_DETAIL_AUTOANY_AUTOANYIMPL_ISRVALUE \
    ( \
      WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_GETGROUP( \
        opaqued_group, exprseq) . captured_obj<itemno>() \
    )

namespace wg
{
namespace autosimulator
{
namespace detail
{

//--------------
//auto_any_group
//--------------

struct auto_any_group
{
  // auto_any must evaluate to false in boolean contexts so that
  // they can be declared in if() statements.
  operator bool() const
  {
    return false;
  }

protected:
  template <typename T>
  void finalize(T &)
  {
  }
};

//--------
//destruct
//--------

template <typename T>
void destruct(T & obj)
{
  obj.~T();
}

//-------------------
//auto_any_group_impl
//-------------------

template
<
  std::size_t N,
  typename Base,
  typename AutoAnyImplTypeVec
>
class auto_any_group_impl;

// Partial Specializations.
WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_AAGIMPL_PARTIALSPECIALIZATIONS( \
  WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_CONFIG_PARAMS_MAX_ARITY)

//----------
//make_group
//----------
WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_MAKEGROUP_DEFINITIONS( \
  WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_CONFIG_PARAMS_MAX_ARITY)

//---------
//get_group
//---------
WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_GETGROUP_DEFINITIONS( \
  WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_CONFIG_PARAMS_MAX_ARITY)

}
}
}

#endif /* WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_HH_ */
