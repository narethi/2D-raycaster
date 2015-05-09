#ifndef TYPE_DEFINITIONS_H
#define TYPE_DEFINITIONS_H

typedef unsigned int		uInt;
typedef unsigned char		uChar;
typedef unsigned long		uLong;
typedef long long			longLong;
typedef unsigned long long	uLongLong;

template<class pointType> class Point2D;
template<class pointType> class Point3D;

typedef Point2D<int>				int2D;
typedef Point2D<float>				float2D;
typedef Point2D<double>				double2D;
typedef Point2D<long>				long2D;
typedef Point2D<longLong>			longLong2D;
typedef Point2D<uInt>				uInt2D;
typedef Point2D<uLong>				uLong2D;
typedef Point2D<uLongLong>			uLongLong2D;

typedef Point3D<float>				float3D;
typedef Point3D<double>				double3D;
typedef Point3D<int>				int3D;
typedef Point3D<long>				long3D;
typedef Point3D<longLong>			longLong3D;
typedef Point3D<uInt>				uInt3D;
typedef Point3D<uLong>				uLong3D;
typedef Point3D<uLongLong>			uLongLong3D;

#endif