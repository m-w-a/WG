Summary
-------
This project contains two libraries. One is LclContext and the other LclFunction. LclContext is an adaptation of Python's "with" statement in C++. LclFunction is a library inspired by Boost.LocalFunction that allows function definition at block scope. However, there are important differences between LclFunction and Boost.LocalFunction, my version allows C++14-like generalized lambda captures, allows binding array types, and allows the use of globally scoped macro parameters, whereas Boost.LocalFunction lacks these features.

Unit Tests
----------
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

Documentation
-------------
Can be found in WG/Local/Docs.

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

LclContext Sample Usage
-----------------------

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