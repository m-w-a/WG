#include <WG/Utils/ClassMethodDisablers.hh>

struct DisabledDeleteArrayNoThrow
{
  DisabledDeleteArrayNoThrow() {}
  WG_DISABLE_HEAP_ALLOCATION();
};

int main()
{
  DisabledDeleteArrayNoThrow * pObj1 = 0;
  DisabledDeleteArrayNoThrow::operator delete[](pObj1, std::nothrow);

  return 0;
}