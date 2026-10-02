// PROFILE: game
struct DialogInfo; int CalcDialogTextLengthWcharAware(DialogInfo *d); void SetWcharFromDialogText(unsigned short *dst, int len, DialogInfo *d); struct WideCharString { unsigned short *buf; void EnsureAllocatedSize(int n); }; struct UILabel { char pad0[0x1c]; int flags; char pad20[0x44]; WideCharString text; int SetStringToDialogText(DialogInfo *d); };
// FUNCTION: 0x0052C2F0
int UILabel::SetStringToDialogText(DialogInfo *d) { int len = CalcDialogTextLengthWcharAware(d); text.EnsureAllocatedSize(len + 1); SetWcharFromDialogText(text.buf, len + 1, d); return flags |= 2; }
