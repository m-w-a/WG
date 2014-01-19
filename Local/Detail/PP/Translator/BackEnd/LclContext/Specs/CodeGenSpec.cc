int main()
{
  WG_LCLCONTEXT( with(cntxtmgr) as(foo) )
  {

  }
  WG_LCLCONTEXT_END;
}

"WG_LCLCONTEXT( with(cntxtmngr1) as(enter_result_obj1) )" should expand to:

{
  TYPEALIASOR(contxtmngrS)
  TYPEALIASOR(enter_result_objS)
  Managers
  {
    CntxMngr1;
    ...

    void onexit(bool const exception_is_active)
    {
      CntxMngr1 . onexit(exception_is_active);
      ...
    }
  } mngrs ;

#ifndef NOEX
  try
  {
#endif NOEX
    enter_result_obj1 = mngrs.CntxtMngr1;
    ...

    //User code starts.
    {

    }
    //User code ends.

#ifndef NOEX
  }
  catch(...)
  {
    mgrs.onexit(true);
    throw;
  }
#endif

  mgrs.onexit(false);
