#include <WG/Utils/ClassMethodDisablers.hh>

struct DisabledNewArrayNoThrow
{
  DisabledNewArrayNoThrow() {}
  WG_DISABLE_HEAP_ALLOCATION();
};

int main()
{
  DisabledNewArrayNoThrow * pObj1 = new(std::nothrow) DisabledNewArrayNoThrow[5]();

  return 0;
}