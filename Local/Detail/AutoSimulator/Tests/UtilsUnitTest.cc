#include <gtest/gtest.h>
#include <gtest/gtest-spi.h>
#include <WG/Local/Detail/AutoSimulator/Tests/Utils.hh>

using namespace ::wg::autosimulator::detail::test;

TEST(wg_autosimulator_test_utils, CallCountVerifier)
{
  ExprGenerator expr;

  expr.mutableArray();
  expr.constArray();

  expr.copyonlyMutableRValue();
  expr.copyonlyConstRValue();
  expr.copyonlyMutableLValue();
  expr.copyonlyConstLValue();

  expr.moveonlyMutableRValue();
  expr.moveonlyMutableLValue();
  expr.moveonlyConstLValue();

  expr.copymoveMutableRValue();
  expr.copymoveConstRValue();
  expr.copymoveMutableLValue();
  expr.copymoveConstLValue();

  EXPECT_NONFATAL_FAILURE( expr.mutableArray(), "" );
  EXPECT_NONFATAL_FAILURE( expr.constArray(), "" );

  EXPECT_NONFATAL_FAILURE( expr.copyonlyMutableRValue(), "" );
  EXPECT_NONFATAL_FAILURE( expr.copyonlyConstRValue(), "" );
  EXPECT_NONFATAL_FAILURE( expr.copyonlyMutableLValue(), "" );
  EXPECT_NONFATAL_FAILURE( expr.copyonlyConstLValue(), "" );

  EXPECT_NONFATAL_FAILURE( expr.moveonlyMutableRValue(), "" );
  EXPECT_NONFATAL_FAILURE( expr.moveonlyMutableLValue(), "" );
  EXPECT_NONFATAL_FAILURE( expr.moveonlyConstLValue(), "" );

  EXPECT_NONFATAL_FAILURE( expr.copymoveMutableRValue(), "" );
  EXPECT_NONFATAL_FAILURE( expr.copymoveConstRValue(), "" );
  EXPECT_NONFATAL_FAILURE( expr.copymoveMutableLValue(), "" );
  EXPECT_NONFATAL_FAILURE( expr.copymoveConstLValue(), "" );
}
