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

#define EXPR employee.timecard()
  ::wg::lclcontext::detail::scopemngr_proxy_t wgXXXlclcontextXXXscopemngr =
    WG_AUTOSIMULATOR_AUTOANY_CUSTOM_CAPTURE(
      ::wg::lclcontext::detail::scopemngr_proxy,
      EXPR,
      autosimflag);

#ifndef NOEX
  try
#endif
  {
    wg_lclcontext_enteredas_typealiases::type0 starttime =
      WG_AUTOSIMULATOR_AUTOANY_VALUE(
        wgXXXlclcontextXXXscpmngrproxy,
        EXPR).enter();

    WG_LCLCLASS(
      wgXXXlclcontextXXXadhoc_scopemngr1_t,
      memext (employee) memint (type(bool) did_call_exit, false)
    )
      void enter()
      {
        employee.zone_out();
      }

      void exit(bool const did_throw)
      {
        did_call_exit = true;
        (void)did_throw;
        employee.zone_in();
      }

      ~wgXXXlclcontextXXXadhoc_scopemngr1_t()
      {
        if( ! did_call_exit )
        {
          this->exit(false);
        }
      }
    WG_LCLCLASS_END;

    wgXXXlclcontextXXXadhoc_scopemngr1_t
      wgXXXlclcontextXXXscopemngr(employee);

    #ifndef NOEX
    try
    #endif
    {
      // User code goes here.
    }
    #ifndef NOEX
    catch(...)
    {
      wgXXXlclcontextXXXscopemngr.exit(true);
      throw;
    }
    #endif
  }
  #ifndef NOEX
  catch(...)
  {
    wgXXXlclcontextXXXscopemngr.exit(true);
    throw;
  }
  #endif
}
