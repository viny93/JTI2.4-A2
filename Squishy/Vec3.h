#pragma once

#include <math.h>

class Vec3
{
public:
	union
	{
		float data[3];
		struct { float x, y, z; };
	};

	Vec3(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	Vec3(void)
	{
		this->x = 0;
		this->y = 0;
		this->z = 0;
	}
	~Vec3(void) {}


	Vec3 operator + (Vec3& other)
	{
		return Vec3(x+other.x, y+other.y, z+other.z);
	}
	Vec3 operator - (Vec3& other)
	{
		return Vec3(x-other.x, y-other.y, z-other.z);
	}
	Vec3 operator * (float factor)
	{
		return Vec3(x*factor, y*factor, z*factor);
	}
	Vec3 operator / (float factor)
	{
		return Vec3(x/factor, y/factor, z/factor);
	}

	float length()
	{
		return sqrt(lengthSquared());
	}
	float lengthSquared()
	{
		return x*x+y*y+z*z;
	}
	Vec3 cross( Vec3 v2 )
	{
		return Vec3(y*v2.z - z*v2.y,
			z*v2.x - x*v2.z,
			x*v2.y - y*v2.x);
	}
	float dot( Vec3 v2 )
	{
		return x*v2.x+y*v2.y+z*v2.z;
	}


};

