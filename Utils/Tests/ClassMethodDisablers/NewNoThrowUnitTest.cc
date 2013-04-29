#include <WG/Utils/ClassMethodDisablers.hh>

struct DisabledNewNoThrow
{
  DisabledNewNoThrow() {}
  WG_DISABLE_HEAP_ALLOCATION();
};

int main()
{
  DisabledNewNoThrow * pObj1 = new(std::nothrow) DisabledNewNoThrow();

  return 0;
}