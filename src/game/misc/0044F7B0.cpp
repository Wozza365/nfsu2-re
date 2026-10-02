// PROFILE: game
// NONMATCHING (498 bytes vs 492): logic reconstructed. The do/while search loop avoids the 4x
// unrolling a for/while loop gets. Still different: operand order of the speed multiply, fucompp vs
// fcomp in the a[]/b[] comparisons, which values live in registers (side/dir), and the final clamp.
// The types are stand-ins: Seg looks like a 0x88-byte track/path segment.
#include "bWare/bMath.h"

struct Seg { bool active; char pad1[0xb]; float dist; float a[2]; char pad18[0x30]; float b[2]; char pad50[0x38]; };
struct Path { char pad[0x10]; signed char count; char pad11[0xf]; Seg segs[1]; };
struct Obj18 { char pad[0x18]; float f18; };
struct Car { char pad[0x1c]; Obj18 *f1c; char pad20[0x410]; float f430; };
struct Obj5D { float sub_5D4520(); };
extern bool g_88F2BE; extern float g_88F2B0;
struct C44F {
	bool sub_4434F0(Seg *a, int sa, Seg *b, int sb);
	float f(Path *path, Obj5D *o, float pos, Car *car);
};
// FUNCTION: 0x0044F7B0
float C44F::f(Path *path, Obj5D *o, float pos, Car *car)
{
	float speed = car->f430;
	if (car->f1c && g_88F2BE)
		speed = g_88F2B0 * car->f1c->f18;
	bool fwd = speed >= 0.0f;
	int dir = fwd ? 1 : -1;
	int side = fwd ? 1 : 0;
	float end = fwd ? 1.0f : 0.0f;
	int last = path->count - 1;
	int i = last;
	if (i > 0) {
		do {
			if (path->segs[i].dist <= pos)
				break;
		} while (--i > 0);
	}
	Seg *cur = i == bClamp(i, 0, last) ? &path->segs[i] : 0;
	for (int j = i + dir; j == bClamp(j, 0, last); j += dir) {
		Seg *s = j == bClamp(j, 0, last) ? &path->segs[j] : 0;
		if (s->active && cur->a[side] == s->a[side ^ 1] && cur->b[side] == s->b[side ^ 1]
		    && sub_4434F0(cur, side, s, side ^ 1))
			continue;
		end = s->dist;
		break;
	}
	float x = o->sub_5D4520() * (end - pos);
	float r = 1000.0f;
	if (bAbs(speed) > 0.0001f) {
		r = bMax(x / speed, 0.0f);
	}
	return r;
}
