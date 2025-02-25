#pragma once



template<typename T>
class Math
{
	static_assert
	(
		std::is_same<T, float>::value ||
		std::is_same<T, double>::value ||
		std::is_same<T, int>::value,

		"T is not a valid type"
	);

	public:
		inline static const T PI = (T)3.141592653589793;
		inline static const T DegToRad = PI / (T)180.0;
		inline static const T RadToDeg = (T)180.0 / PI;

		static T NormalizeAngle(T _Value)
		{
			if (_Value > 180.0f)
				_Value -= 360.0f;
			else if (_Value < -180.0f)
				_Value += 360.0f;

			return _Value;
		}

		static T Clamp(const T& _Value, const T& _Lower, const T& _Upper)
		{
			return std::max<T>(_Lower, std::min<T>(_Value, _Upper));
		}

		static T Lerp(T _A, T _B, T _T)
		{
			return (1.0f - _T) * _A + _T * _B;
		}

		static T Smoothstep(T _X, T _Edge0, T _Edge1)
		{
			_X = Clamp((_X - _Edge0) / (_Edge1 - _Edge0), (T)0.0, (T)1.0);

			return _X * _X * (3 - 2 * _X);
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