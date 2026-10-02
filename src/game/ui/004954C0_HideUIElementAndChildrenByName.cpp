// PROFILE: game
// HideUIElementAndChildrenByName, 31 bytes
// yugecin's prototype: int __cdecl HideUIElementAndChildrenByName(char *fngName, char *name);
struct UIElement;
struct UILabel;
struct UIElementType1;
unsigned int cihash(const char *str);
UIElement *FindUIElementByHash(const char *fngName, unsigned int hash);
UILabel *FindUILabelByHash(const char *fngName, unsigned int hash);
UIElementType1 *FindUIElementType1ByHash(const char *fngName, unsigned int hash);
int SetUILabelLanguageString(UILabel *label, unsigned int languageString);
void HideNullableUIElementAndChildren(UIElement *uielement);
void ShowNullableUIElementAndChildren(UIElement *uielement);

// FUNCTION: 0x004954C0
void HideUIElementAndChildrenByName(const char *fngName, const char *name)
{
	HideNullableUIElementAndChildren(FindUIElementByHash(fngName, cihash(name)));
}
