#include <vector>
#include <string>
#include <stdexcept>
#include <iostream>
#include <cmath>

#include "box.hpp"
#include "exceptions.hpp"
#include "constants.hpp"

using namespace std;

vector<double> Box::getBoxDimensions() const
{
    return _boxDimensions;
}

/**
 * @brief Set the Box Dimensions in Box object
 *
 * @param boxDimensions
 *
 * @throw RstFileException if any of the dimensions is negative
 */
void Box::setBoxDimensions(const vector<double> &boxDimensions)
{
    for (auto &dimension : boxDimensions)
        if (dimension < 0.0)
            throw RstFileException("Box dimensions must be positive - dimension = " + to_string(dimension));

    _boxDimensions = boxDimensions;
}

vector<double> Box::getBoxAngles() const
{
    return _boxAngles;
}

/**
 * @brief Set the Box Angles in Box object
 *
 * @param boxAngles
 *
 * @throw RstFileException if any of the angles is negative or greater than 90°
 */
void Box::setBoxAngles(const vector<double> &boxAngles)
{
    for (auto &angle : boxAngles)
        if (angle < 0.0 || angle > 90.0)
            throw RstFileException("Box angles must be positive and smaller than 90° - angle = " + to_string(angle));

    _boxAngles = boxAngles;
}

/**
 * @brief Set the Density in Box object
 *
 * @param density
 *
 * @throw InputFileException if density is negative
 */
void Box::setDensity(double density)
{
    if (density < 0.0)
        throw InputFileException("Density must be positive - density = " + to_string(density));

    _density = density;
}

/**
 * @brief Calculate the volume of the box
 *
 * @details
 *  The volume is calculated using the formula:
 *  V = a * b * c * sqrt(1 - cos(alpha)^2 - cos(beta)^2 - cos(gamma)^2 + 2 * cos(alpha) * cos(beta) * cos(gamma))
 *  where a, b, c are the box dimensions and alpha, beta, gamma are the box angles.
 *
 *  The volume is stored in the _volume attribute and returned.
 *  The density is also calculated and stored in the _density attribute.
 *
 * @return volume
 */
double Box::calculateVolume() const
{
    double volume = _boxDimensions[0] * _boxDimensions[1] * _boxDimensions[2];

    double cos_alpha = cos(_boxAngles[0] * M_PI / 180.0);
    double cos_beta = cos(_boxAngles[1] * M_PI / 180.0);
    double cos_gamma = cos(_boxAngles[2] * M_PI / 180.0);

    volume *= sqrt(1.0 - cos_alpha * cos_alpha - cos_beta * cos_beta - cos_gamma * cos_gamma + 2.0 * cos_alpha * cos_beta * cos_gamma);

    return volume;
}

/**
 * @brief Calculate the box dimensions from the density
 *
 * @return vector<double>
 */
vector<double> Box::calculateBoxDimensionsFromDensity() const
{
    double volume = _totalMass / (_density * _KG_PER_LITER_CUBIC_TO_AMU_PER_ANGSTROM_CUBIC_);
    double a = cbrt(volume);
    double b = cbrt(volume);
    double c = cbrt(volume);

    vector<double> boxDimensions = {a, b, c};

    return boxDimensions;
}