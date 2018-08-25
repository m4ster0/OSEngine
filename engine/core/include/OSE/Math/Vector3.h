#pragma once

namespace OSE {

	struct Vector3
	{
		static Vector3 Zero();

		static Vector3 XAxis();
		static Vector3 YAxis();
		static Vector3 ZAxis();

		float x;
		float y;
		float z;

		Vector3();
		Vector3(float scalar);
		Vector3(float x, float y, float z);
		Vector3(const Vector3& other);

		Vector3& Add(const Vector3& other);
		Vector3& Subtract(const Vector3& other);
		Vector3& Multiply(const Vector3& other);
		Vector3& Divide(const Vector3& other);

		Vector3& Add(float value);
		Vector3& Subtract(float value);
		Vector3& Multiply(float value);
		Vector3& Divide(float value);

		friend Vector3 operator+(Vector3 left, const Vector3& right);
		friend Vector3 operator-(Vector3 left, const Vector3& right);
		friend Vector3 operator*(Vector3 left, const Vector3& right);
		friend Vector3 operator/(Vector3 left, const Vector3& right);

		friend Vector3 operator+(Vector3 left, float right);
		friend Vector3 operator-(Vector3 left, float right);
		friend Vector3 operator*(Vector3 left, float right);
		friend Vector3 operator/(Vector3 left, float right);

		Vector3& operator+=(const Vector3& other);
		Vector3& operator-=(const Vector3& other);
		Vector3& operator*=(const Vector3& other);
		Vector3& operator/=(const Vector3& other);

		Vector3& operator+=(float value);
		Vector3& operator-=(float value);
		Vector3& operator*=(float value);
		Vector3& operator/=(float value);

		bool operator==(const Vector3& other);
		bool operator!=(const Vector3& other);

	};

}