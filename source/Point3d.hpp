// Point3d.hpp
#ifndef POINT3D_HPP
#define POINT3D_HPP

#include <vector>
#include <array>

#include "Output.hpp"
#include "debug.hpp"

template<typename T>
class Point3d : public Output {
public:
	using Vector = std::vector<Point3d>;

public:
	Point3d(T const& x, T const& y, T const& z) :
		_x(x),
		_y(y),
		_z(z)
	{}

	T const& x() const { return _x; }
	T const& y() const { return _y; }
	T const& z() const { return _z; }

	void set_x(T const& x) { _x = x; }
	void set_y(T const& y) { _y = y; }
	void set_z(T const& z) { _z = z; }

	T norm() const
	{
		return x() + y() + z();
	}

	Point3d operator-(Point3d const& rhs) const
	{
		return Point3d(this->x() - rhs.x(), this->y() - rhs.y(), this->z() - rhs.z());
	}

	virtual std::string to_string() const override
	{
		return "(" + std::to_string(x()) + ", " + std::to_string(y()) + ", " + std::to_string(z()) + ")";
	}

private:
	T _x;
	T _y;
	T _z;
};

#endif
