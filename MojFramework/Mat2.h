#pragma once
#include "Vec2.h"


template <typename T>
class Mat2_
{
public:
	Mat2_& operator=( const Mat2_& rhs )
	{
		memcpy( elements,rhs.elements,sizeof( elements ) );
		return *this;
	}
	Mat2_& operator*=( T rhs )
	{
		for( auto& row : elements )
		{
			for( T& e : row )
			{
				e *= rhs;
			}
		}
		return *this;
	}
	Mat2_ operator*( T rhs ) const
	{
		Mat2_ result = *this;
		return result *= rhs;
	}
	Mat2_ operator*( const Mat2_& rhs ) const
	{
		Mat2_ result;
		for( size_t j = 0; j < 2; j++ )
		{
			for( size_t k = 0; k < 2; k++ )
			{
				T sum = (T)0.0;
				for( size_t i = 0; i < 2; i++ )
				{
					sum += elements[j][i] * rhs.elements[i][k];
				}
				result.elements[j][k] = sum;
			}
		}
		return result;
	}
	static Mat2_ Identity()
	{
		Mat2_ i = { (T)1.0,(T)0.0,(T)0.0,(T)1.0 };
		return i;
	}
	static Mat2_ Rotation( T theta )
	{
		const T cosTheta = cos( theta );
		const T sinTheta = sin( theta );
		Mat2_ r = { 
			cosTheta,	sinTheta,
			-sinTheta,	cosTheta };
		return r;
	}
	static Mat2_ Scaling( T factor )
	{
		Mat2_ s = { factor,(T)0.0,(T)0.0,factor };
		return s;
	}
public:
	// [ row ][ col ]
	T elements[2][2];
};

template<typename T>
Vec2_<T>& operator*=( Vec2_<T>& lhs,const Mat2_<T>& rhs )
{
	return lhs = lhs * rhs;
}

template<typename T>
Vec2_<T> operator*( const Vec2_<T>& lhs,const Mat2_<T>& rhs )
{
	return { 
		lhs.x * rhs.elements[0][0] + lhs.y * rhs.elements[0][1],
		lhs.x * rhs.elements[1][0] + lhs.y * rhs.elements[1][1]
	};
}

typedef Mat2_<float> Mat2;
typedef Mat2_<double> Mad2;