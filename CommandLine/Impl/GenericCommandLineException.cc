#include "../GenericCommandLineException.hh"

namespace WaveGlider
{
namespace CL
{

GenericCommandLineException::GenericCommandLineException(std::string const & what)
: std::runtime_error(what)
{
}

GenericCommandLineException::GenericCommandLineException(GenericCommandLineException const & rhs)
: std::runtime_error(rhs)
{
}

GenericCommandLineException::~GenericCommandLineException() throw()
{
}

}
}
