#ifndef WG_PP_FORWARDER_HH_
#define WG_PP_FORWARDER_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/PP.hh>
#include <WG/Local/Detail/BackEnd/SymbolTable.hh>
#include <WG/Local/Detail/BackEnd/Type.hh>

//###########
//Public APIs
//###########

//###########
//Impl Macros
//###########

#define WG_PP_FORWARDER_DCLN_IMPL( \
  frwdr_typename, frwdr_objname, symbtbl) \
    struct frwdr_typename \
    { \
    private: \
      WG_PP_FORWARDER_TYPE_MEMBERDCLNS(symbtbl) \
    public: \
      WG_PP_FORWARDER_TYPE_CTOR_DCLN(frwdr_typename, symbtbl) \
      WG_PP_PARAMPROXY_TYPE_ACCESSORS(symbtbl) \
    } WG_PP_IDENTITY(;) \
    frwdr_typename const & frwdr_objname = \
      frwdr_typename \
      BOOST_PP_LPAREN() \
        WG_PP_FORWARDER_OBJ_INITLIST(symbtbl) \
      BOOST_PP_RPAREN() WG_PP_IDENTITY(;)

//------------
//Common Utils
//------------

#define WG_PP_FORWARDER_TYPE_MEMBERVAR_NAME(rootname, indx) \
  BOOST_PP_CAT(rootname, indx)

#define WG_PP_FORWARDER_TYPE_ACCESSORVARNAME(membervar_rootname, indx) \
  BOOST_PP_CAT( \
    BOOST_PP_CAT(getXXX, membervar_rootname), \
    indx)

#define WG_PP_FORWARDER_TYPE_MEMBERVAR_ASSIGNEEROOTNAME() assignee
#define WG_PP_FORWARDER_TYPE_MEMBERVAR_BOUNDPARAMROOTNAME() boundparam
#define WG_PP_FORWARDER_TYPE_MEMBERVAR_SETPARAMROOTNAME() setparam
#define WG_PP_FORWARDER_TYPE_MEMBERVAR_BOUNDMEMROOTNAME() boundmem
#define WG_PP_FORWARDER_TYPE_MEMBERVAR_SETMEMROOTNAME() setmem

// transform:
//   a WG_PP_SEQ_FOR_EACH_I that will be passed the following params:
//     data: membervarrootname
//     elem: explicit_or_deduced_type
#define WG_PP_FORWARDER_TYPE_MEMBERTYPECNGRNCECLASS_COMMONTRANSFORM( \
  symbtbl, transform, process_assignto) \
    BOOST_PP_EXPR_IIF( \
      process_assignto, \
      WG_PP_SEQ_IFNIL_THENCLEAR( \
        WG_PP_SEQ_FOR_EACH_I( \
          transform, \
          WG_PP_FORWARDER_TYPE_MEMBERVAR_ASSIGNEEROOTNAME(), \
          WG_PP_SYMBOLTABLE_ASSIGNEDTO_TYPE(symbtbl)))) \
    WG_PP_SEQ_IFNIL_THENCLEAR( \
      WG_PP_SEQ_FOR_EACH_I( \
        transform, \
        WG_PP_FORWARDER_TYPE_MEMBERVAR_BOUNDPARAMROOTNAME(), \
        WG_PP_SYMBOLTABLE_PARAMBIND_TYPES(symbtbl))) \
    WG_PP_SEQ_IFNIL_THENCLEAR( \
      WG_PP_SEQ_FOR_EACH_I( \
        transform, \
        WG_PP_FORWARDER_TYPE_MEMBERVAR_SETPARAMROOTNAME(), \
        WG_PP_SYMBOLTABLE_PARAMSET_TYPES(symbtbl))) )

//-----------
//MemberDclns
//-----------

#define WG_PP_FORWARDER_TYPE_MEMBERDCLNS(symbtbl) \
  WG_PP_FORWARDER_TYPE_MEMBERVAR_ASSIGNEEDCLN(symbtbl) \
  WG_PP_FORWARDER_TYPE_MEMBERTYPECNGRNCECLASS_COMMONTRANSFORM( \
    symbtbl, \
    WG_PP_FORWARDER_TYPE_MEMBERDCLN, \
    0)

// Do not use WG_PP_FORWARDER_TYPE_MEMBERDCLN since we only want a reference to
//   the assignee.
#define WG_PP_FORWARDER_TYPE_MEMBERVAR_ASSIGNEEDCLN(symbtbl) \
  BOOST_PP_EXPR_IIF( \
    WG_PP_SYMBOLTABLE_ASSIGNEDTO_EXISTS(symbtbl), \
    WG_PP_PARSEDTYPE_IFNONLOCAL_ADDREFERENCE( \
      BOOST_PP_TUPLE_ELEM(1, 0, WG_PP_SYMBOLTABLE_ASSIGNEDTO_TYPE(symbtbl)) ) \
    WG_PP_FORWARDER_TYPE_MEMBERVAR_ASSIGNEEROOTNAME() ; )

// WG_PP_SEQ_FOR_EACH_I functor.
#define WG_PP_FORWARDER_TYPE_MEMBERDCLN(r, varrootname, indx, e_or_d_type) \
  WG_PP_PARSEDTYPE_IFNONLOCAL_ADDCONSTADDREFERENCE(e_or_d_type) \
  WG_PP_FORWARDER_TYPE_MEMBERVAR_NAME(varrootname, indx) WG_PP_IDENTITY(;)

//----------
//Ctor Utils
//----------

#define WG_PP_FORWARDER_TYPE_CTOR_PARAMVARNAME(membervar_rootname, indx) \
  BOOST_PP_CAT( \
    BOOST_PP_CAT(paramXXX, membervar_rootname), \
    indx)

//----------
//Ctor Dcln
//----------

#define WG_PP_FORWARDER_TYPE_CTOR_DCLN(frwdr_typename, symbtbl) \
  frwdr_typename \
    BOOST_PP_LPAREN() \
      WG_PP_FORWARDER_TYPE_CTOR_PARAMLIST(symbtbl) \
    BOOST_PP_RPAREN() \
    WG_PP_FORWARDER_TYPE_CTOR_INITLIST(symbtbl) \
    {}

//---------------
//Ctor Param List
//---------------

#define WG_PP_FORWARDER_TYPE_CTOR_PARAMLIST(symbtbl) \
  BOOST_PP_EXPR_IF( \
    WG_PP_SYMBOLTABLE_TOTALXXX_SIZE(symbtbl), \
    WG_PP_FORWARDER_TYPE_CTOR_PARAMLIST_1, \
    WG_PP_FORWARDER_TYPE_CTOR_PARAMLIST_0) (symbtbl)

#define WG_PP_FORWARDER_TYPE_CTOR_PARAMLIST_0(symbtbl)
// There will be at least 1 entry, therefore no worries as to empty macro args
//   to WG_PP_SEQ_ENUM
#define WG_PP_FORWARDER_TYPE_CTOR_PARAMLIST_1(symbtbl) \
  WG_PP_SEQ_ENUM( \
    WG_PP_FORWARDER_TYPE_MEMBERTYPECNGRNCECLASS_COMMONTRANSFORM( \
      symbtbl, \
      WG_PP_FORWARDER_TYPE_CTOR_PARAMLIST_ENTRY, \
      1) )

// WG_PP_SEQ_FOR_EACH_I functor.
#define WG_PP_FORWARDER_TYPE_CTOR_PARAMLIST_ENTRY( \
  r, membervar_rootname, indx, e_or_d_type) \
    BOOST_PP_LPAREN() \
      WG_PP_PARSEDTYPE_IFNONLOCAL_ADDCONSTADDREFERENCE(e_or_d_type) \
      WG_PP_FORWARDER_TYPE_CTOR_PARAMVARNAME(membervar_rootname, indx) \
    BOOST_PP_RPAREN()

//--------------
//Ctor Init List
//--------------

#define WG_PP_FORWARDER_TYPE_CTOR_INITLIST(symbtbl) \
  BOOST_PP_EXPR_IF( \
    WG_PP_SYMBOLTABLE_TOTALXXX_SIZE(symbtbl), \
    WG_PP_FORWARDER_TYPE_CTOR_INITLIST_1, \
    WG_PP_FORWARDER_TYPE_CTOR_INITLIST_0) (symbtbl)

#define WG_PP_FORWARDER_TYPE_CTOR_INITLIST_0(symbtbl)
// There will be at least 1 entry, therefore no worries as to empty macro args
//   to WG_PP_SEQ_ENUM
#define WG_PP_FORWARDER_TYPE_CTOR_INITLIST_1(symbtbl) \
  WG_PP_IDENTITY(:) \
  WG_PP_SEQ_ENUM( \
    WG_PP_FORWARDER_TYPE_MEMBERTYPECNGRNCECLASS_COMMONTRANSFORM( \
      symbtbl, \
      WG_PP_FORWARDER_TYPE_CTOR_INITLISTENTRY, \
      1))

// WG_PP_SEQ_FOR_EACH_I functor.
#define WG_PP_FORWARDER_TYPE_CTOR_INITLISTENTRY( \
  r, membervar_rootname, indx, ignore_elem) \
    BOOST_PP_LPAREN() \
      WG_PP_FORWARDER_TYPE_MEMBERVAR_NAME(membervar_rootname, indx) \
      BOOST_PP_LPAREN() \
        WG_PP_FORWARDER_TYPE_CTOR_PARAMVARNAME(membervar_rootname, indx) \
      BOOST_PP_RPAREN() \
    BOOST_PP_RPAREN()

//---------
//Accessors
//---------

#define WG_PP_FORWARDER_TYPE_ACCESSORS(symbtbl) \
  WG_PP_FORWARDER_TYPE_MEMBERTYPECNGRNCECLASS_COMMONTRANSFORM( \
    symbtbl, \
    WG_PP_FORWARDER_TYPE_ACCESSORDCLN, \
    1)

// WG_PP_SEQ_FOR_EACH_I functor.
#define WG_PP_FORWARDER_TYPE_ACCESSORDCLN( \
  r, membervar_rootname, indx, e_or_d_type) \
    WG_PP_PARSEDTYPE_IFNONLOCAL_ADDCONSTADDREFERENCE(e_or_d_type) \
    WG_PP_FORWARDER_TYPE_ACCESSORVARNAME(membervar_rootname,indx) () const \
    { \
      return WG_PP_FORWARDER_TYPE_MEMBERVAR_NAME(membervar_rootname,indx); \
    }

//-------------
//Obj Init List
//-------------

#define WG_PP_FORWARDER_OBJ_INITLIST(symbtbl) \
  WG_PP_SEQ_ENUM( \
    WG_PP_SEQ_JOIN3( \
      WG_PP_SYMBOLTABLE_ASSIGNEDTO_OBJ(symbtbl), \
      WG_PP_SEQ_REPLACE( \
        WG_PP_SYMBOLTABLE_PARAMBIND_OBJS(symbtbl), \
        WG_PP_SYMBOLTABLE_PARAMBIND_OBJS_THISU_MARKER(symbtbl), \
        this), \
      WG_PP_SYMBOLTABLE_PARAMSET_VALUES(symbtbl) ))

#endif /* WG_PP_FORWARDER_HH_ */
