#include "berendsenThermostat.hpp"   // for BerendsenThermostat
#include "constants.hpp"             // for _BOLTZMANN_CONSTANT_, _FS_TO_S_, _KG_TO_GRAM_, _METER_SQUARED_TO_ANGSTROM_SQUARED_
#include "engine.hpp"                // for Engine
#include "exceptions.hpp"            // for InputFileException, customException
#include "langevinThermostat.hpp"    // for LangevinThermostat
#include "testSetup.hpp"             // for TestSetup
#include "thermostat.hpp"            // for BerendsenThermostat, Thermostat
#include "thermostatSettings.hpp"    // for ThermostatSettings
#include "thermostatSetup.hpp"       // for ThermostatSetup, setupThermostat
#include "timingsSettings.hpp"       // for TimingsSettings
#include "velocityRescalingThermostat.hpp"   // for VelocityRescalingThermostat

#include "gtest/gtest.h"   // for Message, TestPartResult
#include <gtest/gtest.h>   // for EXPECT_EQ, EXPECT_NO_THROW, InitGo...
#include <string>          // for allocator, basic_string

using namespace setup;

TEST_F(TestSetup, setupThermostat)
{
    ThermostatSetup thermostatSetup(*_engine);

    settings::TimingsSettings::setTimeStep(0.1);
    thermostatSetup.setup();

    settings::ThermostatSettings::setThermostatType("berendsen");
    EXPECT_THROW(thermostatSetup.setup(), customException::InputFileException);

    settings::ThermostatSettings::setTargetTemperature(300);
    settings::ThermostatSettings::setTemperatureSet(true);
    EXPECT_NO_THROW(thermostatSetup.setup());

    const auto berendsenThermostat = dynamic_cast<thermostat::BerendsenThermostat &>(_engine->getThermostat());
    EXPECT_EQ(berendsenThermostat.getTau(), 0.1 * 1000);

    settings::ThermostatSettings::setRelaxationTime(0.2);
    EXPECT_NO_THROW(thermostatSetup.setup());

    const auto berendsenThermostat2 = dynamic_cast<thermostat::BerendsenThermostat &>(_engine->getThermostat());
    EXPECT_EQ(berendsenThermostat2.getTau(), 0.2 * 1000);

    settings::ThermostatSettings::setThermostatType("velocity_rescaling");
    EXPECT_NO_THROW(thermostatSetup.setup());

    const auto velocityRescalingThermostat = dynamic_cast<thermostat::VelocityRescalingThermostat &>(_engine->getThermostat());
    EXPECT_EQ(velocityRescalingThermostat.getTau(), 0.2 * 1000);

    settings::ThermostatSettings::setThermostatType("langevin");
    EXPECT_NO_THROW(thermostatSetup.setup());

    const auto langevinThermostat = dynamic_cast<thermostat::LangevinThermostat &>(_engine->getThermostat());
    EXPECT_EQ(langevinThermostat.getFriction(), 1.0e11);

    const auto conversionFactor =
        constants::_UNIVERSAL_GAS_CONSTANT_ * constants::_METER_SQUARED_TO_ANGSTROM_SQUARED_ * constants::_KG_TO_GRAM_;
    const auto sigma = std::sqrt(4.0 * langevinThermostat.getFriction() * conversionFactor *
                                 settings::ThermostatSettings::getTargetTemperature() / settings::TimingsSettings::getTimeStep());

    EXPECT_EQ(langevinThermostat.getSigma(), sigma);

    EXPECT_NO_THROW(setupThermostat(*_engine));
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return ::RUN_ALL_TESTS();
}