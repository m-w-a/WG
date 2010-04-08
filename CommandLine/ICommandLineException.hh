#ifndef WAVEGLIDER_COMMANDLINE_ICOMMANDLINEEXCEPTION_HH_
#define WAVEGLIDER_COMMANDLINE_ICOMMANDLINEEXCEPTION_HH_

#include <string>

namespace WaveGlider
{
namespace CL
{

class ICommandLineException
{
public:
    ICommandLineException();
    virtual ~ICommandLineException() throw() = 0;
    virtual const char* what() const throw() = 0;

private:
    //Declared and purposefully not defined.
    ICommandLineException(ICommandLineException const &);
    ICommandLineException & operator=(ICommandLineException const &);
};

}
}

#endif /* WAVEGLIDER_COMMANDLINE_ICOMMANDLINEEXCEPTION_HH_ */
