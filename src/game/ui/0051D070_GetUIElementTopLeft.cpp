// PROFILE: game
// NONMATCHING: the logic is complete; the original saves ebx in the prologue while ours saves it
// only on the text (case 2) path, which shifts everything after it.
// Tried: the font pointer declared at function scope; the text case as an inline helper (not inlined).
struct FontData {
	float MeasureWidth(unsigned short *s, int a);
	float MeasureHeight(unsigned short *s, int a);
	float sub_50C020(int a, float w);
	float sub_50C050(int a, float h);
};
FontData *GetFontData(int font);
struct UIRect { char pad[0x1c]; float x, y; char pad24[0x14]; float w, h; };
struct UIElement {
	char pad[0x18]; int type; char pad1c[8]; int font; char pad28[4]; UIRect *rect;
	char pad30[0x34]; unsigned short *text; char pad68[4]; int f6c; int f70;
};
// FUNCTION: 0x0051D070
void GetUIElementTopLeft(UIElement *e, float *x, float *y)
{
	if (!e)
		return;
	UIRect *r = e->rect;
	switch (e->type) {
	case 1: case 7: case 9:
		*x = r->x - r->w * 0.5f;
		*y = r->y - r->h * 0.5f;
		break;
	case 2: {
		FontData *f = GetFontData(e->font);
		if (f) {
			float w = f->MeasureWidth(e->text, 0) * r->w;
			float h = f->MeasureHeight(e->text, e->f70) * r->h;
			*x = f->sub_50C020(e->f6c, w) + r->x;
			*y = f->sub_50C050(e->f6c, h) + r->y;
		}
		break;
	}
	case 5:
		break;
	default:
		*x = r->x;
		*y = r->y;
	}
}
