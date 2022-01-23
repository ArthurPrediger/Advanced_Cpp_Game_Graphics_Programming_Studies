#pragma once

#pragma once

template<typename T>
class Vec3_
{
public:
	Vec3_()
	{}
	Vec3_(T x, T y)
		:
		x(x),
		y(y)
	{}
	Vec3_(const Vec3_& vect)
		:
		Vec3_(vect.x, vect.y)
	{}
	Vec3_(const Vec2_<T>& v2)
		:
		Vec3_(v2.x, v2.y)
	{}
	explicit operator Vec2_<T>() const
	{
		return { x, y };
	}
	template <typename T2>
	explicit operator Vec3_<T2>() const
	{
		return{ (T2)x,(T2)y };
	}
	T		LenSq() const
	{
		return x * x + y * y;
	}
	T		Len() const
	{
		return sqrt(LenSq());
	}
	Vec3_& Normalize()
	{
		const T length = Len();
		x /= length;
		y /= length;
		return *this;
	}
	Vec3_	GetNormalized() const
	{
		Vec3_ norm = *this;
		norm.Normalize();
		return norm;
	}
	Vec3_& Rotate(T angle)
	{
		const T cosTheta = cos(angle);
		const T sinTheta = sin(angle);

		const T new_x = x * cosTheta - y * sinTheta;
		y = x * sinTheta + y * cosTheta;
		x = new_x;
		return *this;
	}
	Vec3_ Rotate(T angle) const
	{
		return Vec3_(*this).Rotate(angle);
	}
	T		operator*(const Vec3_& rhs) const
	{
		return x * rhs.x + y * rhs.y;
	}
	Vec3_	operator-() const
	{
		return Vec3_(-x, -y);
	}
	Vec3_& operator=(const Vec3_& rhs)
	{
		x = rhs.x;
		y = rhs.y;
		w = rhs.w;
		return *this;
	}
	Vec3_& operator+=(const Vec3_& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}
	Vec3_& operator-=(const Vec3_& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}
	Vec3_	operator+(const Vec3_& rhs) const
	{
		return Vec3_(*this) += rhs;
	}
	Vec3_	operator-(const Vec3_& rhs) const
	{
		return Vec3_(*this) -= rhs;
	}
	Vec3_& operator*=(const T& rhs)
	{
		x *= rhs;
		y *= rhs;
		return *this;
	}
	Vec3_	operator*(const T& rhs) const
	{
		return Vec3_(*this) *= rhs;
	}
	Vec3_& operator/=(const T& rhs)
	{
		x /= rhs;
		y /= rhs;
		return *this;
	}
	Vec3_	operator/(const T& rhs) const
	{
		return Vec3_(*this) /= rhs;
	}
	bool	operator==(const Vec3_& rhs) const
	{
		return x == rhs.x && y == rhs.y;
	}
	bool	operator!=(const Vec3_& rhs) const
	{
		return !(*this == rhs);
	}
public:
	T x;
	T y;
	T w = (T)1;
};
typedef Vec3_<float> Vec3;
typedef Vec3_<double> Ved3;
typedef Vec3_<int> Vei3;