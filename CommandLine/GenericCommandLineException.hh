#ifndef WAVEGLIDER_COMMANDLINE_GENERICCOMMANDLINEEXCEPTION_HH_
#define WAVEGLIDER_COMMANDLINE_GENERICCOMMANDLINEEXCEPTION_HH_

#include <string>
#include <stdexcept>
#include <WaveGlider/CommandLine/ICommandLineException.hh>

namespace WaveGlider
{
namespace CL
{

class GenericCommandLineException :
    public virtual std::runtime_error,
    public virtual ICommandLineException
{
public:
    explicit GenericCommandLineException(std::string const & what = std::string());
    GenericCommandLineException(GenericCommandLineException const & rhs);
    virtual ~GenericCommandLineException() throw();

private:
    //Declared and purposefully not defined.
    GenericCommandLineException & operator=(GenericCommandLineException const &);
};

}
}

#endif /* WAVEGLIDER_COMMANDLINE_GENERICCOMMANDLINEEXCEPTION_HH_ */
