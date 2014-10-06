#include <boost/cstdint.hpp>

int main()
{
  // WG_LCLCONTEXT(
  //   with(cntxtmngr1) entered_as(enter_result_obj1)
  //   with_adhoc(boundvar1) on_enter(enterstmts) on_exit(exitstmts) )
  //
  // Expands To:
  {
    LOCALOPERANDSYNTAXCHECKER(enteredas_dclns)
    TYPEALIASOR(enteredas_dclns)

    /* Iterator over with_adhoc context managers. */
    LCLCLASS(adhoc_ctxtmngr1, memext(boundvar1) )
      void enter() { enterstmts }
      void exit() { exitstmts }
    LCLCLASS_END;
    adhoc_ctxtmngr1 adhoc_obj1(boundvar1);

    ContextMngrGroup
    {
      /* Iterate over "with" context managers and associated objs. */
      CntxMngr1 cntxtmngr1;

      /* Iterate over with_adhoc context managers and associated objs. */
      adhoc_ctxtmngr1 & adhoc_obj1;

      void exit(bool const exception_is_active)
      {
        /* Reverse iterate context managers obj seq. */
        adhoc_obj1 . exit(exception_is_active);
        cntxtmngr1 . exit(exception_is_active);
      }
    } cntxtMngrGrpObj = {cntxtmngr1, adhoc_obj1};

  #ifndef NOEX
    typedef void (*wg_lclcontext_onexitfptr)(bool);

    try
    {
  #endif NOEX
      /* Iterate context managers obj-ordinal seq. */
      ALIASEDTYPE(1) enteredas_obj1 = cntxtmngr1.enter();
      adhoc_obj1.enter();

      for(boost::uint_least8_t wg_lclcontext_count45 = 0;
          wg_lclcontext_count45 != 2;
          ++wg_lclcontext_count45)
      {
        if(wg_lclcontext_count45)
        {
          adhoc_obj1.exit(false);
          cntxtmngr1.exit(false);
        }

        //User code starts.
        {

        }
        //User code ends.

      }

  #ifndef NOEX
    }
    catch(...)
    {
      mgrs.exit(true);
      throw;
    }
  #endif

    mgrs.exit(false);
  }

  return 0;
}
