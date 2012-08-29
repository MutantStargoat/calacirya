#ifndef CALA_MATH_DEF_H_
#define CALA_MATH_DEF_H_

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES 1
#endif

#include <math.h>

#define CALA_MATH_SINGLE_PRECISION

#ifdef CALA_MATH_SINGLE_PRECISION
typedef float scalar_t;
#else
typedef double scalar_t;
#endif

#define RAD_TO_DEG(a) ((((scalar_t)a) * 360.0) / TWO_PI)
#define DEG_TO_RAD(a) (((scalar_t)a) * (PI / 180.0))

#define SMALL_NUMBER	1.e-4
#define XSMALL_NUMBER	1.e-8
#define ERROR_MARGIN	1.e-6


#endif	/* CALA_MATH_DEF_H_ */
