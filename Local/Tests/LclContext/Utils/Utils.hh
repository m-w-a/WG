#ifndef WG_LCLCONTEXT_DETAIL_TEST_UTILS_HH_
#define WG_LCLCONTEXT_DETAIL_TEST_UTILS_HH_

#define WG_LCLCONTEXT_EXPECT_SUCCESS(x) EXPECT_EQ(Result::Success, x)
#define WG_LCLCONTEXT_EXPECT_FAILURE(x) EXPECT_EQ(Result::Failure, x)

namespace wg
{
namespace lclcontext
{
namespace detail
{
namespace test
{

// Avoid using exceptions where possible, since we want to be able to build
// without support for it.
struct Result
{
  enum Kind
  {
    Failure,
    Success
  };
};

struct ScopeManager
{
  enum Id
  {
    Id0,
    Id1,
    Id2,
    Id3,
    Id4
  };
};

}
}
}
}

#endif /* WG_LCLCONTEXT_DETAIL_TEST_UTILS_HH_ */
