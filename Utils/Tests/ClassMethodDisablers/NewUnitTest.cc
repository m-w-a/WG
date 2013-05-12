#include <WG/Utils/ClassMethodDisablers.hh>

struct DisabledNew
{
  DisabledNew() {}
  WG_DISABLE_HEAP_ALLOCATION();
};

int main()
{
  DisabledNew * pObj1 = new DisabledNew();

  return 0;
}