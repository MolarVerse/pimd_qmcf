#include "stdoutOutput.hpp"

#include "exceptions.hpp"       // for UserInputExceptionWarning, customException
#include "outputMessages.hpp"   // for initialMomentumMessage

#include <iostream>      // for operator<<, char_traits, basic_ostream, cout
#include <string>        // for operator<<
#include <string_view>   // for string_view

using namespace std;
using namespace output;
using namespace customException;

/**
 * @brief write a warning message to the stdout if density and box dimensions are set
 *
 */
void StdoutOutput::writeDensityWarning() const
{
    try
    {
        throw UserInputExceptionWarning("Density and box dimensions set. Density will be ignored.");
    }
    catch (const UserInputExceptionWarning &e)
    {
        cout << e.what() << '\n' << '\n' << flush;
    }
}

/**
 * @brief write initial momentum to stdout
 *
 * @param momentum
 */
void StdoutOutput::writeInitialMomentum(const double momentum) const
{
    cout << '\n';
    cout << initialMomentumMessage(momentum) << '\n';
}