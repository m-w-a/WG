#ifndef WAVEGLIDER_CORE_EXCEPTIONS_HH_
#define WAVEGLIDER_CORE_EXCEPTIONS_HH_

#include <stdexcept>
#include <string>

namespace WaveGlider
{
namespace Core
{

//Class Definitions.
template <typename Tag, typename B>
class StandardExceptionTemplate : virtual public B
{
public:
    explicit StandardExceptionTemplate(std::string const & what = std::string());
    StandardExceptionTemplate(StandardExceptionTemplate const & rhs);
    virtual ~StandardExceptionTemplate() throw();

private:
    //Declared and purposefully not defined.
    StandardExceptionTemplate & operator=(StandardExceptionTemplate const &);
};

//
//Member Template Definitions.
//

template <typename Tag, typename B>
StandardExceptionTemplate<Tag, B>::StandardExceptionTemplate(std::string const & what)
: B(what)
{
}

template <typename Tag, typename B>
StandardExceptionTemplate<Tag, B>::StandardExceptionTemplate(
    StandardExceptionTemplate const & rhs)
: B(rhs)
{
}

template <typename Tag, typename B>
StandardExceptionTemplate<Tag, B>::~StandardExceptionTemplate() throw()
{
}

}
}

#endif /* WAVEGLIDER_CORE_HH_ */
