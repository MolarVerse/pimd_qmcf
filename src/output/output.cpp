#include "output.hpp"

#include "exceptions.hpp"

#include <cstdint>   // for UINT64_MAX
#include <format>
#include <fstream>

#ifdef WITH_MPI
#include <mpi.h>
#endif

using namespace std;
using namespace customException;
using namespace output;

/**
 * @brief Sets the filename of the output file
 *
 * @param filename
 *
 * @throw InputFileException if filename is empty
 * @throw InputFileException if file already exists
 */
void Output::setFilename(const string_view &filename)
{
#ifdef WITH_MPI
    int rank;
    int procId;
    MPI_Comm_rank(MPI_COMM_WORLD, &procId);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0)
    {
        _fileName = filename;
    }
    else
    {
        const auto baseFilename = "procId_pimd-qmcf_";
        filesystem::create_directory(baseFilename + to_string(procId));
        _fileName = filename;
        _fileName = baseFilename + to_string(procId) + "/" + _fileName;
    }
#else

    _fileName = filename;
#endif

    if (_fileName.empty())
        throw InputFileException("Filename cannot be empty");

    if (const ifstream fp(_fileName.c_str()); fp.good())
        throw InputFileException("File already exists - filename = " + string(_fileName));

    openFile();
}

/**
 * @brief Sets the output frequency of the simulation
 *
 * @param outputFreq
 *
 * @throw InputFileException if output frequency is negative
 *
 * @note
 *  if output frequency is 0, it is set to UINT64_MAX
 *  in order to avoid division by 0 in the output
 *
 */
void Output::setOutputFrequency(const size_t outputFreq)
{
    if (0 == outputFreq)
        _outputFrequency = UINT64_MAX;
    else
        _outputFrequency = outputFreq;
}

/**
 * @brief Opens the output file
 *
 * @throw InputFileException if file cannot be opened
 *
 */
void Output::openFile()
{
    _fp.open(_fileName);

    if (!_fp.is_open())
        throw InputFileException("Could not open file - filename = " + _fileName);
}