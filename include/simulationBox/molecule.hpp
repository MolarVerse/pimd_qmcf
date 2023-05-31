#ifndef _MOLECULE_H_

#define _MOLECULE_H_

#include <string>
#include <vector>
#include <map>

/**
 * @class Molecule
 *
 * @brief containing all information about a molecule
 */
class Molecule
{
private:
    std::string _name;

    int _moltype;
    int _numberOfAtoms;
    double _charge;
    double _molMass;

    std::vector<std::string> _atomNames;
    std::vector<std::string> _atomTypeNames;

    std::vector<int> _externalAtomTypes;
    std::vector<int> _atomTypes;
    std::map<int, int> _externalToInternalAtomTypes;

    std::vector<double> _partialCharges;
    std::vector<int> _globalVDWTypes;
    std::vector<double> _masses;
    std::vector<int> _atomicNumbers;

    std::vector<double> _positions;
    std::vector<double> _velocities;
    std::vector<double> _forces;
    std::vector<double> _shiftForces;

    std::vector<double> _positionsOld;
    std::vector<double> _velocitiesOld;
    std::vector<double> _forcesOld;

    std::vector<double> _centerOfMass = {0.0, 0.0, 0.0};

    void addVector(std::vector<double> &vector, const std::vector<double> &vectorToAdd) const;

public:
    Molecule() = default;
    explicit Molecule(std::string_view name) : _name(name){};
    explicit Molecule(int moltype) : _moltype(moltype){};

    void setName(std::string_view name) { _name = name; };
    std::string getName() const { return _name; };

    void setMoltype(int moltype) { _moltype = moltype; };
    int getMoltype() const { return _moltype; };

    void setNumberOfAtoms(int numberOfAtoms);
    int getNumberOfAtoms() const { return _numberOfAtoms; };

    void setCharge(double charge) { _charge = charge; };
    double getCharge() const { return _charge; };

    void setMolMass(double molMass) { _molMass = molMass; };
    double getMolMass() const { return _molMass; };

    void addAtomName(const std::string &atomName) { _atomNames.push_back(atomName); };
    std::string getAtomName(int index) const { return _atomNames[index]; };

    void addAtomTypeName(const std::string &atomTypeName) { _atomTypeNames.push_back(atomTypeName); };
    std::string getAtomTypeName(int index) const { return _atomTypeNames[index]; };

    void addExternalAtomType(int atomType) { _externalAtomTypes.push_back(atomType); };
    int getExternalAtomType(int index) const { return _externalAtomTypes[index]; };
    std::vector<int> getExternalAtomTypes() const { return _externalAtomTypes; };
    void addExternalToInternalAtomTypeElement(int externalAtomType, int internalAtomType) { _externalToInternalAtomTypes.try_emplace(externalAtomType, internalAtomType); };

    void addAtomType(int atomType) { _atomTypes.push_back(atomType); };
    int getInternalAtomType(int externalAtomType) { return _externalToInternalAtomTypes[externalAtomType]; };
    int getAtomType(int index) const { return _atomTypes[index]; };

    void addPartialCharge(double partialCharge) { _partialCharges.push_back(partialCharge); };
    double getPartialCharge(int index) const { return _partialCharges[index]; };

    void addGlobalVDWType(int globalVDWType) { _globalVDWTypes.push_back(globalVDWType); };
    int getGlobalVDWType(int index) const { return _globalVDWTypes[index]; };

    void addMass(double mass) { _masses.push_back(mass); };
    double getMass(int index) const { return _masses[index]; };

    void addAtomicNumber(int atomicNumber) { _atomicNumbers.push_back(atomicNumber); };
    int getAtomicNumber(int index) const { return _atomicNumbers[index]; };

    void addAtomPositions(const std::vector<double> &positions) { addVector(_positions, positions); }
    std::vector<double> getAtomPositions(int index) { return {_positions[3 * index], _positions[3 * index + 1], _positions[3 * index + 2]}; }
    void getAtomPositions(int index, std::vector<double> &position) const
    {
        position[0] = _positions[3 * index];
        position[1] = _positions[3 * index + 1];
        position[2] = _positions[3 * index + 2];
    }
    double getAtomPositions(int index, int dimension) const { return _positions[3 * index + dimension]; }
    void setAtomPositions(int index, const std::vector<double> &position)
    {
        _positions[3 * index] = position[0];
        _positions[3 * index + 1] = position[1];
        _positions[3 * index + 2] = position[2];
    }

    void addAtomVelocities(const std::vector<double> &velocities) { addVector(_velocities, velocities); }
    std::vector<double> getAtomVelocities(int index) { return {_velocities[3 * index], _velocities[3 * index + 1], _velocities[3 * index + 2]}; }
    void getAtomVelocities(int index, std::vector<double> &velocity) const
    {
        velocity[0] = _velocities[3 * index];
        velocity[1] = _velocities[3 * index + 1];
        velocity[2] = _velocities[3 * index + 2];
    }
    void setAtomVelocities(int index, const std::vector<double> &velocity)
    {
        _velocities[3 * index] = velocity[0];
        _velocities[3 * index + 1] = velocity[1];
        _velocities[3 * index + 2] = velocity[2];
    }

    void addAtomForce(const std::vector<double> &forces) { addVector(_forces, forces); }
    std::vector<double> getAtomForces(int index) { return {_forces[3 * index], _forces[3 * index + 1], _forces[3 * index + 2]}; }
    void getAtomForces(int index, std::vector<double> &force) const
    {
        force[0] = _forces[3 * index];
        force[1] = _forces[3 * index + 1];
        force[2] = _forces[3 * index + 2];
    }
    void addAtomForces(int index, const std::vector<double> &force)
    {
        _forces[3 * index] += force[0];
        _forces[3 * index + 1] += force[1];
        _forces[3 * index + 2] += force[2];
    }
    void subtractAtomForces(int index, const std::vector<double> &force)
    {
        _forces[3 * index] -= force[0];
        _forces[3 * index + 1] -= force[1];
        _forces[3 * index + 2] -= force[2];
    }
    void resetAtomForces() { std::fill(_forces.begin(), _forces.end(), 0.0); }

    void resizeAtomShiftForces() { _shiftForces.resize(_forces.size()); }
    void setAtomShiftForces(int index, const std::vector<double> &shiftForces)
    {
        _shiftForces[3 * index] = shiftForces[0];
        _shiftForces[3 * index + 1] = shiftForces[1];
        _shiftForces[3 * index + 2] = shiftForces[2];
    }
    void getAtomShiftForces(int index, std::vector<double> &shiftForce) const
    {
        shiftForce[0] = _shiftForces[3 * index];
        shiftForce[1] = _shiftForces[3 * index + 1];
        shiftForce[2] = _shiftForces[3 * index + 2];
    }
    void addAtomShifForces(int index, const std::vector<double> &shiftForces)
    {
        _shiftForces[3 * index] += shiftForces[0];
        _shiftForces[3 * index + 1] += shiftForces[1];
        _shiftForces[3 * index + 2] += shiftForces[2];
    }

    void addAtomPositionOld(const std::vector<double> &positionsOld) { addVector(_positionsOld, positionsOld); }
    std::vector<double> getAtomPositionOld(int index) { return {_positionsOld[3 * index], _positionsOld[3 * index + 1], _positionsOld[3 * index + 2]}; }

    void addAtomVelocityOld(const std::vector<double> &velocitiesOld) { addVector(_velocitiesOld, velocitiesOld); }
    std::vector<double> getAtomVelocityOld(int index) { return {_velocitiesOld[3 * index], _velocitiesOld[3 * index + 1], _velocitiesOld[3 * index + 2]}; }

    void addAtomForceOld(const std::vector<double> &forcesOld) { addVector(_forcesOld, forcesOld); }
    std::vector<double> getAtomForceOld(int index) { return {_forcesOld[3 * index], _forcesOld[3 * index + 1], _forcesOld[3 * index + 2]}; }

    int getNumberOfAtomTypes();

    std::vector<double> getCenterOfMass();
    void getCenterOfMass(std::vector<double> &centerOfMass) const
    {
        centerOfMass[0] = _centerOfMass[0];
        centerOfMass[1] = _centerOfMass[1];
        centerOfMass[2] = _centerOfMass[2];
    }
    void calculateCenterOfMass(const std::vector<double> &);
};

#endif
