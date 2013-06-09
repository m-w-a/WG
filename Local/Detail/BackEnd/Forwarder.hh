#ifndef WG_PP_FORWARDER_HH_
#define WG_PP_FORWARDER_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/PP.hh>
#include <WG/Local/Detail/BackEnd/SymbolTable.hh>
#include <WG/Local/Detail/BackEnd/Type.hh>

//###########
//Public APIs
//###########

// Creates a class for forwarding captured variables and/or their values.
#define WG_PP_FORWARDER_DCLN( \
  frwdr_typename, frwdr_objname, symbtbl) \
    WG_PP_FORWARDER_DCLN_IMPL(frwdr_typename, frwdr_objname, symbtbl)

// Expands to <frwdr_objname>.<assignto_accessor>()
#define WG_PP_FORWARDER_ACCESSOR_ASSIGNEE(frwdr_objname) \
  WG_PP_FORWARDER_ACCESSOR_ASSIGNEE_IMPL(frwdr_objname)

// Expands to { BOOST_PP_NIL | (ACCESSOR_INDX0)(ACCESSOR_INDX1) ... }
#define WG_PP_FORWARDER_ACCESSORWGSEQ_BOUNDPARAM(frwdr_objname, count) \
  WG_PP_FORWARDER_ACCESSORWGSEQ_BOUNDPARAM_IMPL(frwdr_objname, count)

// Expands to { BOOST_PP_NIL | (ACCESSOR_INDX0)(ACCESSOR_INDX1) ... }
#define WG_PP_FORWARDER_ACCESSORWGSEQ_SETPARAM(frwdr_objname, count) \
  WG_PP_FORWARDER_ACCESSORWGSEQ_SETPARAM_IMPL(frwdr_objname, count)

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
      WG_PP_FORWARDER_TYPE_ACCESSORS(symbtbl) \
    } WG_PP_IDENTITY(;) \
    frwdr_typename const & frwdr_objname = \
      frwdr_typename \
      BOOST_PP_LPAREN() \
        WG_PP_FORWARDER_OBJ_INITLIST(symbtbl) \
      BOOST_PP_RPAREN() WG_PP_IDENTITY(;)

#define WG_PP_FORWARDER_ACCESSOR_ASSIGNEE_IMPL(frwdr_objname) \
  frwdr_objname.WG_PP_FORWARDER_TYPE_ACCESSORNAME( \
    WG_PP_FORWARDER_TYPE_MEMBERVAR_ROOTNAME_ASSIGNEE(), 0) ()

#define WG_PP_FORWARDER_ACCESSORWGSEQ_BOUNDPARAM_IMPL(frwdr_objname, count) \
  WG_PP_FORWARDER_ACCESSORWGSEQ_IMPL( \
    frwdr_objname, \
    WG_PP_FORWARDER_TYPE_MEMBERVAR_ROOTNAME_BOUNDPARAM(), \
    count)

#define WG_PP_FORWARDER_ACCESSORWGSEQ_SETPARAM_IMPL(frwdr_objname, count) \
  WG_PP_FORWARDER_ACCESSORWGSEQ_IMPL( \
    frwdr_objname, \
    WG_PP_FORWARDER_TYPE_MEMBERVAR_ROOTNAME_SETPARAM(), \
    count)

#define WG_PP_FORWARDER_ACCESSORWGSEQ_IMPL0( \
  frwdr_objname, membervar_rootname, count) \
    BOOST_PP_NIL
#define WG_PP_FORWARDER_ACCESSORWGSEQ_IMPL1( \
  frwdr_objname, membervar_rootname, count) \
    BOOST_PP_REPEAT( \
      count, \
      WG_PP_FORWARDER_ACCESSOR_TUPLIZE, \
      (frwdr_objname)(membervar_rootname) )
#define WG_PP_FORWARDER_ACCESSORWGSEQ_IMPL( \
  frwdr_objname, membervar_rootname, count) \
    BOOST_PP_IF( \
      count, \
      WG_PP_FORWARDER_ACCESSORWGSEQ_IMPL1, \
      WG_PP_FORWARDER_ACCESSORWGSEQ_IMPL0) \
    (frwdr_objname, membervar_rootname, count)

// BOOST_PP_REPEAT functor.
// access_seq: (frwdr_objname)(membervar_rootname)
#define WG_PP_FORWARDER_ACCESSOR_TUPLIZE(z, indx, access_seq) \
  ( BOOST_PP_SEQ_ELEM(0, access_seq) . \
    WG_PP_FORWARDER_TYPE_ACCESSORNAME( \
      BOOST_PP_SEQ_ELEM(1, access_seq), indx) () )

//------------
//Common Utils
//------------

#define WG_PP_FORWARDER_TYPE_MEMBERVAR_ROOTNAME_ASSIGNEE() assignee
#define WG_PP_FORWARDER_TYPE_MEMBERVAR_ROOTNAME_BOUNDPARAM() boundparam
#define WG_PP_FORWARDER_TYPE_MEMBERVAR_ROOTNAME_SETPARAM() setparam
#define WG_PP_FORWARDER_TYPE_MEMBERVAR_ROOTNAME_BOUNDMEM() boundmem
#define WG_PP_FORWARDER_TYPE_MEMBERVAR_ROOTNAME_SETMEM() setmem

#define WG_PP_FORWARDER_TYPE_MEMBERVAR_NAME(rootname, indx) \
  BOOST_PP_CAT(rootname, indx)

// membervar_rootname: use any of the MEMBERVAR_ROOTNAME_*() macros.
#define WG_PP_FORWARDER_TYPE_ACCESSORNAME(membervar_rootname, indx) \
  BOOST_PP_CAT( \
    BOOST_PP_CAT(getXXX, membervar_rootname), \
    indx)

// assignee_transform
// rest_transform:
//   a WG_PP_SEQ_FOR_EACH_I that will be passed the following params:
//     data: membervarrootname
//     elem: explicit_or_deduced_type
#define WG_PP_FORWARDER_TYPE_MEMBERTYPE_COMMONTRANSFORM( \
  symbtbl, assignee_transform, rest_transform) \
    WG_PP_FORWARDER_TYPE_MEMBERTYPECNGRNCECLASS_COMMONTRANSFORM( \
      ASSIGNEE, assignee_transform, symbtbl) \
    WG_PP_FORWARDER_TYPE_MEMBERTYPECNGRNCECLASS_COMMONTRANSFORM( \
      BOUNDPARAM, rest_transform, symbtbl) \
    WG_PP_FORWARDER_TYPE_MEMBERTYPECNGRNCECLASS_COMMONTRANSFORM( \
      SETPARAM, rest_transform, symbtbl)

#define WG_PP_FORWARDER_TYPE_MEMBERTYPECNGRNCECLASS_COMMONTRANSFORM( \
  suffix, transform, symbtbl) \
    WG_PP_SEQ_IFNIL_THENCLEAR( \
      WG_PP_SEQ_FOR_EACH_I( \
        transform, \
        BOOST_PP_CAT(WG_PP_FORWARDER_TYPE_MEMBERVAR_ROOTNAME_, suffix) (), \
        BOOST_PP_CAT(WG_PP_SYMBOLTABLE_TYPESEQ_, suffix) (symbtbl) ))

//-----------
//MemberDclns
//-----------

// Do not use WG_PP_FORWARDER_TYPE_MEMBERDCLN since we only want a reference to
//   the assignee.
#define WG_PP_FORWARDER_TYPE_MEMBERDCLNS(symbtbl) \
  WG_PP_FORWARDER_TYPE_MEMBERTYPE_COMMONTRANSFORM( \
    symbtbl, \
    WG_PP_FORWARDER_TYPE_MEMBERDCLN_ASSIGNEE, \
    WG_PP_FORWARDER_TYPE_MEMBERDCLN)

// WG_PP_SEQ_FOR_EACH_I functor.
#define WG_PP_FORWARDER_TYPE_MEMBERDCLN_ASSIGNEE( \
  r, varrootname, indx, e_or_d_type) \
    WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_IFNONLOCALTYPE_ADDREFERENCE(e_or_d_type) \
    WG_PP_FORWARDER_TYPE_MEMBERVAR_NAME(varrootname, indx) WG_PP_IDENTITY(;)

// WG_PP_SEQ_FOR_EACH_I functor.
#define WG_PP_FORWARDER_TYPE_MEMBERDCLN(r, varrootname, indx, e_or_d_type) \
  WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_IFNONLOCALTYPE_ADDCONSTADDREFERENCE(e_or_d_type) \
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
  BOOST_PP_IF( \
    WG_PP_SYMBOLTABLE_TOTALXXX_SIZE(symbtbl), \
    WG_PP_FORWARDER_TYPE_CTOR_PARAMLIST_1, \
    WG_PP_FORWARDER_TYPE_CTOR_PARAMLIST_0) (symbtbl)

#define WG_PP_FORWARDER_TYPE_CTOR_PARAMLIST_0(symbtbl)
// There will be at least 1 entry, therefore no worries as to empty macro args
//   to WG_PP_SEQ_ENUM
#define WG_PP_FORWARDER_TYPE_CTOR_PARAMLIST_1(symbtbl) \
  WG_PP_SEQ_ENUM( \
    WG_PP_FORWARDER_TYPE_MEMBERTYPE_COMMONTRANSFORM( \
      symbtbl, \
      WG_PP_FORWARDER_TYPE_CTOR_PARAMLIST_ENTRY_ASSIGNEE, \
      WG_PP_FORWARDER_TYPE_CTOR_PARAMLIST_ENTRY) )

// WG_PP_SEQ_FOR_EACH_I functor.
#define WG_PP_FORWARDER_TYPE_CTOR_PARAMLIST_ENTRY_ASSIGNEE( \
  r, membervar_rootname, indx, e_or_d_type) \
    BOOST_PP_LPAREN() \
      WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_IFNONLOCALTYPE_ADDREFERENCE(e_or_d_type) \
      WG_PP_FORWARDER_TYPE_CTOR_PARAMVARNAME(membervar_rootname, indx) \
    BOOST_PP_RPAREN()

// WG_PP_SEQ_FOR_EACH_I functor.
#define WG_PP_FORWARDER_TYPE_CTOR_PARAMLIST_ENTRY( \
  r, membervar_rootname, indx, e_or_d_type) \
    BOOST_PP_LPAREN() \
      WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_IFNONLOCALTYPE_ADDCONSTADDREFERENCE(e_or_d_type) \
      WG_PP_FORWARDER_TYPE_CTOR_PARAMVARNAME(membervar_rootname, indx) \
    BOOST_PP_RPAREN()

//--------------
//Ctor Init List
//--------------

#define WG_PP_FORWARDER_TYPE_CTOR_INITLIST(symbtbl) \
  BOOST_PP_IF( \
    WG_PP_SYMBOLTABLE_TOTALXXX_SIZE(symbtbl), \
    WG_PP_FORWARDER_TYPE_CTOR_INITLIST_1, \
    WG_PP_FORWARDER_TYPE_CTOR_INITLIST_0) (symbtbl)

#define WG_PP_FORWARDER_TYPE_CTOR_INITLIST_0(symbtbl)
// There will be at least 1 entry, therefore no worries as to empty macro args
//   to WG_PP_SEQ_ENUM
#define WG_PP_FORWARDER_TYPE_CTOR_INITLIST_1(symbtbl) \
  WG_PP_IDENTITY(:) \
  WG_PP_SEQ_ENUM( \
    WG_PP_FORWARDER_TYPE_MEMBERTYPE_COMMONTRANSFORM( \
      symbtbl, \
      WG_PP_FORWARDER_TYPE_CTOR_INITLISTENTRY, \
      WG_PP_FORWARDER_TYPE_CTOR_INITLISTENTRY))

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
  WG_PP_FORWARDER_TYPE_MEMBERTYPE_COMMONTRANSFORM( \
    symbtbl, \
    WG_PP_FORWARDER_TYPE_ACCESSORDCLN_ASSIGNEE, \
    WG_PP_FORWARDER_TYPE_ACCESSORDCLN)

// WG_PP_SEQ_FOR_EACH_I functor.
#define WG_PP_FORWARDER_TYPE_ACCESSORDCLN_ASSIGNEE( \
  r, membervar_rootname, indx, e_or_d_type) \
    WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_IFNONLOCALTYPE_ADDREFERENCE(e_or_d_type) \
    WG_PP_FORWARDER_TYPE_ACCESSORDCLN_SIGANDBODY(membervar_rootname, indx)

// WG_PP_SEQ_FOR_EACH_I functor.
#define WG_PP_FORWARDER_TYPE_ACCESSORDCLN( \
  r, membervar_rootname, indx, e_or_d_type) \
    WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_IFNONLOCALTYPE_ADDCONSTADDREFERENCE(e_or_d_type) \
    WG_PP_FORWARDER_TYPE_ACCESSORDCLN_SIGANDBODY(membervar_rootname, indx)

#define WG_PP_FORWARDER_TYPE_ACCESSORDCLN_SIGANDBODY( \
  membervar_rootname, indx) \
    WG_PP_FORWARDER_TYPE_ACCESSORNAME(membervar_rootname,indx) () const \
    { \
      return WG_PP_FORWARDER_TYPE_MEMBERVAR_NAME(membervar_rootname,indx); \
    }

//-------------
//Obj Init List
//-------------

#define WG_PP_FORWARDER_OBJ_INITLIST(symbtbl) \
  WG_PP_SEQ_ENUM( \
    WG_PP_SEQ_JOIN3( \
      WG_PP_SYMBOLTABLE_OBJSEQ_ASSIGNEE(symbtbl), \
      WG_PP_SEQ_REPLACE( \
        WG_PP_SYMBOLTABLE_OBJSEQ_BOUNDPARAM(symbtbl), \
        WG_PP_SYMBOLTABLE_OBJSEQ_BOUNDPARAM_THISU_MARKER(symbtbl), \
        this), \
      WG_PP_SYMBOLTABLE_VALUESEQ_SETPARAM(symbtbl) ))

#endif /* WG_PP_FORWARDER_HH_ */
