#pragma once



#include <cmath>



struct Vector2
{
	float X;
	float Y;

	Vector2() : X(0.0f), Y(0.0f) {}
	Vector2(float _X, float _Y) : X(_X), Y(_Y) {}

	Vector2 operator + (const Vector2& _Vector) const
	{
		return Vector2(X, Y) += _Vector;
	}

	Vector2 operator - (const Vector2& _Vector) const
	{
		return Vector2(X, Y) -= _Vector;
	}

	Vector2 operator * (float _Scalar) const
	{
		return Vector2(X, Y) *= _Scalar;
	}

	Vector2 operator / (float _Scalar) const
	{
		return Vector2(X, Y) /= _Scalar;
	}

	Vector2& operator += (const Vector2& _Vector)
	{
		X += _Vector.X;
		Y += _Vector.Y;

		return *this;
	}

	Vector2& operator -= (const Vector2& _Vector)
	{
		X -= _Vector.X;
		Y -= _Vector.Y;

		return *this;
	}

	Vector2& operator *= (float _Scalar)
	{
		X *= _Scalar;
		Y *= _Scalar;

		return *this;
	}

	Vector2& operator /= (float _Scalar)
	{
		X /= _Scalar;
		Y /= _Scalar;

		return *this;
	}

	static float Distance(const Vector2& _First, const Vector2& _Second)
	{
		Vector2 result = _First - _Second;

		return result.GetMagnitude();
	}

	static Vector2 Lerp(const Vector2& _Start, const Vector2& _End, float _Time)
	{
		Vector2 result;

		result.X = std::lerp(_Start.X, _End.X, _Time);
		result.Y = std::lerp(_Start.Y, _End.Y, _Time);

		return result;
	}

	float GetMagnitude() const
	{
		return sqrtf(X * X + Y * Y);
	}

	void Normalize()
	{
		float magnitude = GetMagnitude();

		if (magnitude > 0.0f)
		{
			X /= magnitude;
			Y /= magnitude;
		}
	}

	bool IsNull() const
	{
		return X == 0.0f && Y == 0.0f;
	}
};



struct Vector3
{
	float X;
	float Y;
	float Z;

	Vector3() : X(0.0f), Y(0.0f), Z(0.0f) {}
	Vector3(const Vector3& _Position) : X(_Position.X), Y(_Position.Y), Z(_Position.Z) {}
	Vector3(float _X, float _Y, float _Z) : X(_X), Y(_Y), Z(_Z) {}

	float& operator[](size_t _Index)
	{
		if (_Index == 0) return X;
		else if (_Index == 1) return Y;
		else return Z;
	}

	Vector3 operator + (const Vector3& _Vector) const
	{
		return Vector3(X, Y, Z) += _Vector;
	}

	Vector3 operator - (const Vector3& _Vector) const
	{
		return Vector3(X, Y, Z) -= _Vector;
	}

	Vector3 operator * (float _Scalar) const
	{
		return Vector3(X, Y, Z) *= _Scalar;
	}

	Vector3 operator / (float _Scalar) const
	{
		return Vector3(X, Y, Z) /= _Scalar;
	}

	Vector3& operator += (const Vector3& _Vector)
	{
		X += _Vector.X;
		Y += _Vector.Y;
		Z += _Vector.Z;

		return *this;
	}

	Vector3& operator -= (const Vector3& _Vector)
	{
		X -= _Vector.X;
		Y -= _Vector.Y;
		Z -= _Vector.Z;

		return *this;
	}

	Vector3& operator *= (float _Scalar)
	{
		X *= _Scalar;
		Y *= _Scalar;
		Z *= _Scalar;

		return *this;
	}

	Vector3& operator /= (float _Scalar)
	{
		X /= _Scalar;
		Y /= _Scalar;
		Z /= _Scalar;

		return *this;
	}

	static Vector3 Cross(const Vector3& _First, const Vector3& _Second)
	{
		Vector3 result;

		result.X = _First.Y * _Second.Z - _First.Z * _Second.Y;
		result.Y = _First.Z * _Second.X - _First.X * _Second.Z;
		result.Z = _First.X * _Second.Y - _First.Y * _Second.X;

		return result;
	}

	static float Distance(const Vector3& _First, const Vector3& _Second)
	{
		Vector3 result = _First - _Second;

		return result.GetMagnitude();
	}

	static Vector3 Lerp(const Vector3& _Start, const Vector3& _End, float _Time)
	{
		Vector3 result;

		result.X = std::lerp(_Start.X, _End.X, _Time);
		result.Y = std::lerp(_Start.Y, _End.Y, _Time);
		result.Z = std::lerp(_Start.Z, _End.Z, _Time);

		return result;
	}

	static Vector3 SmoothDamp(const Vector3& _Current, const Vector3& _Target, Vector3& _Velocity, float _SmoothTime, float _DeltaTime)
	{
		float omega = 2.0f / _SmoothTime;
		float x = omega * _DeltaTime;
		float exp = 1.0f / (1.0f + x + 0.48f * x * x + 0.235f * x * x * x);

		Vector3 change = _Current - _Target;
		Vector3 temp = (_Velocity + change * omega) * _DeltaTime;
		_Velocity = (_Velocity - temp * omega) * exp;

		return _Target + (change + temp) * exp;
	}

	static Vector3 SmoothDampEuler(const Vector3& _Current, const Vector3& _Target, Vector3& _Velocity, float _SmoothTime, float _DeltaTime)
	{
		float omega = 2.0f / _SmoothTime;

		Vector3 difference = _Target - _Current;

		for (int i = 0; i < 3; i++)
		{
			if (difference[i] > 180.0f) difference[i] -= 360.0f;
			if (difference[i] < -180.0f) difference[i] += 360.0f;
		}

		Vector3 temp = (_Velocity + difference * omega) * _DeltaTime;
		_Velocity = (_Velocity - (temp * omega)) * (1.0f - _DeltaTime / _SmoothTime);

		return _Current + temp;
	}

	float GetMagnitude() const
	{
		return sqrtf(X * X + Y * Y + Z * Z);
	}

	void Normalize()
	{
		float magnitude = GetMagnitude();

		if (magnitude > 0.0f)
		{
			X /= magnitude;
			Y /= magnitude;
			Z /= magnitude;
		}
	}

	Vector3 Normalized()
	{
		Vector3 v = Vector3(X, Y, Z);

		float magnitude = GetMagnitude();

		if (magnitude > 0.0f)
		{
			v.X /= magnitude;
			v.Y /= magnitude;
			v.Z /= magnitude;
		}

		return v;
	}

	Vector3 Rotate(float _Angle)
	{
		Normalize();

		float c = cosf(_Angle);
		float s = sinf(_Angle);

		return Vector3(c * X - s * Z, Y, s * X + c * Z);
	}

	bool IsNull() const
	{
		return X == 0.0f && Y == 0.0f && Z == 0.0f;
	}
};



#define PACK_VECTOR3_FROM_XYZ(_X, _Y, _Z) Vector2(_X, _Y), _Z
#define PACK_VECTOR3(_Position) Vector2(_Position.X, _Position.Y), _Position.Z