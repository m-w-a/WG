#include <gtest/gtest.h>
#include <WG/Local/LclContext.hh>

namespace
{

struct FileMngrT
{
  FileMngrT()
  : m_Filename(0)
  {}

  FileMngrT(char const * filename)
  : m_Filename(filename)
  {}

  bool isFilenameSet() const
  {
    return m_Filename != 0;
  }

private:
  char const * const m_Filename;
};

}

TEST(wg_lclcontext_raii, Adaptor)
{
  WG_LCLCONTEXT( with_raii(FileMngrT filemngr("../tmp.txt"); ) )
  {
    EXPECT_TRUE(filemngr.isFilenameSet());
  }
  WG_LCLCONTEXT_END1
}
