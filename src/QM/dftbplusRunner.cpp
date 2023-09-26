#include "dftbplusRunner.hpp"

#include "atom.hpp"              // for Atom
#include "exceptions.hpp"        // for InputFileException
#include "qmSettings.hpp"        // for QMSettings
#include "simulationBox.hpp"     // for SimulationBox
#include "stringUtilities.hpp"   // for fileExists
#include "vector3d.hpp"          // for Vec3D

#include <cstddef>      // for size_t
#include <cstdlib>      // for system
#include <format>       // for format
#include <fstream>      // for ofstream
#include <functional>   // for identity
#include <ranges>       // for borrowed_iterator_t, __distance_fn
#include <string>       // for string
#include <vector>       // for vector

using QM::DFTBPlusRunner;

/**
 * @brief writes the coords file in order to run the external qm program
 *
 * @param box
 */
void DFTBPlusRunner::writeCoordsFile(simulationBox::SimulationBox &box)
{
    const std::string fileName = "coords";
    std::ofstream     coordsFile(fileName);

    coordsFile << box.getNumberOfQMAtoms() << "  S\n";

    const auto uniqueAtomNames = box.getUniqueQMAtomNames();

    for (const auto &atomName : uniqueAtomNames)
        coordsFile << atomName << "  ";

    coordsFile << "\n";

    for (size_t i = 0, numberOfAtoms = box.getNumberOfQMAtoms(); i < numberOfAtoms; ++i)
    {
        const auto &atom = box.getQMAtom(i);

        const auto iter   = std::ranges::find(uniqueAtomNames, atom.getName());
        const auto atomId = std::ranges::distance(uniqueAtomNames.begin(), iter) + 1;

        coordsFile << std::format("{:5d} {:5d}\t{:16.12f}\t{:16.12f}\t{:16.12f}\n",
                                  i + 1,
                                  atomId,
                                  atom.getPosition()[0],
                                  atom.getPosition()[1],
                                  atom.getPosition()[2]);
    }

    coordsFile << std::format("{:11}\t{:16.12f}\t{:16.12f}\t{:16.12f}\n", "", 0.0, 0.0, 0.0);
    coordsFile << std::format("{:11}\t{:16.12f}\t{:16.12f}\t{:16.12f}\n", "", box.getBoxDimensions()[0], 0.0, 0.0);
    coordsFile << std::format("{:11}\t{:16.12f}\t{:16.12f}\t{:16.12f}\n", "", 0.0, box.getBoxDimensions()[1], 0.0);
    coordsFile << std::format("{:11}\t{:16.12f}\t{:16.12f}\t{:16.12f}\n", "", 0.0, 0.0, box.getBoxDimensions()[2]);

    coordsFile.close();
}

/**
 * @brief executes the qm script of the external program
 *
 */
void DFTBPlusRunner::execute()
{
    const auto scriptFileName = _scriptPath + settings::QMSettings::getQMScript();

    if (!utilities::fileExists(scriptFileName))
        throw customException::InputFileException(std::format("DFTB+ script file \"{}\" does not exist.", scriptFileName));

    const auto reuseCharges = _isFirstExecution ? 1 : 0;

    const auto command = std::format("{} 0 {} 0 0 0", scriptFileName, reuseCharges);
    ::system(command.c_str());

    _isFirstExecution = false;
}