#include "qmmdEngine.hpp"

#include "integrator.hpp"      // for Integrator
#include "manostat.hpp"        // for Manostat
#include "physicalData.hpp"    // for PhysicalData
#include "resetKinetics.hpp"   // for ResetKinetics
#include "thermostat.hpp"      // for Thermostat

using engine::QMMDEngine;

void QMMDEngine::takeStep()
{
    _thermostat->applyThermostatHalfStep(_simulationBox, _physicalData);

    _integrator->firstStep(_simulationBox);

    _qmRunner->run(_simulationBox, _physicalData);

    _thermostat->applyThermostatOnForces(_simulationBox);

    _integrator->secondStep(_simulationBox);

    _thermostat->applyThermostat(_simulationBox, _physicalData);

    _physicalData.calculateKinetics(_simulationBox);

    _manostat->applyManostat(_simulationBox, _physicalData);

    _resetKinetics.reset(_step, _physicalData, _simulationBox);
}