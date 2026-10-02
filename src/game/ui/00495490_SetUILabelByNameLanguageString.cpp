// PROFILE: game
// SetUILabelByNameLanguageString, 39 bytes
// yugecin's prototype: int __cdecl SetUILabelByNameLanguageString(char *fngName, char *name, unsigned int languageString);
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

// FUNCTION: 0x00495490
int SetUILabelByNameLanguageString(const char *fngName, const char *name, unsigned int languageString)
{
	return SetUILabelLanguageString(FindUILabelByHash(fngName, cihash(name)), languageString);
}
