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
WG_LCLCONTEXT_END2
*/

{
  bool autosimflag = false;

  bool did_scope_complete = false;

#define EXPR employee.timecard()
  ::wg::lclcontext::detail::extant_scopemngr_proxy_t wgXXXlclcontextXXXscopemngr0 =
    WG_LCLCONTEXT_DETAIL_EXTANTSCOPEMNGRPROXY_MAKE(
      EXPR,
      autosimflag);

#ifndef NOEX
  try
  {
#endif
    wg_lclcontext_enteredas_typealiases::type0 starttime =
      WG_LCLCONTEXT_DETAIL_EXTANTSCOPEMNGRPROXY_ENTER(
        wgXXXlclcontextXXXscpmngrproxy0,
        EXPR,
        wg_lclcontext_enteredas_typealiases::type0) ;

    customentryhandler( starttime )

    WG_LCLCLASS(
      wgXXXlclcontextXXXadhoc_scopemngr0_t,
      memext (employee) memint (type(bool) m_didcallexit, false)
    )
      void enter()
      {
        employee.zone_out();
      }

      void exit(bool const scope_completed)
      {
        m_didcallexit = true;
        (void)scope_completed;
        employee.zone_in();
      }

      ~wgXXXlclcontextXXXadhoc_scopemngr0_t()
      {
        if( ! m_didcallexit )
        {
          this->exit(false);
        }
      }
    WG_LCLCLASS_END;

    wgXXXlclcontextXXXadhoc_scopemngr0_t
      wgXXXlclcontextXXXscopemngr1(employee);

  #ifndef NOEX
    try
    {
  #endif
      wgXXXlclcontextXXXscopemngr1.enter();

      {
        // User code goes here.
      }

      did_scope_complete = true;

    #ifndef NOEX
    }
    catch(...)
    {
      wgXXXlclcontextXXXscopemngr1.exit(did_scope_complete);
      throw;
    }
    #endif
    wgXXXlclcontextXXXscopemngr1.exit(true);
  #ifndef NOEX
  }
  catch(...)
  {
    wgXXXlclcontextXXXscopemngr0.exit(did_scope_complete);
    throw;
  }
  #endif
  wgXXXlclcontextXXXscopemngr0.exit(true);
}
