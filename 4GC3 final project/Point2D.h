#ifndef POINT_2D_H
#define POINT_2D_H

#include <cmath>
#include "mathMacros.h"
#include "typeDefinitions.h"

template<class pointType> class Point2D
{
	private:
		pointType _x, _y;
		pointType _getScalar(void) const;
		pointType _performDotProduct(Point2D<pointType> point);
		pointType _performCross(Point2D<pointType> point);
		Point2D<pointType> _performRotation(double value);
		Point2D<pointType> _performScalarMultiplication(pointType value);
		Point2D<pointType> _performScalarDivision(pointType value);

	public:
		Point2D();
		Point2D(pointType x, pointType y);
		pointType getX() const;
		pointType getY() const;

		bool operator==(int2D value)
		{
			if(this->_x == value.getX() && this->_y == value.getY())
			return true;
			return false;
		}

		bool operator==(long2D value)
		{
			if(this->_x == value.getX() && this->_y == value.getY())
				return true;
			return false;
		}

		bool operator==(float2D value)
		{
			if(this->_x == value.getX() && this->_y == value.getY())
				return true;
			return false;
		}

		bool operator==(double2D value)
		{
			if(this->_x == value.getX() && this->_y == value.getY())
				return true;
			return false;
		}

		bool operator==(uInt2D value)
		{
			if(this->_x == value.getX() && this->_y == value.getY())
				return true;
			return false;
		}

		bool operator==(uLong2D value)
		{
			if(this->_x == value.getX() && this->_y == value.getY())
				return true;
			return false;
		}

		bool operator==(uLongLong2D value)
		{
			if(this->_x == value.getX() && this->_y == value.getY())
				return true;
			return false;
		}

		Point2D operator=(int2D value)
		{
			this->_x = value.getX();
			this->_y = value.getY();
			return *this;
		}
		Point2D operator=(long2D value)
		{
			this->_x = value.getX();
			this->_y = value.getY();
			return *this;
		}		
		Point2D operator=(float2D value)
		{
			this->_x = value.getX();
			this->_y = value.getY();
			return *this;
		}		
		Point2D operator=(double2D value)
		{
			this->_x = value.getX();
			this->_y = value.getY();
			return *this;
		}
		Point2D operator=(longLong2D value)
		{
			this->_x = value.getX();
			this->_y = value.getY();
			return *this;
		}
		Point2D operator=(uInt2D value)
		{
			this->_x = value.getX();
			this->_y = value.getY();
			return *this;
		}
		Point2D operator=(uLong2D value)
		{
			this->_x = value.getX();
			this->_y = value.getY();
			return *this;
		}
		Point2D operator=(uLongLong2D value)
		{
			this->_x = value.getX();
			this->_y = value.getY();
			return *this;
		}

		Point2D operator+(int2D value)
		{return Point2D(_x+value.getX(), _y+value.getY());}
		Point2D operator+(long2D value)
		{return Point2D(_x + value.getX(), _y + value.getY());}
		Point2D operator+(float2D value)
		{return Point2D(_x + value.getX(), _y + value.getY());}
		Point2D operator+(double2D value)
		{return Point2D(_x + value.getX(), _y + value.getY());}
		Point2D operator+(longLong2D value)
		{return Point2D(_x + value.getX(), _y + value.getY());}
		Point2D operator+(uInt2D value)
		{return Point2D(_x + value.getX(), _y + value.getY());}
		Point2D operator+(uLong2D value)
		{return Point2D(_x + value.getX(), _y + value.getY());}
		Point2D operator+(uLongLong2D value)
		{return Point2D(_x + value.getX(), _y + value.getY());}

		Point2D operator-(int2D value)
		{return Point2D(_x - value.getX(), _y - value.getY());}
		Point2D operator-(long2D value)
		{return Point2D(_x - value.getX(), _y - value.getY());}
		Point2D operator-(float2D value)
		{return Point2D(_x - value.getX(), _y - value.getY());}
		Point2D operator-(double2D value)
		{return Point2D(_x - value.getX(), _y - value.getY());}
		Point2D operator-(longLong2D value)
		{return Point2D(_x - value.getX(), _y - value.getY());}
		Point2D operator-(uInt2D value)
		{return Point2D(_x - value.getX(), _y - value.getY());}
		Point2D operator-(uLong2D value)
		{return Point2D(_x - value.getX(), _y - value.getY());}
		Point2D operator-(uLongLong2D value)
		{return Point2D(_x - value.getX(), _y - value.getY());}

		Point2D operator*(int2D value)
		{
			this->_x *= value.getX();
			this->_y *= value.getY();
			return *this;
		}
		Point2D operator*(long2D value)
		{
			this->_x *= value.getX();
			this->_y *= value.getY();
			return *this;
		}
		Point2D operator*(float2D value)
		{
			this->_x *= value.getX();
			this->_y *= value.getY();
			return *this;
		}
		Point2D operator*(double2D value)
		{
			this->_x *= value.getX();
			this->_y *= value.getY();
			return *this;
		}
		Point2D operator*(longLong2D value)
		{
			this->_x *= value.getX();
			this->_y *= value.getY();
			return *this;
		}
		Point2D operator*(uInt2D value)
		{
			this->_x *= value.getX();
			this->_y *= value.getY();
			return *this;
		}
		Point2D operator*(uLong2D value)
		{
			this->_x *= value.getX();
			this->_y *= value.getY();
			return *this;
		}
		Point2D operator*(uLongLong2D value)
		{
			this->_x *= value.getX();
			this->_y *= value.getY();
			return *this;
		}

		Point2D operator*(int value) 
		{return _performScalarMultiplication(pointType(value));}
		Point2D operator*(long value) 
		{ return _performScalarMultiplication(pointType(value)); }
		Point2D operator*(float value)
		{return _performScalarMultiplication(pointType(value));}
		Point2D operator*(double value)
		{return _performScalarMultiplication(pointType(value));}
		Point2D operator*(longLong value)
		{return _performScalarMultiplication(pointType(value));}
		Point2D operator*(uInt value)
		{return _performScalarMultiplication(pointType(value));}
		Point2D operator*(uLong value)
		{ return _performScalarMultiplication(pointType(value));}
		Point2D operator*(uLongLong value)
		{return _performScalarMultiplication(pointType(value));}

		Point2D operator/(int value)
		{
			return _performScalarDivision(pointType(value));
		}
		Point2D operator/(long value)
		{
			return _performScalarDivision(pointType(value));
		}
		Point2D operator/(float value)
		{return _performScalarDivision(pointType(value));}
		Point2D operator/(double value)
		{return _performScalarDivision(pointType(value));}
		Point2D operator/(longLong value)
		{return _performScalarDivision(pointType(value));}
		Point2D operator/(uInt value)
		{return _performScalarDivision(pointType(value));}
		Point2D operator/(uLong value)
		{return _performScalarDivision(pointType(value));}
		Point2D operator/(uLongLong value)
		{return _performScalarDivision(pointType(value));}

		Point2D operator/(int2D value)
		{
			if(value.getX() == 0 || value.getY() == 0) try {throw 0;}
			catch(...)
			{
				SetLastError(DIVIDE_BY_ZERO);
#ifdef _DEBUG
				cout << "division by 0 arouse" << endl;
#endif
				return *this;
			}
			return Point2D(_x/value.getX(), _y/value.getY());
		}
		Point2D operator/(long2D value)
		{
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
				return Point2D(_x / value.getX(), _y / value.getY());
			}
		}
		Point2D operator/(float2D value)
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
			return Point2D(_x / value.getX(), _y / value.getY());
		}
		Point2D operator/(double2D value)
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
			return Point2D(_x / value.getX(), _y / value.getY());
		}
		Point2D operator/(longLong2D value)
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
			return Point2D(_x / value.getX(), _y / value.getY());
		}
		Point2D operator/(uInt2D value)
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
			return Point2D(_x / value.getX(), _y / value.getY());
		}
		Point2D operator/(uLong2D value)
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
			return Point2D(_x / value.getX(), _y / value.getY());
		}
		Point2D operator/(uLongLong2D value)
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
			return Point2D(_x / value.getX(), _y / value.getY());
		}

		pointType dotProduct(int2D value);
		pointType dotProduct(long2D value);
		pointType dotProduct(float2D value);
		pointType dotProduct(double2D value);
		pointType dotProduct(longLong2D value);
		pointType dotProduct(uInt2D value);
		pointType dotProduct(uLong2D value);
		pointType dotProduct(uLongLong2D value);
		
		pointType cross(int2D value);
		pointType cross(long2D value);
		pointType cross(float2D value);
		pointType cross(double2D value);
		pointType cross(longLong2D value);
		pointType cross(uInt2D value);
		pointType cross(uLong2D value);
		pointType cross(uLongLong2D value);

		Point2D<pointType> polarRotate(float radianAngle);
		Point2D<pointType> polarRotate(double radianAngle);
		Point2D<pointType> polarRotate(int degreeAngle);
		Point2D<pointType> polarRotate(long degreeAngle);
		Point2D<pointType> polarRotate(longLong degreeAngle);
		Point2D<pointType> polarRotate(uInt degreeAngle);
		Point2D<pointType> polarRotate(uLong degreeAngle);
		Point2D<pointType> polarRotate(uLongLong degreeAngle);
};

template <class pointType> Point2D<pointType>::Point2D(pointType x, pointType y) :
_x(x), _y(y)
{}

template <class pointType> Point2D<pointType>::Point2D() : Point2D<pointType>(0, 0) {}

template <class pointType> pointType Point2D<pointType>::getX() const {return _x;}
template <class pointType> pointType Point2D<pointType>::getY() const {return _y;}

template <class pointType>  pointType Point2D<pointType>::dotProduct(int2D value)
{
	Point2D<pointType> temp = value;
	return _performDotProduct(temp);
}
template <class pointType>  pointType Point2D<pointType>::dotProduct(long2D value)
{
	Point2D<pointType> temp = value;
	return _performDotProduct(temp);
}
template <class pointType>  pointType Point2D<pointType>::dotProduct(float2D value)
{
	Point2D<pointType> temp = value;
	return _performDotProduct(temp);
}
template <class pointType>  pointType Point2D<pointType>::dotProduct(double2D value)
{
	Point2D<pointType> temp = value;
	return _performDotProduct(temp);
}
template <class pointType>  pointType Point2D<pointType>::dotProduct(longLong2D value)
{
	Point2D<pointType> temp = value;
	return _performDotProduct(temp);
}
template <class pointType>  pointType Point2D<pointType>::dotProduct(uInt2D value)
{
	Point2D<pointType> temp = value;
	return _performDotProduct(temp);
}
template <class pointType>  pointType Point2D<pointType>::dotProduct(uLong2D value)
{
	Point2D<pointType> temp = value;
	return _performDotProduct(temp);
}
template <class pointType>  pointType Point2D<pointType>::dotProduct(uLongLong2D value)
{
	Point2D<pointType> temp = value;
	return _performDotProduct(temp);
}

template <class pointType>  pointType Point2D<pointType>::cross(int2D value)
{
	Point2D<pointType> temp = value;
	return _performCross(temp);
}
template <class pointType>  pointType Point2D<pointType>::cross(long2D value)
{
	Point2D<pointType> temp = value;
	return _performCross(temp);
}
template <class pointType>  pointType Point2D<pointType>::cross(float2D value)
{
	Point2D<pointType> temp = value;
	return _performCross(temp);
}
template <class pointType>  pointType Point2D<pointType>::cross(double2D value)
{
	Point2D<pointType> temp = value;
	return _performCross(temp);
}
template <class pointType>  pointType Point2D<pointType>::cross(longLong2D value)
{
	Point2D<pointType> temp = value;
	return _performCross(temp);
}
template <class pointType>  pointType Point2D<pointType>::cross(uInt2D value)
{
	Point2D<pointType> temp = value;
	return _performCross(temp);
}
template <class pointType>  pointType Point2D<pointType>::cross(uLong2D value)
{
	Point2D<pointType> temp = value;
	return _performCross(temp);
}
template <class pointType>  pointType Point2D<pointType>::cross(uLongLong2D value)
{
	Point2D<pointType> temp = value;
	return _performCross(temp);
}

template <class pointType> Point2D<pointType> Point2D<pointType>::polarRotate(float value)
{
	double temp = value;
	return _performRotation(temp);
}
template <class pointType> Point2D<pointType> Point2D<pointType>::polarRotate(double value)
{
	return _performRotation(value);
}
template <class pointType> Point2D<pointType> Point2D<pointType>::polarRotate(int value)
{
	double temp(TO_RAD(value));
	return _performRotation(temp);
}
template <class pointType> Point2D<pointType> Point2D<pointType>::polarRotate(long value)
{
	double temp(TO_RAD(value));
	return _performRotation(temp);
}
template <class pointType> Point2D<pointType> Point2D<pointType>::polarRotate(longLong value)
{
	double temp(TO_RAD(value));
	return _performRotation(temp);
}
template <class pointType> Point2D<pointType> Point2D<pointType>::polarRotate(uLongLong value)
{
	double temp(TO_RAD(value));
	return _performRotation(temp);
}
template <class pointType> Point2D<pointType> Point2D<pointType>::polarRotate(uInt value)
{
	double temp(TO_RAD(value));
	return _performRotation(temp);
}

template <class pointType> pointType Point2D<pointType>::_getScalar(void) const
{return _x + _y;}
template <class pointType> pointType Point2D<pointType>::_performDotProduct(Point2D<pointType> value)
{return (*this * value)._getScalar();}
template <class pointType> pointType Point2D<pointType>::_performCross(Point2D<pointType> value)
{return (Point2D<pointType>(this->x * value.y, -(this->y * value.x)))->_getScalar();}
template <class pointType> Point2D<pointType> Point2D<pointType>::_performRotation(double value)
{return Point2D<pointType>(cos(value), sin(value));}
template <class pointType> Point2D<pointType> Point2D<pointType>::_performScalarMultiplication(pointType value)
{
	return Point2D(value*_x, value*_y);
}
template <class pointType> Point2D<pointType> Point2D<pointType>::_performScalarDivision(pointType value)
{
	if(value == 0) try { throw 0; }
	catch(...)
	{
		SetLastError(DIVIDE_BY_ZERO);
#ifdef _DEBUG
		cout << "division by 0 arouse" << endl;
#endif
		return *this;
	}
	return Point2D(_x / value, _y / value);
}

#endif