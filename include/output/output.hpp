#ifndef _OUTPUT_HPP_

#define _OUTPUT_HPP_

#include <fstream>
#include <string>

namespace output
{
    class Output;
}

/**
 * @class Output
 *
 * @brief Base class for output files
 *
 */
class output::Output
{
  protected:
    std::string          _filename;
    std::ofstream        _fp;
    inline static size_t _outputFrequency = 1;
    int                  _rank;

    void openFile();

  public:
    explicit Output(const std::string &filename) : _filename(filename){};

    void setFilename(const std::string_view &);
    void close() { _fp.close(); }

    static void setOutputFrequency(const size_t);

    std::string initialMomentumMessage(const double) const;

    /********************************
     * standard getters and setters *
     ********************************/

    std::string   getFilename() const { return _filename; }
    static size_t getOutputFrequency() { return _outputFrequency; }
};

#endif   // _OUTPUT_HPP_