#ifndef POINT_3D_H
#define POINT_3D_H

#include "typeDefinitions.h"

template<class pointType> class Point3D
{
	private:
	pointType _x, _y, _z;
	pointType getScalar(void) const;
	pointType performDotProduct(Point3D<pointType> point);
	Point3D<pointType> performCrossProduct(Point3D<pointType> point);

	public:
	Point3D();
	Point3D(pointType x, pointType y, pointType z);
	pointType getX() const;
	pointType getY() const;
	pointType getZ() const;

	Point3D operator=(int3D value)
	{
		this->_x = value.getX();
		this->_y = value.getY();
		this->_z = value.getZ();
		return *this;
	}
	Point3D operator=(long3D value)
	{
		this->_x = value.getX();
		this->_y = value.getY();
		this->_z = value.getZ();
		return *this;
	}
	Point3D operator=(float3D value)
	{
		this->_x = value.getX();
		this->_y = value.getY();
		this->_z = value.getZ();
		return *this;
	}
	Point3D operator=(double3D value)
	{
		this->_x = value.getX();
		this->_y = value.getY();
		this->_z = value.getZ();
		return *this;
	}
	Point3D operator=(uInt3D value)
	{
		this->_x = value.getX();
		this->_y = value.getY();
		this->_z = value.getZ();
		return *this;
	}
	Point3D operator=(uLong3D value)
	{
		this->_x = value.getX();
		this->_y = value.getY();
		this->_z = value.getZ();
		return *this;
	}
	Point3D operator=(uLongLong3D value)
	{
		this->_x = value.getX();
		this->_y = value.getY();
		this->_z = value.getZ();
		return *this;
	}

	Point3D operator+(int3D value)
	{
		this->_x += value.getX();
		this->_y += value.getY();
		this->_z += value.getZ();
		return *this;
	}
	Point3D operator+(long3D value)
	{
		this->_x += value.getX();
		this->_y += value.getY();
		this->_z += value.getZ();
		return *this;
	}
	Point3D operator+(float3D value)
	{
		this->_x += value.getX();
		this->_y += value.getY();
		this->_z += value.getZ();
		return *this;
	}
	Point3D operator+(double3D value)
	{
		this->_x += value.getX();
		this->_y += value.getY();
		this->_z += value.getZ();
		return *this;
	}
	Point3D operator+(uInt3D value)
	{
		this->_x += value.getX();
		this->_y += value.getY();
		this->_z += value.getZ();
		return *this;
	}
	Point3D operator+(uLong3D value)
	{
		this->_x += value.getX();
		this->_y += value.getY();
		this->_z += value.getZ();
		return *this;
	}
	Point3D operator+(uLongLong3D value)
	{
		this->_x += value.getX();
		this->_y += value.getY();
		this->_z += value.getZ();
		return *this;
	}

	Point3D operator*(int3D value)
	{
		this->_x *= value.getX();
		this->_y *= value.getY();
		this->_z *= value.getZ();
		return *this;
	}
	Point3D operator*(long3D value)
	{
		this->_x *= value.getX();
		this->_y *= value.getY();
		this->_z *= value.getZ();
		return *this;
	}
	Point3D operator*(float3D value)
	{
		this->_x *= value.getX();
		this->_y *= value.getY();
		this->_z *= value.getZ();
		return *this;
	}
	Point3D operator*(double3D value)
	{
		this->_x *= value.getX();
		this->_y *= value.getY();
		this->_z *= value.getZ();
		return *this;
	}
	Point3D operator*(uInt3D value)
	{
		this->_x *= value.getX();
		this->_y *= value.getY();
		this->_z *= value.getZ();
		return *this;
	}
	Point3D operator*(uLong3D value)
	{
		this->_x *= value.getX();
		this->_y *= value.getY();
		this->_z *= value.getZ();
		return *this;
	}
	Point3D operator*(uLongLong3D value)
	{
		this->_x *= value.getX();
		this->_y *= value.getY();
		this->_z *= value.getZ();
		return *this;
	}

	Point3D operator/(int3D value)
	{
		if(value.getX() == 0 || value.getY() == 0) try { throw 0; }
		catch(...)
		{
			SetLastError(DIVIDE_BY_ZERO);
#ifdef _DEBUG
			cout << "division by 0 arouse" << endl;
#endif
			return *this;
		}
		this->_x /= value.getX();
		this->_y /= value.getY();
		this->_z /= value.getZ();
		return *this;
	}
	Point3D operator/(long3D value)
	{
		if(value.getX() == 0 || value.getY() == 0) try { throw 0; }
		catch(...)
		{
			SetLastError(DIVIDE_BY_ZERO);
#ifdef _DEBUG
			cout << "division by 0 arouse" << endl;
#endif
			return *this;
		}
		this->_x /= value.getX();
		this->_y /= value.getY();
		this->_z /= value.getZ();
		return *this;
	}
	Point3D operator/(float3D value)
	{
		if(value.getX() == 0 || value.getY() == 0) try { throw 0; }
		catch(...)
		{
			SetLastError(DIVIDE_BY_ZERO);
#ifdef _DEBUG
			cout << "division by 0 arouse" << endl;
#endif
			return *this;
		}
		this->_x /= value.getX();
		this->_y /= value.getY();
		this->_z /= value.getZ();
		return *this;
	}
	Point3D operator/(double3D value)
	{
		if(value.getX() == 0 || value.getY() == 0) try { throw 0; }
		catch(...)
		{
			SetLastError(DIVIDE_BY_ZERO);
#ifdef _DEBUG
			cout << "division by 0 arouse" << endl;
#endif
			return *this;
		}
		this->_x /= value.getX();
		this->_y /= value.getY();
		this->_z /= value.getZ();
		return *this;
	}
	Point3D operator/(uInt3D value)
	{
		if(value.getX() == 0 || value.getY() == 0) try { throw 0; }
		catch(...)
		{
			SetLastError(DIVIDE_BY_ZERO);
#ifdef _DEBUG
			cout << "division by 0 arouse" << endl;
#endif
			return *this;
		}
		this->_x /= value.getX();
		this->_y /= value.getY();
		this->_z /= value.getZ();
		return *this;
	}
	Point3D operator/(uLong3D value)
	{
		if(value.getX() == 0 || value.getY() == 0) try { throw 0; }
		catch(...)
		{
			SetLastError(DIVIDE_BY_ZERO);
#ifdef _DEBUG
			cout << "division by 0 arouse" << endl;
#endif
			return *this;
		}
		this->_x /= value.getX();
		this->_y /= value.getY();
		this->_z /= value.getZ();
		return *this;
	}
	Point3D operator/(uLongLong3D value)
	{
		if(value.getX() == 0 || value.getY() == 0) try { throw 0; }
		catch(...)
		{
			SetLastError(DIVIDE_BY_ZERO);
#ifdef _DEBUG
			cout << "division by 0 arouse" << endl;
#endif
			return *this;
		}
		this->_x /= value.getX();
		this->_y /= value.getY();
		this->_z /= value.getZ();
		return *this;
	}

	pointType dotProduct(int3D value);
	pointType dotProduct(long3D value);
	pointType dotProduct(float3D value);
	pointType dotProduct(double3D value);
	pointType dotProduct(uInt3D value);
	pointType dotProduct(uLong3D value);
	pointType dotProduct(uLongLong3D value);

	Point3D crossProduct(int3D value);
	Point3D crossProduct(long3D value);
	Point3D crossProduct(float3D value);
	Point3D crossProduct(double3D value);
	Point3D crossProduct(uInt3D value);
	Point3D crossProduct(uLong3D value);
	Point3D crossProduct(uLongLong3D value);
};

template <class pointType> Point3D<pointType>::Point3D() :
_x(0), _y(0), _z(0)
{}
template <class pointType> Point3D<pointType>::Point3D(pointType x, pointType y, pointType z) :
_x(x), _y(y), _z(z)
{}

template <class pointType> pointType Point3D<pointType>::getX() const
{
	return _x;
}
template <class pointType> pointType Point3D<pointType>::getY() const
{
	return _y;
}
template <class pointType> pointType Point3D<pointType>::getZ() const
{
	return _z;
}

template <class pointType>  pointType Point3D<pointType>::dotProduct(int3D value)
{
	Point3D<pointType> temp = value;
	return performDotProduct(temp);
}
template <class pointType>  pointType Point3D<pointType>::dotProduct(long3D value)
{
	Point3D<pointType> temp = value;
	return performDotProduct(temp);
}
template <class pointType>  pointType Point3D<pointType>::dotProduct(float3D value)
{
	Point3D<pointType> temp = value;
	return performDotProduct(temp);
}
template <class pointType>  pointType Point3D<pointType>::dotProduct(double3D value)
{
	Point3D<pointType> temp = value;
	return performDotProduct(temp);
}
template <class pointType>  pointType Point3D<pointType>::dotProduct(uInt3D value)
{
	Point3D<pointType> temp = value;
	return performDotProduct(temp);
}
template <class pointType>  pointType Point3D<pointType>::dotProduct(uLong3D value)
{
	Point3D<pointType> temp = value;
	return performDotProduct(temp);
}
template <class pointType>  pointType Point3D<pointType>::dotProduct(uLongLong3D value)
{
	Point3D<pointType> temp = value;
	return performDotProduct(temp);
}

template <class pointType>  Point3D<pointType> Point3D<pointType>::crossProduct(int3D value)
{
	Point3D<pointType> temp = value;
	return performCrossProduct(temp);
}
template <class pointType>  Point3D<pointType> Point3D<pointType>::crossProduct(long3D value)
{
	Point3D<pointType> temp = value;
	return performCrossProduct(temp);
}
template <class pointType>  Point3D<pointType> Point3D<pointType>::crossProduct(float3D value)
{
	Point3D<pointType> temp = value;
	return performCrossProduct(temp);
}
template <class pointType>  Point3D<pointType> Point3D<pointType>::crossProduct(double3D value)
{
	Point3D<pointType> temp = value;
	return performCrossProduct(temp);
}
template <class pointType>  Point3D<pointType> Point3D<pointType>::crossProduct(uInt3D value)
{
	Point3D<pointType> temp = value;
	return performCrossProduct(temp);
}
template <class pointType>  Point3D<pointType> Point3D<pointType>::crossProduct(uLong3D value)
{
	Point3D<pointType> temp = value;
	return performCrossProduct(temp);
}
template <class pointType>  Point3D<pointType> Point3D<pointType>::crossProduct(uLongLong3D value)
{
	Point3D<pointType> temp = value;
	return performCrossProduct(temp);
}

template <class pointType> pointType Point3D<pointType>::getScalar(void) const
{return _x + _y + _z;}
template <class pointType> pointType Point3D<pointType>::performDotProduct(Point3D<pointType> value)
{return (*this * value).getScalar();}
template <class pointType> Point3D<pointType> Point3D<pointType>::performCrossProduct(Point3D<pointType> value)
{
	Point3D<pointType> temp(_y*value.getZ() - _z*value.getY(),
		_z*value.getX() - _x*value.getZ(),
		_x*value.getY() - _y*value.getX());
	return temp;
}

#endif