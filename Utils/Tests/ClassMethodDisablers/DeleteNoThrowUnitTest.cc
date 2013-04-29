#include <WG/Utils/ClassMethodDisablers.hh>

struct DisabledDeleteNoThrow
{
  DisabledDeleteNoThrow() {}
  WG_DISABLE_HEAP_ALLOCATION();
};

int main()
{
  DisabledDeleteNoThrow * pObj1 = 0;
  DisabledDeleteNoThrow::operator delete(pObj1, std::nothrow);

  return 0;
}