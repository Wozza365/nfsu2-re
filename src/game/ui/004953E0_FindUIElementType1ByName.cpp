// PROFILE: game
// FindUIElementType1ByName, 22 bytes
// yugecin's prototype: struct UIElementType1 *__cdecl FindUIElementType1ByName(char *fngName, char *str);
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

// FUNCTION: 0x004953E0
UIElementType1 *FindUIElementType1ByName(const char *fngName, const char *str)
{
	return FindUIElementType1ByHash(fngName, cihash(str));
}
