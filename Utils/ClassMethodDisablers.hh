#ifndef WG_UTILS_CLASSMETHODDISABLERS_HH_
#define WG_UTILS_CLASSMETHODDISABLERS_HH_

#include <new>

#define WG_DISABLE_DEFAULT_CTOR(classname) \
  private: classname();
  
#define WG_DISABLE_COPY_CTOR(classname) \
  private: classname(classname const &);
  
#define WG_DISABLE_COPY_ASSIGNMENT(classname) \
  private: classname & operator=(classname const &);
  
#define WG_DISABLE_HEAP_ALLOCATION() \
  private: \
    void* operator new(std::size_t size) throw(std::bad_alloc); \
    void* operator new(std::size_t size, const std::nothrow_t&) throw(); \
    void* operator new[](std::size_t size) throw(std::bad_alloc); \
    void* operator new[](std::size_t size, const std::nothrow_t&) throw(); \
    void operator delete(void* ptr) throw(); \
    void operator delete(void* ptr, const std::nothrow_t&) throw(); \
    void operator delete[](void* ptr) throw(); \
    void operator delete[](void* ptr, const std::nothrow_t&) throw();

#endif //WG_UTILS_CLASSMETHODDISABLERS_HH_