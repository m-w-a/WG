#include <WG/Utils/ClassMethodDisablers.hh>

struct DisabledDelete
{
  DisabledDelete() {}
  WG_DISABLE_HEAP_ALLOCATION();
};

int main()
{
  DisabledDelete * pObj1 = 0;
  delete pObj1;

  return 0;
}