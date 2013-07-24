#include <WG/Utils/ClassMethodDisablers.hh>

struct DisabledCopyCtor
{
  DisabledCopyCtor() {}
  WG_DISABLE_COPY_CTOR(DisabledCopyCtor);
};

int main()
{
  DisabledCopyCtor obj1;
  DisabledCopyCtor obj2(obj1);
  
  return 0;
};