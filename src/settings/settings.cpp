#include "settings.hpp"

#include "exceptions.hpp"

using namespace std;
using namespace settings;
using namespace customException;

/**
 * @brief set temperature
 *
 * @param temperature
 */
void Settings::setTemperature(double temperature) { _temperature = make_pair(true, temperature); }

/**
 * @brief set relaxation time for thermostat
 *
 * @param relaxationTime
 */
void Settings::setRelaxationTime(double relaxationTime) { _relaxationTime = make_pair(true, relaxationTime); }

/**
 * @brief set relaxation time for manostat
 *
 * @param tauManostat
 *
 * @throw InputFileException if relaxation time is negative
 */
void Settings::setTauManostat(double tauManostat) { _tauManostat = make_pair(true, tauManostat); }
