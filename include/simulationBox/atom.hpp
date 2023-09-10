#ifndef _ATOM_HPP_

#define _ATOM_HPP_

#include "vector3d.hpp"   // for Vec3D

#include <string>   // for string

namespace simulationBox
{
    /**
     * @class Atom
     *
     * @brief containing all information about an atom
     */
    class Atom
    {
      private:
        std::string _name;
        std::string _atomTypeName;

        size_t _externalGlobalVDWType;
        size_t _internalGlobalVDWType;

        size_t _externalAtomType;
        size_t _atomType;

        int    _atomicNumber;
        double _mass;
        double _partialCharge;

        linearAlgebra::Vec3D _position;
        linearAlgebra::Vec3D _velocity;
        linearAlgebra::Vec3D _force;
        linearAlgebra::Vec3D _shiftForce;

      public:
        Atom() = default;
        explicit Atom(const std::string_view &name) : _name(name){};

        void addPosition(const linearAlgebra::Vec3D &position) { _position += position; }
        void addVelocity(const linearAlgebra::Vec3D &velocity) { _velocity += velocity; }
        void addForce(const linearAlgebra::Vec3D &force) { _force += force; }
        void addShiftForce(const linearAlgebra::Vec3D &shiftForce) { _shiftForce += shiftForce; }

        void scaleVelocity(const double scaleFactor) { _velocity *= scaleFactor; }

        /***************************
         * standard getter methods *
         ***************************/

        [[nodiscard]] std::string getName() const { return _name; }

        [[nodiscard]] size_t getExternalAtomType() const { return _externalAtomType; }
        [[nodiscard]] size_t getAtomType() const { return _atomType; }

        [[nodiscard]] size_t getExternalGlobalVDWType() const { return _externalGlobalVDWType; }
        [[nodiscard]] size_t getInternalGlobalVDWType() const { return _internalGlobalVDWType; }

        [[nodiscard]] double getMass() const { return _mass; }
        [[nodiscard]] double getPartialCharge() const { return _partialCharge; }

        [[nodiscard]] linearAlgebra::Vec3D getPosition() const { return _position; }
        [[nodiscard]] linearAlgebra::Vec3D getVelocity() const { return _velocity; }
        [[nodiscard]] linearAlgebra::Vec3D getForce() const { return _force; }
        [[nodiscard]] linearAlgebra::Vec3D getShiftForce() const { return _shiftForce; }

        /***************************
         * standard setter methods *
         ***************************/

        void setPartialCharge(const double partialCharge) { _partialCharge = partialCharge; }

        void setInternalGlobalVDWType(const size_t internalGlobalVDWType) { _internalGlobalVDWType = internalGlobalVDWType; }

        void setPosition(const linearAlgebra::Vec3D &position) { _position = position; }
        void setVelocity(const linearAlgebra::Vec3D &velocity) { _velocity = velocity; }
        void setForce(const linearAlgebra::Vec3D &force) { _force = force; }
        void setShiftForce(const linearAlgebra::Vec3D &shiftForce) { _shiftForce = shiftForce; }
    };
}   // namespace simulationBox

#endif   // _ATOM_HPP_