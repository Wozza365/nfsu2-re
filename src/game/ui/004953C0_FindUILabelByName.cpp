// PROFILE: game
// FindUILabelByName, 22 bytes
// yugecin's prototype: struct UILabel *__cdecl FindUILabelByName(char *fngName, char *str);
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

// FUNCTION: 0x004953C0
UILabel *FindUILabelByName(const char *fngName, const char *str)
{
	return FindUILabelByHash(fngName, cihash(str));
}
