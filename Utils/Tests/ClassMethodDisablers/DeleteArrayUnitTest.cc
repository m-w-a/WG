#include <WG/Utils/ClassMethodDisablers.hh>

struct DisabledDeleteArray
{
  DisabledDeleteArray() {}
  WG_DISABLE_HEAP_ALLOCATION();
};

int main()
{
  DisabledDeleteArray * pObj1 = 0;
  delete[] pObj1;

  return 0;
}