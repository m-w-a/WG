/*
WG_LCLCONTEXT(
  with(employee.timecard()) entered_as(const starttime)
  with_adhoc (employee)
    on_enter(employee.zone_out();) on_exit(employee.zone_in();)
)
{
  if(starttime > current_shift.start_time())
  {
    assign_potatoe_peeling_duty(employee);
  }
}
WG_LCLCONTEXT_END
*/

{
#define EXTANTSCOPEMNGR_EXPR0 employee.timecard()

  struct wg_lclcontext_enteredas_typealiases
  {
    typedef
      add_const<BOOST_TYPEOF( (EXTANTSCOPEMNGR_EXPR0).enter() )>::type
        type0;
  };

  #ifdef CPP03
  typedef
    ::wg::lclcontext::detail::cpp03::adhoc_scope_manager_proxy
      wgXXXlclcontextXXXadhoc_scopemngr0_base_t;
  #else
  typedef
    ::wg::lclcontext::detail::cpp11::adhoc_scope_manager_proxy
    <wgXXXlclcontextXXXadhoc_scopemngr0_t>
      wgXXXlclcontextXXXadhoc_scopemngr0_base_t;
  #endif

  WG_LCLCLASS(
    wgXXXlclcontextXXXadhoc_scopemngr0_t,
    derives (public wgXXXlclcontextXXXadhoc_scopemngr0_base_t)
    memext (employee)
    #ifdef CPP03
    baseinit
    (
      ::wg::lclcontext::detail::cpp11::adhoc_scope_manager_proxy(
        & wgXXXlclcontextXXXadhoc_scopemngr0_t ::on_exit_proxy)
    )
    #endif
  )
    #ifdef CPP03
    static void on_exit_proxy(
      ::wg::lclcontext::detail::cpp03::adhoc_scope_manager_proxy * const base,
      bool const did_throw)
    {
      static_cast<classname *>(base)->on_exit(did_throw);
    }
    #endif

    void enter()
    {
      employee.zone_out();
    }

    void exit(bool const did_throw)
    {
      (void)did_throw;
      employee.zone_in();
    }

    ~wgXXXlclcontextXXXadhoc_scopemngr0_t()
    {
    }
  WG_LCLCLASS_END;

  wgXXXlclcontextXXXadhoc_scopemngr0_t
    wgXXXlclcontextXXXadhoc_scopemngr0(employee);

#define EXPRSEQ \
  ( EXTANTSCOPEMNGR_EXPR0 ) \
  ( \
    static_cast<wgXXXlclcontextXXXadhoc_scopemngr0_base_t &> \
    (wgXXXlclcontextXXXadhoc_scopemngr0) \
  )

  ::wg::lclcontext::detail::scope_mngr_group_t
    wgXXXlclcontextXXXscope_mngr_grp =
      WG_AUTOSIMULATOR_AUTOANYGROUP_ALLOC_CUSTOM( \
        ::wg::lclcontext::detail::scope_mngr_group,
        EXPRSEQ);

  bool wgXXXlclcontextXXXautosimflag = false;
  WG_AUTOSIMULATOR_AUTOANYGROUP_INIT(
    wgXXXlclcontextXXXscope_mngr_grp,
    wgXXXlclcontextXXXautosimflag,
    EXPRSEQ);

#ifndef NOEX
  try
#endif
  {
    wg_lclcontext_enteredas_typealiases::type0 starttime =
      WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(
        wgXXXlclcontextXXXscope_mngr_grp, 0, EXPRSEQ) . enter() ;

    (void) wgXXXlclcontextXXXadhoc_scopemngr0 . enter();

    {
      // User code goes here.
    }
  }
#ifndef NOEX
  catch(...)
  {
    wgXXXlclcontextXXXscope_mngr_grp.mark_exception();
    throw;
  }
#endif
}
