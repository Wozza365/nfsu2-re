// bMin / bMax / bClamp / bAbs
// From dbalatoni13/nfsmw src/Speed/Indep/bWare/Inc/bMath.hpp (CC0), PC branches.
// The int forms match the branch-free clamps in NFSU2 (e.g. 0x44F7B0); the float forms are unverified.
#ifndef BWARE_BMATH_H
#define BWARE_BMATH_H

#include <math.h>

inline int bMin(int a, int b) { if (a < b) return a; else return b; }
inline float bMin(float a, float b) { return a < b ? a : b; }
inline int bMax(int a, int b) { if (a > b) return a; else return b; }
inline float bMax(float a, float b) { return a > b ? a : b; }
inline int bAbs(int a) { if (a < 0) return -a; return a; }
inline float bAbs(float a) { return (float)fabs(a); }
inline int bClamp(int a, int MINIMUM, int MAXIMUM) { return bMin(MAXIMUM, bMax(a, MINIMUM)); }
inline float bClamp(float a, float MINIMUM, float MAXIMUM) { return bMin(MAXIMUM, bMax(a, MINIMUM)); }

#endif
