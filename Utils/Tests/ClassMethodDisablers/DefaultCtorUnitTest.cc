#include <WG/Utils/ClassMethodDisablers.hh>

struct DisabledDefaultCtor
{
  WG_DISABLE_DEFAULT_CTOR(DisabledDefaultCtor);
};

int main()
{
  DisabledDefaultCtor();
  return 0;
}