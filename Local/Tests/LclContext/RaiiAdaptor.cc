#include <gtest/gtest.h>
#include <WG/Local/LclContext.hh>

namespace
{

struct FileMngrT
{
  FileMngrT()
  : m_Filename(0),
    m_Type(0)
  {}

  FileMngrT(char const * filename)
  : m_Filename(filename),
    m_Type(0)
  {}

  FileMngrT(char const * filename, int const type)
  : m_Filename(filename),
    m_Type(type)
  {}

  bool isFilenameSet() const
  {
    return m_Filename != 0;
  }

private:
  char const * const m_Filename;
  int const m_Type;
};

}

TEST(wg_lclcontext_raii, NoEmbeddedCommas)
{
  WG_LCLCONTEXT( with_raii(FileMngrT filemngr("../tmp.txt"); ) )
  {
    EXPECT_TRUE(filemngr.isFilenameSet());
  }
  WG_LCLCONTEXT_END1
}

TEST(wg_lclcontext_raii, OneEmbeddedComma)
{
  WG_LCLCONTEXT( with_raii(FileMngrT filemngr("../tmp.txt", 1); ) )
  {
    EXPECT_TRUE(filemngr.isFilenameSet());
  }
  WG_LCLCONTEXT_END1
}
