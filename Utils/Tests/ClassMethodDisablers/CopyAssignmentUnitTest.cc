#include <WG/Utils/ClassMethodDisablers.hh>

struct DisabledCopyAssignment
{
  DisabledCopyAssignment() {}
  WG_DISABLE_COPY_ASSIGNMENT(DisabledCopyAssignment);
};

int main()
{
  DisabledCopyAssignment obj1;
  DisabledCopyAssignment obj2;
  obj2 = obj1;
  
  return 0;
}