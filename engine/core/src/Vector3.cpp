#include "OSE/Math/Vector3.h"

namespace OSE {
	
	Vector3 Vector3::Zero()
	{
		return Vector3();
	}

	Vector3 Vector3::XAxis()
	{
		return Vector3(1.0f, 0.0f, 0.0f);
	}

	Vector3 Vector3::YAxis()
	{
		return Vector3(0.0f, 1.0f, 0.0f);
	}

	Vector3 Vector3::ZAxis()
	{
		return Vector3(0.0f, 0.0f, 1.0f);
	}

	Vector3::Vector3() :
		x{ 0.0f }, y{ 0.0f }, z{ 0.0f }
	{
	}

	Vector3::Vector3(float scalar):
		x{ scalar }, y{ scalar }, z{ scalar }
	{
	}

	Vector3::Vector3(float x, float y, float z) :
		x{ x }, y{ y }, z{ z }
	{
	}

	Vector3::Vector3(const Vector3& other) :
		x{ other.x }, y{ other.y }, z{ other.z }
	{
	}

	Vector3& Vector3::Add(const Vector3 & other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	Vector3& Vector3::Subtract(const Vector3 & other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	Vector3& Vector3::Multiply(const Vector3 & other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		return *this;
	}

	Vector3& Vector3::Divide(const Vector3 & other)
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;
		return *this;
	}

	Vector3& Vector3::Add(float value)
	{
		x += value;
		y += value;
		z += value;
		return *this;
	}

	Vector3& Vector3::Subtract(float value)
	{
		x -= value;
		y -= value;
		z -= value;
		return *this;
	}

	Vector3& Vector3::Multiply(float value)
	{
		x *= value;
		y *= value;
		z *= value;
		return *this;
	}

	Vector3& Vector3::Divide(float value)
	{
		x /= value;
		y /= value;
		z /= value;
		return *this;
	}

	Vector3 operator+(Vector3 left, const Vector3& right)
	{
		return left.Add(right);
	}

	Vector3 operator-(Vector3 left, const Vector3& right)
	{
		return left.Subtract(right);
	}

	Vector3 operator*(Vector3 left, const Vector3& right)
	{
		return left.Multiply(right);
	}

	Vector3 operator/(Vector3 left, const Vector3& right)
	{
		return left.Divide(right);
	}

	Vector3 operator+(Vector3 left, float right)
	{
		return left.Add(right);
	}

	Vector3 operator-(Vector3 left, float right)
	{
		return left.Subtract(right);
	}

	Vector3 operator*(Vector3 left, float right)
	{
		return left.Multiply(right);
	}

	Vector3 operator/(Vector3 left, float right)
	{
		return left.Divide(right);
	}

	Vector3& Vector3::operator+=(const Vector3 & other)
	{
		return Add(other);
	}

	Vector3& Vector3::operator-=(const Vector3 & other)
	{
		return Subtract(other);
	}

	Vector3& Vector3::operator*=(const Vector3& other)
	{
		return Multiply(other);
	}

	Vector3& Vector3::operator/=(const Vector3& other)
	{
		return Divide(other);
	}

	Vector3& Vector3::operator+=(float value)
	{
		return Add(value);
	}

	Vector3& Vector3::operator-=(float value)
	{
		return Subtract(value);
	}

	Vector3& Vector3::operator*=(float value)
	{
		return Multiply(value);
	}

	Vector3& Vector3::operator/=(float value)
	{
		return Divide(value);
	}

	bool Vector3::operator==(const Vector3& other)
	{
		return (x == other.x) && (y == other.y) && (z == other.z);
	}

	bool Vector3::operator!=(const Vector3& other)
	{
		return !(*this == other);
	}


}