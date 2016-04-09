Summary
-------
This project contains two libraries. One is LclFunction and the other LclContext. 

LclFunction is a library inspired by Boost.LocalFunction that allows function definition at block scope. However, there are important differences between LclFunction and Boost.LocalFunction, my version allows C++14-like generalized lambda captures, allows binding array types, and allows the use of globally scoped macro parameters, whereas Boost.LocalFunction lacks these features. One last "feature" is that the local function's name is only required in the beginning macro.

LclContext is an adaptation of Python's "with" statement in C++. The reasons to use this over RAII or Boost.ScopeExit are 1) the scope of a resource's lifetime is explicit rather than implicit, 2) it is clearly identified which resource is being managed as opposed to the RAII idiom where it's not clear whether a declaration is RAII or not, and 3) this library automatically detects whether a scope exited prematurely or not and that fact is conveyed to the user via "scope_completed" variable.

Documentation
-------------
Can be found in "./Local/Docs".

Unit Tests
----------
Can be found in "./Local/Tests".
To run unit tests:

  1) cd WG/build_autotools
  2) autoconf
     automake -a
     autoreconf
  3) mkdir -p builds/debug;
  4) cd builds/debug;
  5) ../../configure CXXFLAGS="-O0 -ggdb" --with-boost-headers=<absolute-path-to-boost-headers> --enable-gtest
  6) make
  7) cd "<build-directory>/WG/Local/Tests/build_autotools" for test executables.

LclFunction Sample Usage
------------------------

  #include <iostream>
  #include <WG/Local/LclFunction.hh>

  int main()
  {
    int const mass = 10;
    int const velocity = 2;
    
    WG_LCLFUNCTION
    (calculateForce,
    return (int)
    params (int const mass)
    varbind (const velocity) )
    {
      return mass * velocity;
    }
    WG_LCLFUNCTION_END
    
    int force = calculateForce(mass);
    std::cout << force << '\n';
    
    return 0;
  }

LclContext Extant Sample Usage
------------------------------
  #include <WG/Local/LclContext.hh>

  struct Transaction
  {
    void start() {}
    void record(int) {}
    void commit() {}
    void rollback() {};
  };

  struct TransactionScopeMngr
  {
    TransactionScopeMngr(Transaction & transaction)
    : m_Transaction(transaction)
    {}
    
    void enter()
    {
      m_Transaction.start();
    }
    
    void exit(bool const scope_completed)
    {
      if( ! scope_completed )
      {
        m_Transaction.rollback();
      }
      else
      {
        m_Transaction.commit();
      }
    }
    
  private:
    Transaction & m_Transaction;
  };

  int main()
  {
    Transaction t;
    
    WG_LCLCONTEXT( with(TransactionScopeMngr(t)) )
    {
      t.record(1);
      t.record(2);
      // etc...
    }
    WG_LCLCONTEXT_END1
    
    return 0;
  }

LclContext Adhoc Sample Usage
-----------------------------

  #include <WG/Local/LclContext.hh>

  struct Transaction
  {
    void start() {}
    void record(int) {}
    void commit() {}
    void rollback() {};
  };

  int main()
  {
    Transaction transaction;
    
    WG_LCLCONTEXT(
      with_adhoc (ref transaction) 
        on_enter(transaction.start();)
        on_exit( 
          if(! scope_completed) {transaction.rollback();} 
          else { transaction.commit(); } ) )
    // Scope1
    {
      transaction.record(1);
      transaction.record(2);
      // etc...
    }
    WG_LCLCONTEXT_END1
    
    return 0;
  }
