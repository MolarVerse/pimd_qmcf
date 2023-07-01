#include "testThermostat.hpp"

#include "constants.hpp"

TEST_F(TestThermostat, calculateTemperature)
{
    _thermostat->applyThermostat(*_simulationBox, *_data);

    const auto velocity_mol1_atom1 = _simulationBox->getMolecule(0).getAtomVelocity(0);
    const auto velocity_mol1_atom2 = _simulationBox->getMolecule(0).getAtomVelocity(1);
    const auto mass_mol1_atom1     = _simulationBox->getMolecule(0).getAtomMass(0);
    const auto mass_mol1_atom2     = _simulationBox->getMolecule(0).getAtomMass(1);

    const auto velocity_mol2_atom1 = _simulationBox->getMolecule(1).getAtomVelocity(0);
    const auto mass_mol2_atom1     = _simulationBox->getMolecule(1).getAtomMass(0);

    const auto kineticEnergyAtomicVector = mass_mol1_atom1 * velocity_mol1_atom1 * velocity_mol1_atom1 +
                                           mass_mol1_atom2 * velocity_mol1_atom2 * velocity_mol1_atom2 +
                                           mass_mol2_atom1 * velocity_mol2_atom1 * velocity_mol2_atom1;

    const auto nDOF = _simulationBox->getDegreesOfFreedom();

    EXPECT_EQ(_data->getTemperature(), sum(kineticEnergyAtomicVector) * config::_TEMPERATURE_FACTOR_ / (nDOF));
}

TEST_F(TestThermostat, applyThermostatBerendsen)
{
    _thermostat = new thermostat::BerendsenThermostat(300.0, 100.0);
    _thermostat->setTimestep(0.1);

    const auto velocity_mol1_atom1 = _simulationBox->getMolecule(0).getAtomVelocity(0);
    const auto velocity_mol1_atom2 = _simulationBox->getMolecule(0).getAtomVelocity(1);
    const auto mass_mol1_atom1     = _simulationBox->getMolecule(0).getAtomMass(0);
    const auto mass_mol1_atom2     = _simulationBox->getMolecule(0).getAtomMass(1);

    const auto velocity_mol2_atom1 = _simulationBox->getMolecule(1).getAtomVelocity(0);
    const auto mass_mol2_atom1     = _simulationBox->getMolecule(1).getAtomMass(0);

    const auto kineticEnergyAtomicVector = mass_mol1_atom1 * velocity_mol1_atom1 * velocity_mol1_atom1 +
                                           mass_mol1_atom2 * velocity_mol1_atom2 * velocity_mol1_atom2 +
                                           mass_mol2_atom1 * velocity_mol2_atom1 * velocity_mol2_atom1;

    const auto nDOF = _simulationBox->getDegreesOfFreedom();

    const auto oldTemperature = sum(kineticEnergyAtomicVector) * config::_TEMPERATURE_FACTOR_ / (nDOF);

    const auto berendsenFactor = sqrt(1.0 + (0.1 / 100.0) * (300.0 / oldTemperature - 1.0));

    _thermostat->applyThermostat(*_simulationBox, *_data);

    EXPECT_EQ(_data->getTemperature(), oldTemperature * berendsenFactor * berendsenFactor);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return ::RUN_ALL_TESTS();
}