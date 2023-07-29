#ifndef _CONSTRAINTS_HPP_

#define _CONSTRAINTS_HPP_

#include "bondConstraint.hpp"

/**
 * @brief namespace for all constraints
 */
namespace constraints
{
    class Constraints;
}

/**
 * @class Constraints
 */
class constraints::Constraints
{
  private:
    bool _activated = false;

    size_t _shakeMaxIter;
    size_t _rattleMaxIter;

    double _shakeTolerance;
    double _rattleTolerance;

    double _dt;

    std::vector<BondConstraint> _bondConstraints;

  public:
    void activate() { _activated = true; }
    bool isActivated() const { return _activated; }

    void calculateConstraintBondRefs(simulationBox::SimulationBox &simulationBox);

    void addBondConstraint(BondConstraint bondConstraint) { _bondConstraints.push_back(bondConstraint); }

    void applyShake(simulationBox::SimulationBox &simulationBox);

    /***************************
     *                         *
     * standard getter methods *
     *                         *
     ***************************/

    const std::vector<BondConstraint> &getBondConstraints() const { return _bondConstraints; }

    size_t getShakeMaxIter() const { return _shakeMaxIter; }
    size_t getRattleMaxIter() const { return _rattleMaxIter; }
    double getShakeTolerance() const { return _shakeTolerance; }
    double getRattleTolerance() const { return _rattleTolerance; }

    double getDt() const { return _dt; }

    /***************************
     *                         *
     * standard setter methods *
     *                         *
     ***************************/

    void setShakeMaxIter(size_t shakeMaxIter) { _shakeMaxIter = shakeMaxIter; }
    void setRattleMaxIter(size_t rattleMaxIter) { _rattleMaxIter = rattleMaxIter; }
    void setShakeTolerance(double shakeTolerance) { _shakeTolerance = shakeTolerance; }
    void setRattleTolerance(double rattleTolerance) { _rattleTolerance = rattleTolerance; }

    void setDt(double dt) { _dt = dt; }
};

#endif   // _CONSTRAINTS_HPP_