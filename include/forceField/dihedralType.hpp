#ifndef _DIHEDRAL_TYPE_HPP_

#define _DIHEDRAL_TYPE_HPP_

#include "cstddef"

namespace forceField
{
    class DihedralType;
}

/**
 * @class DihedralType
 *
 * @brief represents a dihedral type
 *
 */
class forceField::DihedralType
{
  private:
    size_t _id;

    double _forceConstant;
    double _periodicity;
    double _phaseShift;

  public:
    DihedralType(size_t id, double forceConstant, double frequency, double phaseShift)
        : _id(id), _forceConstant(forceConstant), _periodicity(frequency), _phaseShift(phaseShift){};

    [[nodiscard]] bool operator==(const DihedralType &other) const;

    [[nodiscard]] size_t getId() const { return _id; }
    [[nodiscard]] double getForceConstant() const { return _forceConstant; }
    [[nodiscard]] double getPeriodicity() const { return _periodicity; }
    [[nodiscard]] double getPhaseShift() const { return _phaseShift; }
};

#endif   // _DIHEDRAL_TYPE_HPP_