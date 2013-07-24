#include <WG/Utils/ClassMethodDisablers.hh>

struct DisabledNewArray
{
  DisabledNewArray() {}
  WG_DISABLE_HEAP_ALLOCATION();
};

int main()
{
  DisabledNewArray * pObj1 = new DisabledNewArray[5]();

  return 0;
}