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
};