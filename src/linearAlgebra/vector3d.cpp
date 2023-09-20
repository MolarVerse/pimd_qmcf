#include "vector3d.hpp"

using namespace linearAlgebra;

template <class T>
Vector3D<T> &Vector3D<T>::operator=(Vector3D<T> &rhs)
{
    _x = rhs._x;
    _y = rhs._y;
    _z = rhs._z;
    return *this;
}

template <class T>
Vector3D<T> &Vector3D<T>::operator=(const Vector3D<T> &rhs)
{
    _x = rhs._x;
    _y = rhs._y;
    _z = rhs._z;
    return *this;
}

template <class T>
void Vector3D<T>::operator+=(const Vector3D<T> &rhs)
{
    _x += rhs._x;
    _y += rhs._y;
    _z += rhs._z;
}

template <class T>
Vector3D<T> &Vector3D<T>::operator+=(const T rhs)
{
    _x += rhs;
    _y += rhs;
    _z += rhs;
    return *this;
}

template <class T>
Vector3D<T> &Vector3D<T>::operator-=(const Vector3D<T> &rhs)
{
    _x -= rhs._x;
    _y -= rhs._y;
    _z -= rhs._z;
    return *this;
}

template <class T>
Vector3D<T> &Vector3D<T>::operator-=(const T rhs)
{
    _x -= rhs;
    _y -= rhs;
    _z -= rhs;
    return *this;
}

template <class T>
Vector3D<T> &Vector3D<T>::operator*=(const Vector3D<T> &rhs)
{
    _x *= rhs._x;
    _y *= rhs._y;
    _z *= rhs._z;
    return *this;
}

template <class T>
Vector3D<T> &Vector3D<T>::operator*=(const T rhs)
{
    _x *= rhs;
    _y *= rhs;
    _z *= rhs;
    return *this;
}

template <class T>
Vector3D<T> &Vector3D<T>::operator/=(const Vector3D<T> &rhs)
{
    _x /= rhs._x;
    _y /= rhs._y;
    _z /= rhs._z;
    return *this;
}

template <class T>
Vector3D<T> &Vector3D<T>::operator/=(const T rhs)
{
    _x /= rhs;
    _y /= rhs;
    _z /= rhs;
    return *this;
}

template class linearAlgebra::Vector3D<double>;
template class linearAlgebra::Vector3D<int>;
template class linearAlgebra::Vector3D<size_t>;
template class linearAlgebra::Vector3D<Vector3D<double>>;