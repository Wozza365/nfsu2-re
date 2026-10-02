// PROFILE: game
// SetUILabelByHashLanguageString, 33 bytes
// yugecin's prototype: int __cdecl SetUILabelByHashLanguageString(char *fngName, unsigned int hash, unsigned int languageString);
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

// FUNCTION: 0x00495460
int SetUILabelByHashLanguageString(const char *fngName, unsigned int hash, unsigned int languageString)
{
	return SetUILabelLanguageString(FindUILabelByHash(fngName, hash), languageString);
}
