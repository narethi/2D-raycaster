#ifndef MATH_MACROS
#define MATH_MACROS

#include <cmath>

using namespace std;

#ifndef PI
	#define PI (4*atan(1))
#endif

#ifndef TO_RAD
	#define TO_RAD(value) ((PI/180.0)*double(value))
#endif

#ifndef TO_DEGREE
	#define TO_DEGREE(value) ((180/PI)*double(value))
#endif

#ifndef SQUARE
	#define SQUARE(value) double(value*value)
#endif
#endif